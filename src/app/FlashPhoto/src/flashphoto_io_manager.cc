/*******************************************************************************
 * Name            : flash_photo_io_manager.cc
 * Project         : FlashPhoto
 * Module          : io_manager
 * Description     : Implementation of FlashPhotoIOManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 20:47:05 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app/FlashPhoto/src/flashphoto_io_manager.h"
#include <assert.h>
#include <iostream>
#include "lib/libimgtools/src/include/image_handler.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FlashPhotoIOManager::FlashPhotoIOManager(void) : IOManager() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
GLUI_Panel *FlashPhotoIOManager::InitGlui(const GLUI *const glui,
                                          void (*s_gluicallback)(int)) {
  new GLUI_Column(const_cast<GLUI *>(glui), true);

  GLUI_Panel *image_panel =
      new GLUI_Panel(const_cast<GLUI *>(glui), "Image I/O");
  AddFileBrowserToGLUI(image_panel, s_gluicallback);

  AddLoadStampToGLUI(image_panel, s_gluicallback);
  new GLUI_Separator(image_panel);

  AddSaveCanvasToGLUI(image_panel, s_gluicallback);
  return image_panel;
}

} /* namespace image_tools */
