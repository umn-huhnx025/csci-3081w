/*******************************************************************************
 * Name            : main.cc
 * Project         : FlashPhoto
 * Module          : main
 * Description     : Entry point for FlashPhoto application
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 1/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app/FlashPhoto/src/flashphoto_app.h"
#include "lib/libimgtools/src/include/color_data.h"

/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
int main(int argc, char** argv) {
  if (argc == 1) {
    image_tools::FlashPhotoApp* app = new image_tools::FlashPhotoApp(800, 800);
    app->Init(argc, argv, 50, 50,
              image_tools::ColorData(1, 1, static_cast<float>(0.95)));
    app->RunMainLoop();
    delete app;
  } else {
    /* Create command line application? */
  }
  return 0;
} /* main() */
