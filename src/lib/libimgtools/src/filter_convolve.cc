/*******************************************************************************
 * Name            : filter_convolve.cc
 * Project         : FlashPhoto
 * Module          : filter
 * Description     : Implementation of filter convolution class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/3/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/filter_convolve.h"
#include <stdio.h>
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/helpers.h"
#include "lib/libimgtools/src/include/kernel.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FilterConvolve::FilterConvolve(Kernel *kernel, bool convolve_alpha)
    : kernel_(kernel), convolve_alpha_(convolve_alpha) {}

FilterConvolve::~FilterConvolve(void) {
  if (kernel_) {
    delete kernel_;
  }
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
ColorData FilterConvolve::GeneratePixel(const PixelBuffer &buffer, int x,
                                        int y) const {
  if (NULL == kernel_) {
    return buffer.get_pixel(x, y);
  }

  int half_width = kernel_->width() / 2;
  int half_height = kernel_->height() / 2;
  int buffer_width = buffer.width();
  int buffer_height = buffer.height();
  ColorData result(0, 0, 0, 0);

#pragma omp for
  for (int i = 0; i < kernel_->width(); i++) {
    for (int j = 0; j < kernel_->height(); j++) {
      int c_x = x + i - half_width;
      int c_y = y + j - half_height;
      c_y = helpers::clamp(c_y, 0, buffer_height - 1);
      c_x = helpers::clamp(c_x, 0, buffer_width - 1);

      ColorData original = buffer.get_pixel(c_x, c_y);
      float a = original.alpha();
      ColorData premult = original * a;
      premult.alpha(a);

      ColorData weight = premult * kernel_->value(i, j);
      if (!convolve_alpha_) {
        weight.alpha(a);
      }
      result = result + weight;
    }
  }
  return result;
}

} /* namespace image_tools */
