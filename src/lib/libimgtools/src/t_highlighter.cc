/*******************************************************************************
 * Name            : t_highlighter.cc
 * Project         : BrushWork
 * Module          : Tool
 * Description     : Implementation of highlighter tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/t_highlighter.h"
#include <string>
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/m_oval.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
THighlighter::THighlighter(void) { mask(new MOval(7.0, 0.4, 90, 0.3)); }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
// Overrides the super's function to include the luminance of the canvasColor
// in the calculation of the tool's intensity
ColorData THighlighter::color_blend_math(float mask_pixel_amount,
                                         ColorData tool_color,
                                         ColorData current_color,
                                         ColorData background_color) {
  float L = current_color.luminance();
  float intensity = mask_pixel_amount * L;
  return tool_color * intensity + current_color * (1.0 - intensity);
}

} /* namespace image_tools */
