/*******************************************************************************
 * Name            : f_threshold.cc
 * Project         : FlashPhoto
 * Module          : filter
 * Description     : Implementation of FThreshold class.
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/4/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/f_threshold.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/helpers.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
ColorData FThreshold::GeneratePixel(const PixelBuffer &buffer, int x,
                                    int y) const {
  ColorData c = buffer.get_pixel(x, y);

  ColorData output;
  output.red(c.red() < threshold_ ? 0 : 1);
  output.green(c.green() < threshold_ ? 0 : 1);
  output.blue(c.blue() < threshold_ ? 0 : 1);

  return output;
}
} /* namespace image_tools  */
