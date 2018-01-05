/*******************************************************************************
 * Name            : flashphoto_app.cc
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of FlashPhoto
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app/FlashPhoto/src/flashphoto_app.h"
#include <cmath>
#include <iostream>
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/image_handler.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/t_stamp.h"
#include "lib/libimgtools/src/include/tool_factory.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FlashPhotoApp::FlashPhotoApp(int width, int height)
    : BaseGfxApp(width, height),
      filter_manager_(),
      io_manager_(),
      state_manager_(),
      glui_ctrl_hooks_(),
      display_buffer_(nullptr),
      cur_tool_(0),
      tools_(nullptr),
      mouse_last_x_(0),
      mouse_last_y_(0),
      cur_color_red_(0.0),
      cur_color_green_(0.0),
      cur_color_blue_(0.0) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void FlashPhotoApp::Init(int argc, char* argv[], int x, int y,
                         ColorData background_color) {
  BaseGfxApp::Init(argc, argv, x, y, GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH, true,
                   width() + 51, 50);

  // Set the name of the window
  set_caption("FlashPhoto");

  // Initialize Interface
  InitializeBuffers(background_color, width(), height());

  // Create array of tools and populate
  tools_ = new Tool*[ToolFactory::num_tools()];
  for (int i = 0; i < ToolFactory::num_tools(); i++) {
    tools_[i] = ToolFactory::CreateTool(i);
  }

  InitGlui();
  InitGraphics();
}

void FlashPhotoApp::Display(void) {
  DrawPixels(0, 0, width(), height(), display_buffer_->data());
}

FlashPhotoApp::~FlashPhotoApp(void) {
  if (display_buffer_) {
    delete display_buffer_;
  }

  // Delete each of the tools before deleting the list of tool pointers.
  if (tools_) {
    Tool** toolsEnd = tools_ + ToolFactory::num_tools();
    for (Tool** tool_i = tools_; tool_i < toolsEnd; tool_i++) {
      Tool* tool = *tool_i;
      if (tool) {
        delete tool;
      }
    }

    delete[] tools_;
  }
}

void FlashPhotoApp::MouseMoved(int x, int y) {}

void FlashPhotoApp::MouseDragged(int x, int y) {
  if (tools_[cur_tool_]->should_smear()) {
    int max_steps = tools_[cur_tool_]->max_smear();

    // We implimented a smoothing feature by interpolating between
    // mouse events. This is at the expense of processing, though,
    // because we just "stamp" the tool many times between the two
    // even locations. you can reduce max_steps until it runs
    // smoothly on your machine.

    // Get the differences between the events
    // in each direction
    int delta_x = x - mouse_last_x_;
    int delta_y = y - mouse_last_y_;

    // Calculate the min number of steps necesary to fill
    // completely between the two event locations.
    float pixels_between = fmax(abs(delta_x), abs(delta_y));
    int step_size = 1;

    // Optimize by maxing out at the max_steps,
    // and fill evenly between
    if (pixels_between > max_steps) {
      step_size = pixels_between / max_steps;
    }

    // Iterate between the event locations
    for (int i = 0; i < pixels_between; i += step_size) {
      int curr_x = mouse_last_x_ + (i * delta_x / pixels_between);
      int curr_y = mouse_last_y_ + (i * delta_y / pixels_between);

      tools_[cur_tool_]->ApplyToBuffer(
          curr_x, height() - curr_y,
          ColorData(cur_color_red_, cur_color_green_, cur_color_blue_),
          display_buffer_);
    }
  }

  // let the previous point catch up with the current.
  mouse_last_x_ = x;
  mouse_last_y_ = y;
}

void FlashPhotoApp::LeftMouseDown(int x, int y) {
  display_buffer_ = state_manager_.CommitState(display_buffer_);

  tools_[cur_tool_]->ApplyToBuffer(
      x, height() - y,
      ColorData(cur_color_red_, cur_color_green_, cur_color_blue_),
      display_buffer_);

  mouse_last_x_ = x;
  mouse_last_y_ = y;
}

void FlashPhotoApp::LeftMouseUp(int x, int y) {
  std::cout << "mouseReleased " << x << " " << y << std::endl;
}

void FlashPhotoApp::InitializeBuffers(ColorData background_color, int width,
                                      int height) {
  display_buffer_ = new PixelBuffer(width, height, background_color);
}

void FlashPhotoApp::InitGlui(void) {
  // Select first tool (this activates the first radio button in glui)
  cur_tool_ = 0;

  GLUI_Panel* toolPanel = new GLUI_Panel(glui(), "Tool Type");
  {
    GLUI_RadioGroup* radio = new GLUI_RadioGroup(
        toolPanel, &cur_tool_, UICtrl::UI_TOOLTYPE, s_gluicallback);
    for (int i = 0; i < ToolFactory::num_tools(); i++) {
      new GLUI_RadioButton(radio, tools_[i]->name().c_str());
    }
  }

  GLUI_Panel* color_panel = new GLUI_Panel(glui(), "Tool Color");
  {
    cur_color_red_ = 0;
    glui_ctrl_hooks_.spinner_red =
        new GLUI_Spinner(color_panel, "Red:", &cur_color_red_,
                         UICtrl::UI_COLOR_R, s_gluicallback);
    glui_ctrl_hooks_.spinner_red->set_float_limits(0, 1.0);

    cur_color_green_ = 0;
    glui_ctrl_hooks_.spinner_green =
        new GLUI_Spinner(color_panel, "Green:", &cur_color_green_,
                         UICtrl::UI_COLOR_G, s_gluicallback);
    glui_ctrl_hooks_.spinner_green->set_float_limits(0, 1.0);

    cur_color_blue_ = 0;
    glui_ctrl_hooks_.spinner_blue =
        new GLUI_Spinner(color_panel, "Blue:", &cur_color_blue_,
                         UICtrl::UI_COLOR_B, s_gluicallback);
    glui_ctrl_hooks_.spinner_blue->set_float_limits(0, 1.0);

    new GLUI_Button(color_panel, "Red", UICtrl::UI_PRESET_RED, s_gluicallback);
    new GLUI_Button(color_panel, "Orange", UICtrl::UI_PRESET_ORANGE,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Yellow", UICtrl::UI_PRESET_YELLOW,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Green", UICtrl::UI_PRESET_GREEN,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Blue", UICtrl::UI_PRESET_BLUE,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Purple", UICtrl::UI_PRESET_PURPLE,
                    s_gluicallback);
    new GLUI_Button(color_panel, "White", UICtrl::UI_PRESET_WHITE,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Black", UICtrl::UI_PRESET_BLACK,
                    s_gluicallback);
  }

  /* Initialize state management (undo, redo, quit) */
  state_manager_.InitGlui(glui(), s_gluicallback);

  /* Initialize Filtering */
  filter_manager_.InitGlui(glui(), s_gluicallback);

  /* Initialize image I/O */
  io_manager_.InitGlui(glui(), s_gluicallback);
  return;
}

void FlashPhotoApp::GluiControl(int control_id) {
  switch (control_id) {
    case UICtrl::UI_PRESET_RED:
      cur_color_red_ = 1;
      cur_color_green_ = 0;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_PRESET_ORANGE:
      cur_color_red_ = 1;
      cur_color_green_ = 0.5;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_PRESET_YELLOW:
      cur_color_red_ = 1;
      cur_color_green_ = 1;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_PRESET_GREEN:
      cur_color_red_ = 0;
      cur_color_green_ = 1;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_PRESET_BLUE:
      cur_color_red_ = 0;
      cur_color_green_ = 0;
      cur_color_blue_ = 1;
      update_colors();
      break;
    case UICtrl::UI_PRESET_PURPLE:
      cur_color_red_ = 0.5;
      cur_color_green_ = 0;
      cur_color_blue_ = 1;
      update_colors();
      break;
    case UICtrl::UI_PRESET_WHITE:
      cur_color_red_ = 1;
      cur_color_green_ = 1;
      cur_color_blue_ = 1;
      update_colors();
      break;
    case UICtrl::UI_PRESET_BLACK:
      cur_color_red_ = 0;
      cur_color_green_ = 0;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_APPLY_BLUR:
      display_buffer_ = state_manager_.CommitState(display_buffer_);
      filter_manager_.ApplyBlur(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_SHARP:
      display_buffer_ = state_manager_.CommitState(display_buffer_);
      filter_manager_.ApplySharpen(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_MOTION_BLUR:
      display_buffer_ = state_manager_.CommitState(display_buffer_);
      filter_manager_.ApplyMotionBlur(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_EDGE:
      display_buffer_ = state_manager_.CommitState(display_buffer_);
      filter_manager_.ApplyEdgeDetect(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_THRESHOLD:
      display_buffer_ = state_manager_.CommitState(display_buffer_);
      filter_manager_.ApplyThreshold(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_SATURATE:
      display_buffer_ = state_manager_.CommitState(display_buffer_);
      filter_manager_.ApplySaturate(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_CHANNEL:
      display_buffer_ = state_manager_.CommitState(display_buffer_);
      filter_manager_.ApplyChannel(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_QUANTIZE:
      display_buffer_ = state_manager_.CommitState(display_buffer_);
      filter_manager_.ApplyQuantize(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_SPECIAL_FILTER:
      display_buffer_ = state_manager_.CommitState(display_buffer_);
      filter_manager_.ApplySpecial(&display_buffer_);
      break;
    case UICtrl::UI_FILE_BROWSER:
      io_manager_.set_image_file(io_manager_.file_browser()->get_file());
      break;
    case UICtrl::UI_LOAD_CANVAS_BUTTON:
      io_manager_.LoadImageToCanvas(&display_buffer_);
      SetWindowDimensions(display_buffer_->width(), display_buffer_->height());
      break;
    case UICtrl::UI_LOAD_STAMP_BUTTON:
      PixelBuffer* loadedStamp;
      io_manager_.LoadImageToStamp(&loadedStamp);
      static_cast<TStamp*>(tools_[ToolFactory::TOOL_STAMP])
          ->set_stamp_buffer(loadedStamp);
      break;
    case UICtrl::UI_SAVE_CANVAS_BUTTON:
      // Reload the current directory:
      io_manager_.file_browser()->fbreaddir(".");
      io_manager_.SaveCanvasToFile(*display_buffer_);
      break;
    case UICtrl::UI_FILE_NAME:
      io_manager_.set_image_file(io_manager_.file_name());
      break;
    case UICtrl::UI_UNDO:
      state_manager_.UndoOperation(&display_buffer_);
      SetWindowDimensions(display_buffer_->width(), display_buffer_->height());
      break;
    case UICtrl::UI_REDO:
      state_manager_.RedoOperation(&display_buffer_);
      SetWindowDimensions(display_buffer_->width(), display_buffer_->height());
      Display();
      break;
    default:
      break;
  }

  // Forces canvas to update changes made in this function
  glui()->post_update_main_gfx();
}

/*******************************************************************************
 * Member Functions For Managing GLUI Interface
 ******************************************************************************/
void FlashPhotoApp::update_colors(void) {
  glui_ctrl_hooks_.spinner_blue->set_float_val(cur_color_blue_);
  glui_ctrl_hooks_.spinner_green->set_float_val(cur_color_green_);
  glui_ctrl_hooks_.spinner_red->set_float_val(cur_color_red_);
}

void FlashPhotoApp::InitGraphics(void) {
  // Initialize OpenGL for 2D graphics as used in the FlashPhoto app
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(0, width(), 0, height());
  glViewport(0, 0, width(), height());
}

} /* namespace image_tools */
