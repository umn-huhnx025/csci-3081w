/*******************************************************************************
 * Name            : f_saturate.h
 * Project         : FlashPhoto
 * Module          : filter
 * Description     : Header file for FSaturate class.
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/1/15
 * Original Author : Seth Johnson
 *
******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_SATURATE_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_SATURATE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/filter.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Implements a saturation filter
 *
 * A Filter that adjusts the saturation or colorfulness of an image. This can
 * be used to convert an image to grayscale.
 */
class FSaturate : public Filter {
 public:
  explicit FSaturate(float amount) : amount_(amount) {}

 private:
  virtual ColorData GeneratePixel(const PixelBuffer& buffer, int x,
                                  int y) const;
  /**
   * @brief The percent of the original saturation that should be used when
   * picking the output color. (0 = grayscale, 1 = original
   * color, 2 = twice the saturation of the original)
   *
   */
  float amount_;
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_SATURATE_H_ */
