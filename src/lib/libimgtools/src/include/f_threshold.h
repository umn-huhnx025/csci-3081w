/*******************************************************************************
 * Name            : f_threshold.h
 * Project         : FlashPhoto
 * Module          : filter
 * Description     : Header file for FThreshold class.
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/4/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_THRESHOLD_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_THRESHOLD_H_

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
 * @brief A threshold filter
 *
 * The effect of this filter is to set the RGB components of all pixels that it
 * operates on to 1 if the RGB value is greater than the threshold, and 0
 * otherwise.
 */
class FThreshold : public Filter {
 public:
  explicit FThreshold(float threshold) : threshold_(threshold) {}

 private:
  virtual ColorData GeneratePixel(const PixelBuffer& buffer, int x,
                                  int y) const;
  float threshold_;
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_THRESHOLD_H_ */
