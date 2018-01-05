/*******************************************************************************
 * Name            : i_png_handler.h
 * Project         : image_tools
 * Module          : io_handler
 * Description     : Header file for PNG I/O handler
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/2/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_I_PNG_HANDLER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_I_PNG_HANDLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "lib/libimgtools/src/include/image_handler.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Handles PNG image loading/saving via the libpng library. This is a
 * static class, serving as more of a namespace for grouping common
 * functionality.
 *
 */
class IPNGHandler : public ImageHandler {
 public:
  static PixelBuffer* LoadImage(const std::string file_name);
  static bool SaveImage(const std::string file_name, const PixelBuffer* buffer);
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_I_PNG_HANDLER_H_ */
