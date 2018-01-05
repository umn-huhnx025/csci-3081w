/*******************************************************************************
 * Name            : kernel.h
 * Project         : FlashPhoto
 * Module          : kernel
 * Description     : Header file for kernel base class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/1/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/
#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_KERNEL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_KERNEL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "lib/libimgtools/src/include/float_matrix.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The base class for all mathematical kernels used for filtering
 *
 */
class Kernel : public FloatMatrix {
 public:
  explicit Kernel(int rad);
  virtual ~Kernel() {}

  /**
   * @brief Get the radius of the kernel
   *
   */
  int radius(void) { return radius_; }
  std::ostream& operator<<(std::ostream& s);

 protected:
  virtual float get_intensity(int x, int y, float radius) { return 1; }
  /**
   * @brief Get the sum total of all elements of the kernel
   *
   */
  float sum(void);

  /**
   * @brief Normalize the kernel by dividing each element by the sum
   *
   */
  void NormalizeKernel(void);

  /**
   * @brief The default way to generate a kernel, which is just 1's everywhere
   *
   */
  void GenerateKernel(void);

 private:
  int radius_; /**< The kernel radius  */
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_KERNEL_H_ */
