/*******************************************************************************
 * Name            : Mask.h
 * Project         : image_tools
 * Module          : Mask
 * Description     : Header file for Mask base class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_MASK_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_MASK_H_

#include "lib/libimgtools/src/include/float_matrix.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Base class for representing the shape of a tool.
 * Mask is a wrapper for the array of floats representing the shape of a
 * tool. It does not have a shape; shapes are defined implicitly with
 * get_intensity().
 */
class Mask : public FloatMatrix {
 public:
  Mask(float radius, float opacity);
  Mask(void);
  virtual ~Mask(void);

 protected:
  /**
   * @brief Generate the intensity value array that defines the shape and effect
   * of the tool.
   * Relies on the derived class implementation of get_intensity to do so.
   */
  void GenerateMask(void);

  /**
   * @brief Define the shape of the mask.
   * @param x The X coordinate of the tool/mouse location
   * @param y The Y coordinate of the tool/mouse location
   * @param radius Distance from (x,y) tool/mouse location to compute intensity
   * at
   */
  virtual float get_intensity(int x, int y, float radius) = 0;

 private:
  /* Copy/move assignment/construction are disallowed */
  Mask(const Mask& rhs) = delete;
  Mask& operator=(const Mask& rhs) = delete;

  float radius_; /**< max distance in pixels the mask reaches from center  */
  float opacity_;
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_MASK_H_ */
