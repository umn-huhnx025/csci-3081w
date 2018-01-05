/*******************************************************************************
 * Name            : t_blur.cc
 * Project         : FlashPhoto
 * Module          : tool
 * Description     : Implementation of blurring tool
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/4/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/t_blur.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/filter.h"
#include "lib/libimgtools/src/include/filter_factory.h"
#include "lib/libimgtools/src/include/helpers.h"
#include "lib/libimgtools/src/include/m_constant.h"
#include "lib/libimgtools/src/include/m_linear.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
TBlur::TBlur()
    : filter_(FilterFactory::CreateFilter(FilterFactory::FILTER_BLUR, 1,
                                          static_cast<float>(0.5))),
      size_(10) {
  set_constant();
  mask(new MConstant(size_, 1));
  set_smear(3);
}

TBlur::~TBlur(void) {
  if (filter_) {
    delete filter_;
  }
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

ColorData TBlur::process_pixel(int mask_x, int mask_y, ColorData tool_color,
                               PixelBuffer *buffer, int buffer_x,
                               int buffer_y) {
  ColorData c = buffer->get_pixel(buffer_x, buffer_y);
  if (mask()->value(mask_x, mask_y) > 0.01) {
    c = filter_->GeneratePixel(*buffer, buffer_x, buffer_y);
  }
  return c;
}

} /* namespace image_tools */
