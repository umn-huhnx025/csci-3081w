/*******************************************************************************
 * Name            : state_manager.cc
 * Project         : FlashPhoto
 * Module          : state_manager
 * Description     : Implementation of StateManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Sun Oct 2 20:47:05 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/state_manager.h"
#include <iostream>
#include "lib/libimgtools/src/include/ui_ctrl.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
StateManager::StateManager(void)
    : undo_btn_(nullptr),
      redo_btn_(nullptr),
      max_undos_(50),
      history_states_(),
      redo_states_() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void StateManager::InitGlui(const GLUI *const glui,
                            void (*s_gluicallback)(int)) {
  undo_btn_ = new GLUI_Button(const_cast<GLUI *>(glui), "Undo", UICtrl::UI_UNDO,
                              s_gluicallback);
  undo_toggle(false);

  redo_btn_ = new GLUI_Button(const_cast<GLUI *>(glui), "Redo", UICtrl::UI_REDO,
                              s_gluicallback);
  redo_toggle(false);

  new GLUI_Button(const_cast<GLUI *>(glui), "Quit", UICtrl::UI_QUIT,
                  static_cast<GLUI_Update_CB>(exit));
}

void StateManager::UndoOperation(PixelBuffer **display_buffer) {
  if (!history_states_.empty()) {
    if (history_states_.size() >= max_undos_) {
      delete history_states_.front();
      history_states_.pop_front();
    }
    redo_states_.push(*display_buffer);
    *display_buffer = history_states_.back();
    history_states_.pop_back();
  }
  redo_toggle(!redo_states_.empty());
  undo_toggle(!history_states_.empty());
}

void StateManager::RedoOperation(PixelBuffer **display_buffer) {
  history_states_.push_back(*display_buffer);
  *display_buffer = redo_states_.top();
  redo_states_.pop();

  redo_toggle(!redo_states_.empty());
  undo_toggle(!history_states_.empty());
}

PixelBuffer *StateManager::CommitState(PixelBuffer *display_buffer) {
  PixelBuffer *new_state =
      new PixelBuffer(display_buffer->width(), display_buffer->height(),
                      display_buffer->background_color());
  *new_state = *display_buffer;
  history_states_.push_back(display_buffer);

  while (!redo_states_.empty()) {
    delete redo_states_.top();
    redo_states_.pop();
  }

  redo_toggle(!redo_states_.empty());
  undo_toggle(!history_states_.empty());
  return new_state;
}

} /* namespace image_tools */
