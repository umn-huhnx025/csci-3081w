/*******************************************************************************
 * Name            : k_gaussian.cc
 * Project         : FlashPhoto
 * Module          : kernel
 * Description     : Implementation of Gaussian kernel
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/2/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/k_gaussian.h"
#include <cmath>
#include <iostream>
#include "lib/libimgtools/src/include/helpers.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
KGaussian::KGaussian() : Kernel(0), sigma_(0) {
  GenerateKernel();
  NormalizeKernel();
}

KGaussian::KGaussian(float sigma)
    : Kernel(static_cast<int>(ceil(sigma))), sigma_(sigma) {
  GenerateKernel();
  NormalizeKernel();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
float KGaussian::get_intensity(int x, int y, float radius) {
  if (radius < 1) {
    return 1;
  }
  float dist = sqrt(x * x + y * y);
  return helpers::gaussian(dist, sigma_);
}

} /* namespace image_tools */
