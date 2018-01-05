/*******************************************************************************
 * Name            : t_chalk.cc
 * Project         : BrushWork
 * Module          : Tool
 * Description     : Implementation of chalk tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/t_chalk.h"
#include <cmath>
#include <cstdlib>
#include <string>
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/m_linear.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
TChalk::TChalk(void) : seed_(0) { mask(new MLinear(5.0, 1.0)); }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
//  A random number between 0.0 and 1.0 is multiplied by a brightened_mask to
//      vary the intensity used in the blending math
ColorData TChalk::color_blend_math(float mask_pixel_amount,
                                   ColorData tool_color,
                                   ColorData current_color,
                                   ColorData background_color) {
  float r = static_cast<float>(rand_r(&seed_)) / static_cast<float>(RAND_MAX);
  float brightened_mask = (mask_pixel_amount / 2 + 0.5);
  float intensity = round(brightened_mask * r);
  return tool_color * intensity + current_color * (1.0 - intensity);
}

}  // namespace image_tools
