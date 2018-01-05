/*******************************************************************************
 * Name            : f_quantize.cc
 * Project         : FlashPhoto
 * Module          : filter
 * Description     : Implementation of FQuantize class.
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/3/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/f_quantize.h"
#include <cmath>
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
ColorData FQuantize::GeneratePixel(const PixelBuffer &buffer, int x,
                                   int y) const {
  ColorData c = buffer.get_pixel(x, y);
  float red = c.red();
  float blue = c.blue();
  float green = c.green();
  int steps = bins_ - 1;
  red = round(red * steps) / steps;
  green = round(green * steps) / steps;
  blue = round(blue * steps) / steps;
  ColorData output(red, green, blue);
  return output;
}

} /* namespace image_tools */
