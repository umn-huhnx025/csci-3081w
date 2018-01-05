/*******************************************************************************
 * Name            : filter_factory.cc
 * Project         : FlashPhoto
 * Module          : filter
 * Description     : Implementation of Filter factor class.
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/3/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/filter_factory.h"
#include <stdarg.h> /* va_list, va_start, va_arg, va_end */

#include "lib/libimgtools/src/include/f_blur.h"
#include "lib/libimgtools/src/include/f_channel.h"
#include "lib/libimgtools/src/include/f_edge.h"
#include "lib/libimgtools/src/include/f_motion_blur.h"
#include "lib/libimgtools/src/include/f_quantize.h"
#include "lib/libimgtools/src/include/f_saturate.h"
#include "lib/libimgtools/src/include/f_sharpen.h"
#include "lib/libimgtools/src/include/f_special.h"
#include "lib/libimgtools/src/include/f_threshold.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

Filter* FilterFactory::CreateFilter(int filter_id, int param_count, ...) {
  va_list vl;
  va_start(vl, param_count);

  Filter* f = NULL;
  switch (filter_id) {
    case FILTER_BLUR:
      f = new FBlur(va_arg(vl, double));
      break;
    case FILTER_MOTION_BLUR:
      f = new FMotionBlur(
          va_arg(vl, double),
          static_cast<UICtrl::MotionBlurDirection>(va_arg(vl, int)));
      break;
    case FILTER_SHARPEN:
      f = new FSharpen(va_arg(vl, double));
      break;
    case FILTER_EDGE_DETECT:
      f = new FEdge;
      break;
    case FILTER_SATURATION:
      f = new FSaturate(va_arg(vl, double));
      break;
    case FILTER_QUANTIZE:
      f = new FQuantize(va_arg(vl, int));
      break;
    case FILTER_THRESHOLD:
      f = new FThreshold(va_arg(vl, double));
      break;
    case FILTER_CHANNELS:
      f = new FChannel(va_arg(vl, double), va_arg(vl, double),
                       va_arg(vl, double));
      break;
    case FILTER_SPECIAL:
      f = new FSpecial();
      break;
    default:
      break;
  }
  va_end(vl);

  return f;
}

void FilterFactory::ApplyFilter(const Filter& f, PixelBuffer** buffer) {
  PixelBuffer* old_buffer = *buffer;
  *buffer = f.GenerateFilteredBuffer(**buffer);
  if (old_buffer) {
    delete old_buffer;
  }
}

} /* namespace image_tools */
