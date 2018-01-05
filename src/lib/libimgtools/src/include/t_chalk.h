/*******************************************************************************
 * Name            : t_chalk.h
 * Project         : image_tools
 * Module          : Tool
 * Description     : Header file for Chalk class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_T_CHALK_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_T_CHALK_H_

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
 * @brief This tool simulates the usage of Chalk.
 * It has an linear mask with a radius of 5.0 (diameter of 11), an opacity of
 * 1.0 (completely opaque).  color_blend_math() is overriden to randomly change
 * the tool's intensity at a pixel.
 */
class TChalk : public Tool {
 public:
  TChalk(void);

  ColorData color_blend_math(float mask_pixel_amount, ColorData tool_color,
                             ColorData current_color,
                             ColorData background_color);

  std::string name(void) { return "Chalk"; }

 private:
  unsigned seed_; /** Random seed for use with color blending */
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_T_CHALK_H_ */
