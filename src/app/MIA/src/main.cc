/*******************************************************************************
 * Name            : main.cc
 * Project         : MIA
 * Module          : main
 * Description     : Entry point for MIA application
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 1/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "app/MIA/src/mia_app.h"
#include "lib/libimgtools/src/include/color_data.h"

/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
int main(int argc, char** argv) {
  int return_val = 0;
  if (argc == 1) {
    image_tools::MIAApp* app =
        new image_tools::MIAApp(400, 400, "resources/marker.png");
    app->Init(argc, argv, 50, 50,
              image_tools::ColorData(1, 1, static_cast<float>(0.95)));
    app->RunMainLoop();
    delete app;
  } else {
    image_tools::MIACmdManager* cmdApp =
        new image_tools::MIACmdManager(argc, argv);

    return_val = cmdApp->RunMain();
    delete cmdApp;
  }
  return return_val;
} /* main() */
