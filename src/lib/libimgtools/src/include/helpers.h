/*******************************************************************************
 * Name            : helpers.h
 * Project         : image_tools
 * Module          : utils
 * Description     : Header file for Helper class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/1/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_HELPERS_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_HELPERS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>
#include <cmath>
#include "lib/libimgtools/src/include/color_data.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {
namespace helpers {

/*******************************************************************************
 * Forward Declations
 ******************************************************************************/
/**
 * @brief Linear interpolation between 2 two elements by a factor r
 *
 */
template <typename T>
T lerp(T a, T b, float r) {
  return a + (b - a) * r;
}

/**
 * @brief Clamp the value of a type between [high,low] (inclusive)
 *
 * @return The clamped value
 */
template <typename T>
T clamp(T x, T low, T high) {
  return std::min(std::max(x, low), high);
}

/**
 * @brief Get the std deviation of a value in a gaussian distribution
 *
 */
inline float gaussian(float x, float sigma) {
  return exp(
      -(pow(x, 2) / (2 * pow(sigma, 2)) + pow(0, 2) / (2 * pow(sigma, 2))));
}

} /* namespace helpers */

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_HELPERS_H_ */
