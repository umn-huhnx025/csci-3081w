/*******************************************************************************
 * Name            : t_stamp.cc
 * Project         : image_tools
 * Module          : Tool
 * Description     : Implementation of Stamp tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/4/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/t_stamp.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
TStamp::TStamp() : stamp_buffer_(NULL) { set_smear(0); }

TStamp::~TStamp() { delete stamp_buffer_; }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
ColorData TStamp::process_pixel(int maskx, int masky, ColorData toolcolor,
                                PixelBuffer* buffer, int bufferx, int buffery) {
  ColorData canvascolor = buffer->get_pixel(bufferx, buffery);
  ColorData stampcolor = stamp_buffer_->get_pixel(maskx, masky);
  float alpha = stampcolor.alpha();

  stampcolor.red(toolcolor.red() * stampcolor.red());
  stampcolor.green(toolcolor.green() * stampcolor.green());
  stampcolor.blue(toolcolor.blue() * stampcolor.blue());

  // Use the alpha to blend the colors
  ColorData C =
      stampcolor * alpha + buffer->get_pixel(bufferx, buffery) * (1 - alpha);

  // Adjust the alpha
  C.alpha(canvascolor.alpha() + alpha * (1 - canvascolor.alpha()));
  return C;
}

} /* namespace image_tools */
