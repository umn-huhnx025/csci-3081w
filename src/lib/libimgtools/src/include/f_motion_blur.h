/*******************************************************************************
 * Name            : f_motion_blur.h
 * Project         : FlashPhoto
 * Module          : filter
 * Description     : Header file for FMotionBlur class.
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/4/15
 * Original Author : Seth Johnson
 *
******************************************************************************/
#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_MOTION_BLUR_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_MOTION_BLUR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/filter_convolve.h"
#include "lib/libimgtools/src/include/k_motion_blur.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Implements a motion blurring filter.
 *
 * This is different that a blurring filter, which blurs in all directions. A
 * motion blur filter only blurs in one particular direction.
 *
 */
class FMotionBlur : public FilterConvolve {
 public:
  FMotionBlur(float amount, enum UICtrl::MotionBlurDirection direction)
      : FilterConvolve(new KMotionBlur(amount, direction), true) {}
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_MOTION_BLUR_H_ */
