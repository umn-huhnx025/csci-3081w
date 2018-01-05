/*******************************************************************************
 * Name            : f_sharpen.h
 * Project         : FlashPhoto
 * Module          : filter
 * Description     : Header file for FSharpen class.
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/3/15
 * Original Author : Seth Johnson
 *
******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_SHARPEN_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_SHARPEN_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/filter_convolve.h"
#include "lib/libimgtools/src/include/k_sharpen.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Implements a sharpening filter using a corresponding sharpening kernel
 *
 */
class FSharpen : public FilterConvolve {
 public:
  explicit FSharpen(float amount)
      : FilterConvolve(new KSharpen(amount), true) {}
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_SHARPEN_H_  */
