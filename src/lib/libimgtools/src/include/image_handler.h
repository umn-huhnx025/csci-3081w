/*******************************************************************************
 * Name            : image_handler.h
 * Project         : image_tools
 * Module          : io_handler
 * Description     : Header file for ImageHandler class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/2/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/
#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_IMAGE_HANDLER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_IMAGE_HANDLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A static class for handling image loading and saving. It currently
 * supports PNG and JPEG image loading (via derived classes).
 *
 */

class ImageHandler {
 public:
  enum IMAGE_TYPE { UNKNOWN_IMAGE, PNG_IMAGE, JPEG_IMAGE };

  /**
   * @brief Load the RGB data from the image associated with a file name to a
   * PixelBuffer.
   *
   * @param file_name The file name of the image
   *
   * @return A new PixelBuffer with the image data
   */
  static PixelBuffer* LoadImage(const std::string& file_name);

  /**
   * @brief Save the image data from a PixelBuffer to the specified file
   *
   * @return TRUE if save is successful, FALSE otherwise
   */
  static bool SaveImage(const std::string& file_name,
                        const PixelBuffer* buffer);

 private:
  static IMAGE_TYPE image_type(const std::string& file_name);
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_IMAGE_HANDLER_H_ */
