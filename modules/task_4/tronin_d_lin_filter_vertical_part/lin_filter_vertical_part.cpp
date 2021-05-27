// Copyright 2021 Tronin Dmitry
#include "../../modules/task_4/tronin_d_lin_filter_vertical_part/lin_filter_vertical_part.h"
#include <stdexcept>
#include <cmath>
#include "../../3rdparty/unapproved/unapproved.h"

static const double kPi = 3.141592653589793;

std::vector<double> CalculateGaussFilterSTD(size_t size, double sigma) {
    if (size % 2 == 0) {
        throw std::invalid_argument("Size can't be even");
    }
    if (size <= 0) {
        throw std::invalid_argument("Size should be positive");
    }
    if (sigma <= 0) {
        throw std::invalid_argument("Sigma should be positive");
    }
    double sum = 0;

    std::vector<double> filter(size * size, 0);
    for (int row = -static_cast<int>(size) / 2; row <= static_cast<int>(size) / 2; ++row) {
        for (int col = -static_cast<int>(size) / 2; col <= static_cast<int>(size) / 2; ++col) {
            filter[(row + static_cast<int>(size) / 2) * size + col + static_cast<int>(size) / 2] =
                1. / (2 * kPi * sigma * sigma)
                    * exp(-static_cast<double>(row * row + col * col) / (2 * sigma * sigma));
            sum += filter[(row + static_cast<int>(size) / 2) * size + col
                + static_cast<int>(size) / 2];
        }
    }

    double a = 0;

    for (int row = -static_cast<int>(size) / 2; row <= static_cast<int>(size) / 2; ++row) {
        for (int col = -static_cast<int>(size) / 2; col <= static_cast<int>(size) / 2; ++col) {
            filter[(row + static_cast<int>(size) / 2) * size + col + static_cast<int>(size) / 2] /=
                sum;
            a += filter[(row + static_cast<int>(size) / 2) * size + col
                + static_cast<int>(size) / 2];
        }
    }
    return filter;
}

std::vector<uint8_t> ApplyFilterSTD(const std::vector<double> &filter,
                                    const std::vector<uint8_t> &image,
                                    size_t width,
                                    size_t height,
                                    size_t filter_size, int number_of_threads) {
    if (image.size() != width * height) {
        throw std::invalid_argument("Incorrect image size");
    }
    if (filter.size() != filter_size * filter_size) {
        throw std::invalid_argument("Incorrect filter size");
    }
    if (width <= 0 || height <= 0 || filter_size <= 0) {
        throw std::invalid_argument("Arguments should be positive");
    }
    std::vector<uint8_t> result_image(image.size(), 1);

    std::vector<std::thread> threads;

    for (int i = 0; i < number_of_threads; ++i) {
        threads.emplace_back([width, height, number_of_threads, &image, &result_image, filter_size, &filter, i]() {
          for (int col = static_cast<int>(width) / number_of_threads * i;
               col < static_cast<int>(width) / number_of_threads * (i + 1)
                   + (i == number_of_threads ? static_cast<int>(width) % number_of_threads : 0); ++col) {
              for (int row = 0; row < static_cast<int>(height); ++row) {
                  double pixel_value = 0;
                  for (int filter_row = -static_cast<int>(filter_size) / 2;
                       filter_row <= static_cast<int>(filter_size) / 2;
                       ++filter_row) {
                      for (int filter_col =
                          -static_cast<int>(filter_size) / 2;
                           filter_col <= static_cast<int>(filter_size) / 2;
                           ++filter_col) {
                          size_t image_row =
                              static_cast<size_t>(ClampSTD(
                                  static_cast<int>(row) + filter_row,
                                  0,
                                  static_cast<int>(height) - 1));
                          size_t image_col =
                              static_cast<size_t>(ClampSTD(
                                  static_cast<int>(col) + filter_col,
                                  0,
                                  static_cast<int>(width) - 1));
                          double test = image[image_row * width + image_col]
                              * filter[
                                  (filter_row
                                      + static_cast<int>(filter_size) / 2)
                                      * filter_size
                                      + filter_col
                                      + static_cast<int>(filter_size) / 2];
                          pixel_value += test;
                      }
                  }
                  result_image[row * width + col] =
                      static_cast<uint8_t>(ClampSTD(pixel_value, 0., 255.));
              }
          }
        });
    }

    for (auto &thread : threads) {
        thread.join();
    }

    return result_image;
}