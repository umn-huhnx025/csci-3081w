/*******************************************************************************
 * Name            : Mask.cc
 * Project         : image_tools
 * Module          : Mask
 * Description     : Implementation of Mask class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/mask.h"
#include <cmath>
#include <iostream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Mask::Mask(void) : FloatMatrix(0, 0), radius_(0.0), opacity_(0.0) {}

Mask::Mask(float radius, float opacity)
    : FloatMatrix(ceil(radius) * 2 + 1, ceil(radius) * 2 + 1),
      radius_(radius),
      opacity_(opacity) {}

Mask::~Mask(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void Mask::GenerateMask(void) {
  for (int j = 0; j < height(); j++) {
    for (int i = 0; i < width(); i++) {
      int x = i - width() / 2;
      int y = j - height() / 2;
      float intensity = opacity_ * get_intensity(x, y, radius_);
      value(i, j, intensity);
    }
  }
}

}  // namespace image_tools
