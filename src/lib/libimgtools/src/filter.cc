/*******************************************************************************
 * Name            : filter.cc
 * Project         : FlashPhoto
 * Module          : filter
 * Description     : Implementation details for Filter base class.
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/1/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/filter.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
PixelBuffer *Filter::GenerateFilteredBuffer(
    const PixelBuffer &input_buffer) const {
  PixelBuffer *output_buffer =
      new PixelBuffer(input_buffer.width(), input_buffer.height(),
                      input_buffer.background_color());
  for (int i = 0; i < input_buffer.width(); i++) {
    for (int j = 0; j < input_buffer.height(); j++) {
      ColorData p = GeneratePixel(input_buffer, i, j);
      output_buffer->set_pixel(i, j, p.clamped_color());
    }
  }
  return output_buffer;
}

} /* namespace image_tools */
