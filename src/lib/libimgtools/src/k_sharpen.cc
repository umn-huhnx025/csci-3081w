/*******************************************************************************
 * Name            : k_sharpen.cc
 * Project         : FlashPhoto
 * Module          : kernel
 * Description     : Implementation of sharpening kernel.
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/3/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/k_sharpen.h"
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
KSharpen::KSharpen() : KGaussian(0) {
  GenerateKernel();
  NormalizeKernel();
}

KSharpen::KSharpen(float sigma) : KGaussian(sigma) {
  GenerateKernel();
  NormalizeKernel();

  // Negate all the values
  (*this) * -1;
  // Add two to the middle
  float middle_value = value(width() / 2, height() / 2);
  value(width() / 2, height() / 2, middle_value + 2);
}

} /* namespace image_tools */
