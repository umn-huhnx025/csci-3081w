/*******************************************************************************
 * Name            : tool.h
 * Project         : image_tools
 * Module          : Tool
 * Description     : Header file for Tool base class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_TOOL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_TOOL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/mask.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Tool is the representation of a particular BrushWork tool.
 * This baseclass is abstract and does not provide a default mask.
 * Tools inherited from this class MUST:\n
 * (1) Provide a name\n
 * (2) Define the mask. You will get an assert error if you do not.\n
 * Inherited classes may optionally override the default color_blend_math().
 */
class Tool {
 public:
  Tool(void);
  virtual ~Tool(void);

  /**
   * @brief Apply the selected tool to the buffer
   * @param[in] tool_x The X coordinate of current tool location
   * @param[in] tool_y The Y coordinate of current tool location
   * @param[in] tool_color The current color of the tool
   * @param buffer The buffer of pixels to apply the tool to
   */
  virtual void ApplyToBuffer(int tool_x, int tool_y, ColorData tool_color,
                             PixelBuffer* buffer);

  /**
   * @brief The name of the tool
   * @return
   */
  virtual std::string name(void) = 0;
  virtual int width() { return mask_ ? mask_->width() : 0; }
  virtual int height() { return mask_ ? mask_->height() : 0; }
  int max_smear() { return max_smear_; }
  bool should_smear() { return max_smear_ != 0; }

 protected:
  /**
   * @brief The definition of how the tool will operate on a single pixel on
   * the canvas when applied
   * @param[in] mask_pixel_amount Value of the relevant pixal in the mask
   * @param[in] tool_color Current color of the tool
   * @param[in] canvas_color Color of the background if no tool had been applied
   * @param[in] current_color Color present that this blend would replace
   * @return The new color definition for the pixel
   */
  virtual ColorData color_blend_math(float mask_pixel_amount,
                                     ColorData tool_color,
                                     ColorData current_color,
                                     ColorData background_color);

  /**
   * @brief Get the mask associated with the tool
   * @return The mask
   */
  Mask* mask(void) { return mask_; }

  /**
   * Set the mask associated with the tool
   */
  void mask(Mask* mask) { mask_ = mask; }

  void set_constant(void) { keep_buffer_constant_ = true; }
  void set_smear(int s) { max_smear_ = s; }

  virtual ColorData process_pixel(int maskX, int maskY, ColorData toolColor,
                                  PixelBuffer* buffer, int bufferX,
                                  int bufferY);

 private:
  /* Usage of copy/move construction or assignment is disallowed */
  Tool(const Tool& rhs) = delete;
  Tool& operator=(const Tool& rhs) = delete;

  Mask* mask_;
  bool keep_buffer_constant_;
  int max_smear_;
};

} /* namespace image_tools */

#endif /* SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_TOOL_H_ */
