/*******************************************************************************
 * Name            : t_eraser.h
 * Project         : image_tools
 * Module          : Tool
 * Description     : Header file for Eraserclass
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_T_ERASER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_T_ERASER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "lib/libimgtools/src/include/tool.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This tool simulates the usage of an Eraser.
 * It has a constant mask with a radius of 10.0 (diameter of 21) and an
 * opacity of 1.0 Eraser overrides the color_blend_math() function to provide
 * its
 * special eraser functionality.
 */
class TEraser : public Tool {
 public:
  TEraser(void);

  ColorData color_blend_math(float mask_pixel_amount, ColorData tool_color,
                             ColorData current_color,
                             ColorData background_color);

  std::string name(void) { return "Eraser"; }
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_T_ERASER_H_ */
