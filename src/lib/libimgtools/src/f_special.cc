/*******************************************************************************
 * Name            : f_special.cc
 * Project         : FlashPhoto
 * Module          : filter
 * Description     : Implementation of FSpecial class.
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/7/15
 * Original Author : Sarit Ghildayal
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/f_special.h"
#include <cmath>
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/f_blur.h"
#include "lib/libimgtools/src/include/filter.h"
#include "lib/libimgtools/src/include/filter_factory.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
ColorData FSpecial::GeneratePixel(const PixelBuffer &buffer,
                                  const PixelBuffer &blurred_buffer, int x,
                                  int y) const {
  const float blurred_luminance = blurred_buffer.get_pixel(x, y).luminance();

  const ColorData &p = buffer.get_pixel(x, y);

  ColorData output(pow(blurred_luminance, 7.0), p.red(),
                   pow(blurred_luminance, 7.0), p.alpha());
  return output;
}

PixelBuffer *FSpecial::GenerateFilteredBuffer(
    const PixelBuffer &input_buffer) const {
  PixelBuffer *blurred_buffer = new PixelBuffer(input_buffer);
  PixelBuffer *tmp = blurred_buffer;
  for (int y = 0; y < blurred_buffer->height(); y++) {
    for (int x = 0; x < blurred_buffer->width(); x++) {
      blurred_buffer->set_pixel(x, y, blurred_buffer->get_pixel(x, y) * 1.2);
    }
  }

  Filter *f = FilterFactory::CreateFilter(FilterFactory::FILTER_BLUR, 1, 3.5);
  FilterFactory::ApplyFilter(*f, &blurred_buffer);

  for (int y = 0; y < blurred_buffer->height(); y++) {
    for (int x = 0; x < blurred_buffer->width(); x++) {
      blurred_buffer->set_pixel(
          x, y, blurred_buffer->get_pixel(x, y).clamped_color());
    }
  }

  delete f;

  PixelBuffer *output_buffer =
      new PixelBuffer(input_buffer.width(), input_buffer.height(),
                      input_buffer.background_color());
#pragma omp for
  for (int i = 0; i < input_buffer.width(); i++) {
    for (int j = 0; j < input_buffer.height(); j++) {
      ColorData p = GeneratePixel(input_buffer, *blurred_buffer, i, j);
      output_buffer->set_pixel(i, j, p.clamped_color());
    }
  }

  return output_buffer;
}

} /* namespace image_tools */
