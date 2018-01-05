/*******************************************************************************
 * Name            : t_blur.h
 * Project         : FlashPhoto
 * Module          : tool
 * Description     : Header file for blurring tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/4/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_T_BLUR_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_T_BLUR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <string>
#include "lib/libimgtools/src/include/filter.h"
#include "lib/libimgtools/src/include/tool.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This tool serves as a mobile version of the blur filter, functions
 * much like the spray can, except with blurring neighboring pixels rather than
 * coloring them (linear falloff).
 *
 */

class TBlur : public Tool {
 public:
  TBlur();
  ~TBlur();
  std::string name() { return "Blur"; }

 private:
  /* Copy assignment/construction is disallowed */
  TBlur(const TBlur& rhs) = delete;
  TBlur& operator=(const TBlur& rhs) = delete;

  Filter* filter_;
  int size_;
  ColorData process_pixel(int mask_x, int mask_y, ColorData tool_color,
                          PixelBuffer* buffer, int buffer_x, int buffer_y);
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_T_BLUR_H_ */
