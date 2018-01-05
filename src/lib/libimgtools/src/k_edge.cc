/*******************************************************************************
 * Name            : k_edge.cc
 * Project         : FlashPhoto
 * Module          : kernel
 * Description     : Implementation of edge kernel
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/1/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/k_edge.h"
#include <cmath>
#include <iostream>
#include "lib/libimgtools/src/include/helpers.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
KEdge::KEdge(void) : Kernel(1) { GenerateKernel(); }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
float KEdge::get_intensity(int x, int y, float radius) {
  if (fabs(radius - x - 1) < 1 && fabs(radius - y - 1) < 1) {
    return 8;
  } else {
    return -1;
  }
}

} /* namespace image_tools */
