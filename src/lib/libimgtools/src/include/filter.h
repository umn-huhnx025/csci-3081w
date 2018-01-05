/*******************************************************************************
 * Name            : filter.h
 * Project         : FlashPhoto
 * Module          : filter
 * Description     : Header file for Filter base class.
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/1/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The base class for all filters
 *
 * A Filter describes an algorithm for producing a filtered pixel based on a
 * PixelBuffer and a set of coordinates in that PixelBuffer.
 */
class Filter {
 public:
  virtual ~Filter(void) {}
  /**
   * @brief  Generate a filtered pixel.
   *
   * Since this is the base class, this function just returns the same (x,y)
   * pixel.

   *
   * @param[in] buffer The buffer to filter
   * @param[in] x Current X position in buffer
w   * @param[in] y Current Y position in buffer
   *
   * @return The filtered pixel
   */
  virtual ColorData GeneratePixel(const PixelBuffer &buffer, int x,
                                  int y) const {
    ColorData p = buffer.get_pixel(x, y);
    return p;
  }

  /**
   * @brief Filter an entire buffer
   *
   * This function just calls GeneratePixel() for each pixel in the buffer,
   * populating a new PixelBuffer with the content.
   *
   * @param[in] input_buffer
   *
   * @return The new, filtered buffer
   */
  virtual PixelBuffer *GenerateFilteredBuffer(
      const PixelBuffer &input_buffer) const;
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_H_ */
