/*******************************************************************************
 * Name            : filter_factory.h
 * Project         : FlashPhoto
 * Module          : filter
 * Description     : Header file for Filter factor class.
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 4/3/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_FACTORY_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/filter.h"
#include "lib/libimgtools/src/include/filter_factory.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Implementation of the factor design pattern for filters
 *
 * @note This is a static class
 */
class FilterFactory {
 public:
  /**
   * @brief The list of filters that this factor knows how to construct
   *
   */
  enum Filters {
    FILTER_BLUR,
    FILTER_MOTION_BLUR,
    FILTER_SHARPEN,
    FILTER_EDGE_DETECT,
    FILTER_SATURATION,
    FILTER_QUANTIZE,
    FILTER_THRESHOLD,
    FILTER_CHANNELS,
    FILTER_SPECIAL,
    NUMFILTERS
  };

  /**
   * @brief Get the # of filters for the factor
   *
   * @return # of filters
   */
  static int num_filters(void) { return NUMFILTERS; }

  /**
   * @brief Create a new filter
   *
   * @param[in] filter_id ID of filter (from enum)
   * @param[in] param_count (how many parameters the filter takes)
   *
   * @return The constructed filter
   */
  static Filter* CreateFilter(int filter_id, int param_count, ...);

  /**
   * @brief Apply a filter to a buffer
   *
   * Buffer is updated to point to a NEW PixelBuffer (i.e. in place modification
   * is not done)
   *
   * @param f The filter
   * @param buffer The buffer to apply to
   */
  static void ApplyFilter(const Filter& f, PixelBuffer** buffer);
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_FACTORY_H_ */
