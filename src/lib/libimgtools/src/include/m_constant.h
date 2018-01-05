/*******************************************************************************
 * Name            : m_constant.h
 * Project         : image_tools
 * Module          : Mask
 * Description     : Header File for Constant Mask class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_M_CONSTANT_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_M_CONSTANT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/mask.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief MConstant is a Mask that is round, with a constant fill  value.
 */
class MConstant : public Mask {
 public:
  MConstant(float radius, float opacity);

 protected:
  float get_intensity(int x, int y, float radius);
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_M_CONSTANT_H_ */
