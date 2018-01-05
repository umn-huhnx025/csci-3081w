/*******************************************************************************
 * Name            : mia_cmd_manager.h
 * Project         : MIA
 * Module          : command_line_manager
 * Description     : Header for MIACmdManager class
 * Copyright       : 2016 Curlin Group. All rights reserved.
 * Creation Date   : Sun Dec 4 2016
 * Original Author : Kent Miller
 *
 ******************************************************************************/

#ifndef SRC_APP_MIA_SRC_MIA_CMD_MANAGER_H_
#define SRC_APP_MIA_SRC_MIA_CMD_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include "app/MIA/src/mia_cmd_input_error_handler.h"
#include "app/MIA/src/mia_filter_manager.h"
#include "app/MIA/src/mia_io_manager.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Manager for all command line actions that can be leveraged by the
 * application.  Handles all valid and invalid command line inputs.
 */
class MIACmdManager {
 public:
  MIACmdManager(int argc, char** argv);
  virtual ~MIACmdManager();

  /**
   * @brief The main loop that runs the command line manager.  It first checks
   * for valid input, executes the commands, produces any output, and then
   * exits.
   */
  int RunMain();

  /**
   * @brief Checks each command to see if it is valid and can be
   * successfully carried out by the application.
   *
   * @return TRUE if input is valid, FALSE if not
   */
  bool ValidInput();

  /**
   * @brief The -h cmd line command
   *
   * Displays all the valid commands and their correct use in the
   * terminal.  Can be directly called in the terminal, and also displays if
   * invalid input is entered by the user.
   *
   * Proper cmd line usage is
   * <program path> -h
   */
  void DisplayHelp();

  /**
   * @brief The -sharpen <float> cmd line command
   *
   * Sharpens the image file listed in the arguments list before it. Note that
   * -sharpen can be in a list of filter commands and will be applied
   * according to its position in the list of commands. Once -sharpen is applied
   * (as well as all following filters in the list of commands) the image will
   * be output to a new file with name/type supplied by the user in the cmd line
   * arguments.
   *
   * Proper cmd line usage is
   * <program path> input_img.type -sharpen output_img.type
   * Note that the image types must match and be supported by the application.
   */
  void Sharpen(float amount);

  /**
   * @brief The -edge cmd line command
   *
   * Runs the image through the EdgeDetect filter.  Note that -edge can be in a
   * list of filter commands and will be applied according to its position in
   * the list of commands. Once -edge is applied (as well as all following
   * filters in the list of commands) the image will be output to a new file
   * with the name/type supplied by the user in the cmd line arguments.
   *
   * Proper cmd line usage is
   * <program path> input_img.type -edge output_img.type
   * Note that the image types must match and be supported by the application.
   */
  void EdgeDetect();

  /**
   * @brief The -threshold <float> cmd line command
   *
   * Runs the image through the Threshold filter.  Note that -threshold can be
   * in a list of filter commands and will be applied according to its position
   * in the list of commands. Once -threshold is applied (as well as all
   * following filters in the list of commands) the image will be output to a
   * new file with the name/type supplied by the user in the cmd line arguments.
   *
   * Proper cmd line usage is
   * <program path> input_img.type -threshold <float> output_img.type
   * Note that the image types must match and be supported by the application.
   */
  void Threshold(float amount);

  /**
   * @brief The -quantize <int> cmd line command
   *
   * Runs the image through the Quantize filter.  Note that -quantize can be
   * in a list of filter commands and will be applied according to its position
   * in the list of commands. Once -quantize is applied (as well as all
   * following filters in the list of commands) the image will be output to a
   * new file with the name/type supplied by the user in the cmd line arguments.
   *
   * Proper cmd line usage is
   * <program path> input_img.type -quantize <float> output_img.type
   * Note that the image types must match and be supported by the application.
   */
  void Quantize(int bins);

  /**
   * @brief The -blur <float> cmd line command
   *
   * Runs the image through the Blur filter.  Note that -blur can be
   * in a list of filter commands and will be applied according to its position
   * in the list of commands. Once -blur is applied (as well as all
   * following filters in the list of commands) the image will be output to a
   * new file with the name/type supplied by the user in the cmd line arguments.
   *
   * Proper cmd line usage is
   * <program path> input_img.type -blur <float> output_img.type
   * Note that the image types must match and be supported by the application.
   */
  void Blur(float amount);

  /**
   * @brief The -saturate <float> cmd line command
   *
   * Runs the image through the Saturate filter.  Note that -saturate can be
   * in a list of filter commands and will be applied according to its position
   * in the list of commands. Once -saturate is applied (as well as all
   * following filters in the list of commands) the image will be output to a
   * new file with the name/type supplied by the user in the cmd line arguments.
   *
   * Proper cmd line usage is
   * <program path> input_img.type -saturate <float> output_img.type
   * Note that the image types must match and be supported by the application.
   */
  void Saturate(float amount);

  /**
   * @brief The -channel <float> <float> <float> cmd line command
   *
   * Runs the image through the Channels filter.  Note that -saturate can be
   * in a list of filter commands and will be applied according to its position
   * in the list of commands. Once -saturate is applied (as well as all
   * following filters in the list of commands) the image will be output to a
   * new file with the name/type supplied by the user in the cmd line arguments.
   *
   * Proper cmd line usage is
   * <pgrm path> input_img.type -channel <float> <float> <float> output_img.type
   * Note that the image types must match and be supported by the application.
   */
  void Channel(float r, float g, float b);

  /**
   * @brief The -compare cmd line command
   *
   * Compares two images pixel by pixel. If the images are identical, outputs
   * 1, otherwise outputs 0.
   *
   * Proper cmd line usage is
   * <program path> input_img.type -compare output_img.type
   * Note that the image types must match and be supported by the application.
   */
  void Compare(std::string img1, std::string img2);

  /**
   * @brief The -convert cmd line command
   *
   * Converts an image of one type into an image of another type.
   *
   * Proper cmd line usage is
   * <program path> input_img.type -compare output_img.type
   * Note that the image types must be supported by the application.
   */
  // void Convert(char* img1, char* img2);

 private:
  /* Copy/move assignment/construction are disallowed */
  MIACmdManager(const MIACmdManager& rhs) = delete;
  MIACmdManager& operator=(const MIACmdManager& rhs) = delete;

  void RunCommands();
  int GetCurrentCmd(char* cur_cmd);

  enum CMD {
    INVALID,
    FILE,
    HELP,
    SHARPEN,
    EDGE,
    THRESHOLD,
    QUANTIZE,
    BLUR,
    SATURATE,
    CHANNEL,
    COMPARE
  };

  std::map<std::string, int> cmd_types_ = {{"h", HELP},
                                           {"sharpen", SHARPEN},
                                           {"edge", EDGE},
                                           {"threshold", THRESHOLD},
                                           {"quantize", QUANTIZE},
                                           {"blur", BLUR},
                                           {"saturate", SATURATE},
                                           {"channel", CHANNEL},
                                           {"compare", COMPARE}};

  int num_args_;
  char** commands_;
  bool in_file_set_;
  bool out_file_set_;
  MIACmdInputErrorHandler* err_handler_;
  image_tools::PixelBuffer* output_buffer_;
  std::string input_file_;
  std::string output_file_;

  const char* flt = "float";
  const char* intgr = "int";
};

} /* namespace image_tools */

#endif  // SRC_APP_MIA_SRC_MIA_CMD_MANAGER_H_
