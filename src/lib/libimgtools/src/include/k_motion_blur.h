/*******************************************************************************
 * Name            : k_motion_blur.h
 * Project         : FlashPhoto
 * Module          : kernel
 * Description     : Header file for motion blur kernel class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/4/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_K_MOTION_BLUR_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_K_MOTION_BLUR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/kernel.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A directional motion blurring kernel
 *
 * Defines a kernel that blurs pixels along a straight line when convolved
 * with an image.
 */
class KMotionBlur : public Kernel {
 public:
  KMotionBlur(float amount, enum UICtrl::MotionBlurDirection);

 protected:
  float get_intensity(int x, int y, float radius);

 private:
  float amount_;
  int direction_;
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_K_MOTION_BLUR_H_ */
