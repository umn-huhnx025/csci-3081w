/*******************************************************************************
 * Name            : pixel_buffer.cc
 * Project         : BrushWork
 * Module          : utils
 * Description     : Implementation of PixelBuffer class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include <math.h>
#include <cstring>
#include <iostream>
#include "lib/libimgtools/src/include/color_data.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
using std::cerr;
using std::endl;
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
PixelBuffer::PixelBuffer(int w, int h, ColorData background_color)
    : width_(w),
      height_(h),
      pixels_(w * h, background_color),
      background_color_(background_color) {}

PixelBuffer::PixelBuffer(const PixelBuffer &rhs)
    : PixelBuffer(rhs.width_, rhs.height_, rhs.background_color_) {
  std::copy(rhs.pixels_.begin(), rhs.pixels_.end(), pixels_.begin());
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
ColorData PixelBuffer::get_pixel(int x, int y) const {
  ColorData pixel_data;

  if ((x < 0) || (x >= width_) || (y < 0) || (y >= height_)) {
    cerr << "getPixel: x,y out of range: " << x << " " << y << endl;
  } else {
    int index = x + width_ * (y);
    pixel_data = pixels_[index];
  }
  return pixel_data;
}

void PixelBuffer::set_pixel(int x, int y, const ColorData &new_pixel) {
  if ((x < 0) || (x >= width_) || (y < 0) || (y >= height_)) {
    cerr << "setPixel: x,y out of range: " << x << " " << y << endl;
  } else {
    int index = x + width_ * (y);  // x + width*(height-(y+1));
    pixels_[index] = new_pixel;
  }
}
/*******************************************************************************
 * Operators
 ******************************************************************************/
PixelBuffer &PixelBuffer::operator=(const PixelBuffer &rhs) {
  /* Check for self-assignment! */
  if (this == &rhs) {
    return *this;
  }
  this->pixels_ = rhs.pixels_;
  this->background_color_ = rhs.background_color_;

  return *this;
} /* operator=() */

bool PixelBuffer::operator==(const PixelBuffer &rhs) {
  if ((this->height() != rhs.height()) || (this->width() != rhs.width())) {
    return false;
  }

  int n = this->height() * this->width();
  const ColorData *a, *b;
  for (int i = 0; i < n; i++) {
    a = this->data() + i;
    b = rhs.data() + i;
    if ((fabs(a->red() - b->red()) > 0) ||
        (fabs(a->green() - b->green()) > 0) ||
        (fabs(a->blue() - b->blue()) > 0)) {
      return false;
    }
  } /* for() */

  return true;
} /* operator==() */

} /* namespace image_tools */
