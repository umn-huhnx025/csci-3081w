/*******************************************************************************
 * Name            : tool.cc
 * Project         : BrushWork
 * Module          : Tool
 * Description     : Implementation of Tool base class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/tool.h"
#include <assert.h>
#include <algorithm>
#include <cmath>
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/mask.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Tool::Tool(void)
    : mask_(nullptr), keep_buffer_constant_(false), max_smear_(30) {}

Tool::~Tool(void) { delete mask_; }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
ColorData Tool::color_blend_math(float mask_pixel_amount, ColorData tool_color,
                                 ColorData current_color,
                                 ColorData background_color) {
  return tool_color * mask_pixel_amount +
         current_color * (1.0 - mask_pixel_amount);
}

ColorData Tool::process_pixel(int mask_x, int mask_y, ColorData tool_color,
                              PixelBuffer *buffer, int buffer_x, int buffer_y) {
  // Because we interpolate the pixels, colors overlap
  // and increase intensity quickly. We found that cubing
  // the mask intensity compensated for this.
  ColorData result = buffer->get_pixel(buffer_x, buffer_y);
  if (mask_) {
    float slimmed_mask_value = powf(mask_->value(mask_x, mask_y), 3);
    result = color_blend_math(slimmed_mask_value, tool_color,
                              buffer->get_pixel(buffer_x, buffer_y),
                              buffer->background_color());
  }

  return result;
}

void Tool::ApplyToBuffer(int tool_x, int tool_y, ColorData tool_color,
                         PixelBuffer *buffer) {
  int left_bound = std::max(tool_x - width() / 2, 0);
  int right_bound = std::min(tool_x + width() / 2, buffer->width() - 1);
  int lower_bound = std::max(tool_y - height() / 2, 0);
  int upper_bound = std::min(tool_y + height() / 2, buffer->height() - 1);

  PixelBuffer *temp_buffer = buffer;
  if (keep_buffer_constant_) {
    temp_buffer = new PixelBuffer(*buffer);
  }

#pragma omp for
  for (int y = lower_bound; y < upper_bound; y++) {
    for (int x = left_bound; x < right_bound; x++) {
      int mask_x = x - (tool_x - width() / 2);
      int mask_y = y - (tool_y - height() / 2);

      ColorData c =
          process_pixel(mask_x, mask_y, tool_color, temp_buffer, x, y);

      buffer->set_pixel(x, y, c);
    }
  }
  if (keep_buffer_constant_) {
    delete temp_buffer;
  }
}

} /* namespace image_tools */
