/*******************************************************************************
 * Name            : m_linear.cc
 * Project         : image_tools
 * Module          : Mask
 * Description     : Implementation of Linear mask class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/m_linear.h"
#include <cmath>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MLinear::MLinear(float radius, float opacity) : Mask(radius, opacity) {
  GenerateMask();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
float MLinear::get_intensity(int x, int y, float radius) {
  float hyp = sqrt(x * x + y * y);

  if (hyp <= radius) {
    return 1 - hyp / radius;
  } else {
    return 0.0;
  }
}

}  // namespace image_tools
