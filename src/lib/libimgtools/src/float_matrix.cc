/*******************************************************************************
 * Name            : float_matrix.cc
 * Project         : FlashPhoto
 * Module          : kernel
 * Description     : Implementation of FloatMatrix class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/1/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/float_matrix.h"
#include <stdio.h>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FloatMatrix::FloatMatrix() : height_(0), width_(0), float_array_() {}

FloatMatrix::FloatMatrix(int w, int h)
    : height_(h), width_(w), float_array_(w * h, 0.0) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
float FloatMatrix::value(int x, int y) const {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    return 0.f;
  } else {
    return float_array_[y * width_ + x];
  }
}

void FloatMatrix::value(int x, int y, float v) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    return;
  } else {
    float_array_[y * width_ + x] = v;
  }
}

void FloatMatrix::operator*(const float c) {
  for (int i = height() * width() - 1; i >= 0; i--) {
    float_array_[i] *= c;
  }
}

} /* namespace image_tools */
