/*******************************************************************************
 * Name            : f_channel.cc
 * Project         : FlashPhoto
 * Module          : filter
 * Description     : Implementation of FChannel class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/4/16
 * Original Author : Seth Johnson
 *
******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/f_channel.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
ColorData FChannel::GeneratePixel(const PixelBuffer& buffer, int x,
                                  int y) const {
  const ColorData& p = buffer.get_pixel(x, y);
  ColorData output(p.red() * red_, p.green() * green_, p.blue() * blue_,
                   p.alpha());
  return output;
}

} /* namespace image_tools */
