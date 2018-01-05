/*******************************************************************************
 * Name            : filter_convolve.h
 * Project         : FlashPhoto
 * Module          : filter
 * Description     : Header file for Filter convolution class.
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/3/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_CONVOLVE_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_CONVOLVE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/filter.h"
#include "lib/libimgtools/src/include/kernel.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Base class for filters that use convolution
 *
 * A Convolution Filter describes an algorithm for producing a filtered pixel
 * based on a PixelBuffer and a set of coordinates in that PixelBuffer.
 * It makes use of a kernel to determine the amounts that neighboring pixels
 * affect the output color.
 */

class FilterConvolve : public Filter {
 public:
  FilterConvolve(Kernel *kernel, bool convolve_alpha);
  virtual ~FilterConvolve(void);

 protected:
  /**
   * @brief Generate a new pixel at (x,y) by taking the kernel and convolving it
   * with the neigboring pixels.
   *
   * A function that will use the Kernel kernel_ to perform a weighted sum of
   * nearby pixels.
   *
   * @param[in] buffer The buffer to read from when convolving
   * @param[in] x X location of pixel to convolve
   * @param[in] y Y location of pixel to convolve
   *
   * @return The new pixel
   */
  virtual ColorData GeneratePixel(const PixelBuffer &buffer, int x,
                                  int y) const;

 private:
  /* Copy assignment/construction is disallowed */
  FilterConvolve(const FilterConvolve &rhs) = delete;
  FilterConvolve &operator=(const FilterConvolve &rhs) = delete;

  Kernel *kernel_;
  bool convolve_alpha_;
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_CONVOLVE_H_ */
