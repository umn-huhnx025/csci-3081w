/*******************************************************************************
 * Name            : m_oval.cc
 * Project         : image_tools
 * Module          : Mask
 * Description     : Implementation of Oval mask class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/m_oval.h"
#include <cmath>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MOval::MOval(float radius, float opacity, float angle, float ratio)
    : Mask(radius, opacity), angle_(angle), ratio_(ratio) {
  GenerateMask();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
float MOval::get_intensity(int x, int y, float radius) {
  float a = radius;
  float b = ratio_ * radius;
  float theta = angle_ / 180 * M_PI;

  float h = powf(x * cos(theta) + y * sin(theta), 2) / powf(a, 2) +
            powf(x * sin(theta) - y * cos(theta), 2) / powf(b, 2);
  if (h < 1)
    return 1.0;
  else
    return 0.0;
}

}  // namespace image_tools
