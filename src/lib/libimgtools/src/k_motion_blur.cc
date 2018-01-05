/*******************************************************************************
 * Name            : k_motion_blur.cc
 * Project         : FlashPhoto
 * Module          : kernel
 * Description     : Implementation of motion blur kernel
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/4/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/k_motion_blur.h"
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
KMotionBlur::KMotionBlur(float amount,
                         enum UICtrl::MotionBlurDirection direction)
    : Kernel(static_cast<int>(ceil(amount))),
      amount_(amount),
      direction_(direction) {
  GenerateKernel();
  NormalizeKernel();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
float KMotionBlur::get_intensity(int x, int y, float radius) {
  float element = 0.0;
  switch (direction_) {
    case UICtrl::MotionBlurDirection::UI_DIR_N_S:
      element = (x == 0) ? 1 : 0;
      break;
    case UICtrl::MotionBlurDirection::UI_DIR_E_W:
      element = (y == 0) ? 1 : 0;
      break;
    case UICtrl::MotionBlurDirection::UI_DIR_NE_SW:
      element = (y == x) ? 1 : 0;
      break;
    case UICtrl::MotionBlurDirection::UI_DIR_NW_SE:
      element = (y == -x) ? 1 : 0;
      break;
    default:
      break;
  }
  return element;
}

} /* namespace image_tools */
