/*******************************************************************************
 * Name            : i_png_handler.cc
 * Project         : image_tools
 * Module          : io_handler
 * Description     : Implementation of PNG I/O handler
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/2/15
 * Original Author : Sarit Ghildayal
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/i_png_handler.h"
#include <png.h>
#include <cstring>
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Static Member Functions
 ******************************************************************************/
PixelBuffer* IPNGHandler::LoadImage(const std::string fileName) {
  PixelBuffer* loaded_image_buffer = NULL;

  png_image image;
  memset(&image, 0, (sizeof image));
  image.version = PNG_IMAGE_VERSION;

  if (png_image_begin_read_from_file(&image, fileName.c_str())) {
    loaded_image_buffer =
        new PixelBuffer(image.width, image.height, ColorData(0.0, 0.0, 0.0));

    png_bytep buffer;
    image.format = PNG_FORMAT_RGBA;
    buffer = new png_byte[PNG_IMAGE_SIZE(image)];

    if (buffer && png_image_finish_read(&image, NULL, buffer, 0, NULL)) {
      for (unsigned y = 0; y < image.height; y++) {
        for (unsigned x = 0; x < image.width; x++) {
          int r, g, b, a = 0;
          r = static_cast<int>(buffer[(y * image.width * 4) + (x * 4)]);
          g = static_cast<int>(buffer[(y * image.width * 4) + (x * 4) + 1]);
          b = static_cast<int>(buffer[(y * image.width * 4) + (x * 4) + 2]);
          a = static_cast<int>(buffer[(y * image.width * 4) + (x * 4) + 3]);
          loaded_image_buffer->set_pixel(
              x, image.height - (y + 1),
              ColorData(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f));
        }
      }
    }
    delete[] buffer;
  }
  return loaded_image_buffer;
}

bool IPNGHandler::SaveImage(const std::string file_name,
                            const PixelBuffer* buffer_in) {
  bool success = false;

  png_image image;

  memset(&image, 0, (sizeof image));
  image.height = buffer_in->height();
  image.width = buffer_in->width();
  image.version = PNG_IMAGE_VERSION;
  image.opaque = NULL;
  image.format = PNG_FORMAT_RGBA;

  png_bytep buffer = new png_byte[PNG_IMAGE_SIZE(image)];

  for (int y = image.height - 1; y >= 0; y--) {
    for (unsigned x = 0; x < image.width; x++) {
      ColorData curr = buffer_in->get_pixel(x, y);
      buffer[((image.height - (y + 1)) * image.width + x) * 4] =
          static_cast<png_byte>((curr.red() * 255.0));
      buffer[((image.height - (y + 1)) * image.width + x) * 4 + 1] =
          static_cast<png_byte>((curr.green() * 255.0));
      buffer[((image.height - (y + 1)) * image.width + x) * 4 + 2] =
          static_cast<png_byte>((curr.blue() * 255.0));
      buffer[((image.height - (y + 1)) * image.width + x) * 4 + 3] =
          static_cast<png_byte>((curr.alpha() * 255.0));
    }
  }

  if (png_image_write_to_file(&image, file_name.c_str(), 0 /*convert_to_8bit*/,
                              buffer, 0 /*row_stride*/,
                              NULL /*colormap*/) != 0) {
    success = true;
  } else {
    success = false;
  }

  delete[] buffer;
  return success;
}

} /* namespace image_tools */
