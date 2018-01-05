/*******************************************************************************
> * Name            : mia_app.h
 * Project         : MIA
 * Module          : App
 * Description     : Header file for MIA class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 5/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_APP_MIA_SRC_MIA_APP_H_
#define SRC_APP_MIA_SRC_MIA_APP_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "app/MIA/src/mia_cmd_manager.h"
#include "app/MIA/src/mia_filter_manager.h"
#include "app/MIA/src/mia_io_manager.h"
#include "lib/libimgtools/src/include/base_gfx_app.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/state_manager.h"
#include "lib/libimgtools/src/include/tool.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class MIAApp : public BaseGfxApp {
 public:
  MIAApp(int width, int height, const std::string& marker_fname);
  virtual ~MIAApp(void);

  void MouseDragged(int x, int y);
  void MouseMoved(int x, int y) {}
  void LeftMouseDown(int x, int y);
  void LeftMouseUp(int x, int y) {}
  void Display(void);
  void GluiControl(int control_id);

  /**
   * @brief Initialize MIA
   *
   * @param[in] argc Unused--required by BaseGfxApp
   * @param[in] argv Unused--required by BaseGfxApp
   * @param[in] x Unused--required by BaseGfxApp
   * @param[in] y Unused--required by BaseGfxApp
   * @param[in] background_color The initial canvas color
   */
  void Init(int argc, char* argv[], int x, int y, ColorData background_color);

 private:
  /**
   * @brief Initialize the GLUI interface
   *
   */
  void InitGlui(void);
  void InitGraphics(void);

  /**
   * @brief Initialize the buffers for the main window
   */
  void InitializeBuffers(ColorData initial_color, int width, int height);

  /* Copy/move assignment/construction disallowed */
  MIAApp(const MIAApp& rhs) = delete;
  MIAApp& operator=(const MIAApp& rhs) = delete;

  /**
   * @brief Manager for all filter operations
   */
  MIAFilterManager filter_manager_;

  /**
   * @brief Manager for all I/O operations
   */
  MIAIOManager io_manager_;

  /**
   * @brief Manager for redo/undo stack
   */
  StateManager state_manager_;

  // This is the pointer to the buffer where the display PixelBuffer is stored
  PixelBuffer* display_buffer_;

  // The path to the marker file
  std::string marker_fname_;

  int cur_tool_;

  // These are used to store the selections from the GLUI user interface
  Tool** tools_;

  // Previous mouse coordinates for interpolating mouse moves
  int mouse_last_x_, mouse_last_y_;
  float cur_color_red_;
  float cur_color_green_;
  float cur_color_blue_;
};

} /* namespace image_tools */

#endif  // SRC_APP_MIA_SRC_MIA_APP_H_
