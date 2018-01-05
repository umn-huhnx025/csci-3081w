/*******************************************************************************
 * Name            : m_constant.cc
 * Project         : image_tools
 * Module          : Mask
 * Description     : Implementation of Constant mask class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/m_constant.h"
#include <cmath>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MConstant::MConstant(float radius, float opacity) : Mask(radius, opacity) {
  GenerateMask();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
float MConstant::get_intensity(int x, int y, float radius) {
  float hyp = sqrt(x * x + y * y);
  if (hyp > radius) {
    return 0.0;
  } else {
    return 1.0;
  }
}
}  // namespace image_tools
