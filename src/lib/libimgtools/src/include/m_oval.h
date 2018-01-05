/*******************************************************************************
 * Name            : m_oval.h
 * Project         : image_tools
 * Module          : Mask
 * Description     : Header File for Oval mask class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_M_OVAL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_M_OVAL_H_

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
 * @brief MOval is a Mask in the shape of an ellipse with an orientation.
 * It takes an angle in degrees, and a ratio between height and width.
 * It is of constant fill.
 */
class MOval : public Mask {
 public:
  MOval(float radius, float opacity, float angle, float ratio);
  virtual ~MOval(void) {}

 protected:
  float get_intensity(int x, int y, float radius);

 private:
  float angle_;
  float ratio_;
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_M_OVAL_H_ */
