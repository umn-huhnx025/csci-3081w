/*******************************************************************************
 * Name            : kernel.cc
 * Project         : FlashPhoto
 * Module          : kernel
 * Description     : Implementation of kernel base class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/3/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/kernel.h"
#include <stdio.h>
#include <iomanip>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Kernel::Kernel(int rad) : FloatMatrix(rad * 2 + 1, rad * 2 + 1), radius_(rad) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
float Kernel::sum() {
  float s = 0;
  for (int i = 0; i < width(); i++) {
    for (int j = 0; j < height(); j++) {
      s += value(i, j);
    }
  }
  return s;
}
std::ostream& Kernel::operator<<(std::ostream& s) {
  for (int j = 0; j < height(); j++) {
    for (int i = 0; i < width(); i++) {
      s << std::setprecision(3) << value(i, j);
    }
    s << std::endl;
  }
  return s;
} /* operator<<() */

void Kernel::NormalizeKernel() {
  float s = sum();
  if (!(s > 0)) {
    return;
  }
  float v;

  for (int i = 0; i < width(); i++) {
    for (int j = 0; j < height(); j++) {
      v = value(i, j);
      value(i, j, v / s);
    }
  }
}

void Kernel::GenerateKernel() {
  for (int j = 0; j < height(); j++) {
    for (int i = 0; i < width(); i++) {
      int x = i - width() / 2;
      int y = j - height() / 2;
      float intensity = get_intensity(x, y, radius_);

      value(i, j, intensity);
    }
  }
}

} /* namespace image_tools */
