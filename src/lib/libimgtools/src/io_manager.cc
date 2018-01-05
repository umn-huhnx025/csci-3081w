/*******************************************************************************
 * Name            : io_manager.cc
 * Project         : FlashPhoto
 * Module          : io_manager
 * Description     : Implementation of IOManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 20:47:05 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/io_manager.h"
#include <assert.h>
#include <iostream>
#include "lib/libimgtools/src/include/image_handler.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
IOManager::IOManager(void)
    : file_browser_(nullptr),
      load_canvas_btn_(nullptr),
      load_stamp_btn_(nullptr),
      save_canvas_btn_(nullptr),
      current_file_label_(nullptr),
      file_name_box_(nullptr),
      save_file_label_(nullptr),
      file_name_() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void IOManager::InitGlui(const GLUI *const glui, void (*s_gluicallback)(int)) {
  new GLUI_Column(const_cast<GLUI *>(glui), true);
  GLUI_Panel *image_panel =
      new GLUI_Panel(const_cast<GLUI *>(glui), "Image I/O");
  AddFileBrowserToGLUI(image_panel, s_gluicallback);
  AddLoadStampToGLUI(image_panel, s_gluicallback);
  new GLUI_Separator(image_panel);
  AddSaveCanvasToGLUI(image_panel, s_gluicallback);
}

void IOManager::AddFileBrowserToGLUI(GLUI_Panel *image_panel,
                                     void (*s_gluicallback)(int)) {
  file_browser_ = new GLUI_FileBrowser(image_panel, "Choose Image", false,
                                       UICtrl::UI_FILE_BROWSER, s_gluicallback);

  file_browser_->set_h(400);

  file_name_box_ = new GLUI_EditText(image_panel, "Image:", file_name_,
                                     UICtrl::UI_FILE_NAME, s_gluicallback);
  file_name_box_->set_w(200);

  new GLUI_Separator(image_panel);

  current_file_label_ =
      new GLUI_StaticText(image_panel, "Will load image: none");
  load_canvas_btn_ =
      new GLUI_Button(image_panel, "Load Canvas", UICtrl::UI_LOAD_CANVAS_BUTTON,
                      s_gluicallback);
  load_canvas_toggle(false);
}

void IOManager::AddLoadStampToGLUI(GLUI_Panel *image_panel,
                                   void (*s_gluicallback)(int)) {
  load_stamp_btn_ = new GLUI_Button(
      image_panel, "Load Stamp", UICtrl::UI_LOAD_STAMP_BUTTON, s_gluicallback);
  load_stamp_toggle(false);
}

void IOManager::AddSaveCanvasToGLUI(GLUI_Panel *image_panel,
                                    void (*s_gluicallback)(int)) {
  save_file_label_ = new GLUI_StaticText(image_panel, "Will save image: none");

  save_canvas_btn_ =
      new GLUI_Button(image_panel, "Save Canvas", UICtrl::UI_SAVE_CANVAS_BUTTON,
                      s_gluicallback);
  save_canvas_toggle(false);
}

bool IOManager::is_valid_image_file(const std::string &name) {
  FILE *f;
  bool is_valid = false;
  if (is_valid_image_file_name(name)) {
    if ((f = fopen(name.c_str(), "r"))) {
      is_valid = true;
      fclose(f);
    }
  }
  return is_valid;
}

void IOManager::set_image_file(const std::string &file_name) {
  // If a directory was selected
  // instead of a file, use the
  // latest file typed or selected.
  std::string image_file = file_name;
  if (!is_valid_image_file_name(image_file)) {
    image_file = file_name_;
  }

  // TOGGLE SAVE FEATURE
  // If no file is selected or typed,
  // don't allow file to be saved. If
  // there is a file name, then allow
  // file to be saved to that name.

  if (!is_valid_image_file_name(image_file)) {
    save_file_label_->set_text("Will save image: none");
    save_canvas_toggle(false);
  } else {
    save_file_label_->set_text(
        (std::string("Will save image: ") + image_file).c_str());
    save_canvas_toggle(true);
  }

  // TOGGLE LOAD FEATURE

  // If the file specified cannot be opened,
  // then disable stamp and canvas loading.
  if (is_valid_image_file(image_file)) {
    load_stamp_toggle(true);
    load_canvas_toggle(true);

    current_file_label_->set_text(
        (std::string("Will load: ") + image_file).c_str());
    file_name_box_->set_text(image_file);
  } else {
    load_stamp_toggle(false);
    load_canvas_toggle(false);
    current_file_label_->set_text("Will load: none");
  }
}

void IOManager::LoadImageToCanvas(PixelBuffer **buffer) {
  assert(buffer && *buffer);
  delete *buffer;
  *buffer = ImageHandler::LoadImage(file_name());
}

void IOManager::LoadImageToStamp(PixelBuffer **buffer) {
  *buffer = ImageHandler::LoadImage(file_name());
}

void IOManager::SaveCanvasToFile(const PixelBuffer &buffer) {
  ImageHandler::SaveImage(file_name_, &buffer);
}

} /* namespace image_tools */
