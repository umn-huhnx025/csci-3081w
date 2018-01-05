/*******************************************************************************
 * Name            : k_edge.h
 * Project         : FlashPhoto
 * Module          : kernel
 * Description     : Header file for edge kernel class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/3/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_K_EDGE_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_K_EDGE_H_

/*******************************************************************************
 * Class Definitions
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
 * @brief An edge detection kernel
 *
 * Defines a kernel that highlights edges visual edges between colors, and
 * colors non-edge areas black when convolved with an image.
 *
 */
class KEdge : public Kernel {
 public:
  KEdge();

 protected:
  float get_intensity(int x, int y, float radius);
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_K_EDGE_H_ */
