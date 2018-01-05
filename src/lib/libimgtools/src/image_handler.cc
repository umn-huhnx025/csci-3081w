
/*******************************************************************************
 * Name            : image_handler.cc
 * Project         : image_tools
 * Module          : io_handler
 * Description     : Implementation of ImageHandler class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/2/15
 * Original Author : Sarit Ghildayal
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/image_handler.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/i_jpeg_handler.h"
#include "lib/libimgtools/src/include/i_png_handler.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Static Functions
 ******************************************************************************/
PixelBuffer* ImageHandler::LoadImage(const std::string& file_name) {
  IMAGE_TYPE type = image_type(file_name);
  PixelBuffer* loaded_image = NULL;
  if (type == PNG_IMAGE) {
    loaded_image = IPNGHandler::LoadImage(file_name);
  } else if (type == JPEG_IMAGE) {
    loaded_image = IJPEGHandler::LoadImage(file_name);
  } else {
    // how to error out?
  }
  return loaded_image;
}

bool ImageHandler::SaveImage(const std::string& file_name,
                             const PixelBuffer* buffer) {
  IMAGE_TYPE type = image_type(file_name);
  bool success = false;
  if (type == PNG_IMAGE) {
    success = IPNGHandler::SaveImage(file_name, buffer);
  } else if (type == JPEG_IMAGE) {
    success = IJPEGHandler::SaveImage(file_name, buffer);
  } else {
    // how to error out?
  }
  return success;
}

ImageHandler::IMAGE_TYPE ImageHandler::image_type(
    const std::string& file_name) {
  if (file_name.find(".png", file_name.size() - 5) != std::string::npos) {
    return PNG_IMAGE;
  } else if (file_name.find(".jpg", file_name.size() - 5) !=
                 std::string::npos ||
             file_name.find(".jpeg", file_name.size() - 6) !=
                 std::string::npos) {
    return JPEG_IMAGE;
  } else {
    return UNKNOWN_IMAGE;
  }
}

} /* namespace image_tools */
