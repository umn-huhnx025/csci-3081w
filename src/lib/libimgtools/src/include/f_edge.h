/*******************************************************************************
 * Name            : f_edge.h
 * Project         : FlashPhoto
 * Module          : filter
 * Description     : Header file for FEdge class.
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/3/15
 * Original Author : Seth Johnson
 *
******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_EDGE_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_EDGE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/filter_convolve.h"
#include "lib/libimgtools/src/include/k_edge.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Implements an edge filter using an edge filter
 *
 */
class FEdge : public FilterConvolve {
 public:
  FEdge() : FilterConvolve(new KEdge(), false) {}
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_EDGE_H_ */
