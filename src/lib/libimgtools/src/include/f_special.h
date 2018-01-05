/*******************************************************************************
 * Name            : f_special.h
 * Project         : FlashPhoto
 * Module          : filter
 * Description     : Header file for FSpecial class.
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/7/15
 * Original Author : Sarit Ghildayal
 *
******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_SPECIAL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_SPECIAL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "lib/libimgtools/src/include/filter.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Implements a "night-vision" filter
 *
 */
class FSpecial : public Filter {
 public:
  PixelBuffer *GenerateFilteredBuffer(const PixelBuffer &input_buffer) const;

 private:
  virtual ColorData GeneratePixel(const PixelBuffer &buffer,
                                  const PixelBuffer &blurred_buffer, int x,
                                  int y) const;
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_SPECIAL_H_ */
