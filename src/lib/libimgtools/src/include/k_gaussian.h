/*******************************************************************************
 * Name            : k_gaussian.h
 * Project         : FlashPhoto
 * Module          : kernel
 * Description     : Header file for Gaussian kernel class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/2/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_K_GAUSSIAN_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_K_GAUSSIAN_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/kernel.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A gaussian kernel
 *
 * This is used for general blurring.
 */
class KGaussian : public Kernel {
 public:
  explicit KGaussian(float sigma);
  KGaussian(void);

 protected:
  /**
   * @brief The standard deviation of the Gaussian kernel.
   *
   * This controls how the values fall off from the center of the kernel.
   *
   */
  float sigma_;
  float get_intensity(int x, int y, float radius);
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_K_GAUSSIAN_H_ */
