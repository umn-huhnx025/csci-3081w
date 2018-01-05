/*******************************************************************************
 * Name            : f_quantize.h
 * Project         : FlashPhoto
 * Module          : filter
 * Description     : Header file for FQuantize class.
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/3/15
 * Original Author : Seth Johnson
 *
******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_QUANTIZE_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_QUANTIZE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/filter.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Implements a quantization filter
 *
 * Reduce the amount of information comprising an image by sorting each pixel
 * into one of n predefined bins that cover the full range of RGB (0.0-1.0).
 *
 */
class FQuantize : public Filter {
 public:
  explicit FQuantize(int bins) : bins_(bins) {}

 private:
  virtual ColorData GeneratePixel(const PixelBuffer& buffer, int x,
                                  int y) const;
  /**
   * @brief The number of categories (bins) to quantize pixels into based on
   * their value
   */
  int bins_;
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_QUANTIZE_H_ */
