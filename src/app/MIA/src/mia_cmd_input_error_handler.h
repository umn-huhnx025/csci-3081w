/*******************************************************************************
 * Name            : mia_cmd_input_error_handler.h
 * Project         : MIA
 * Module          : command_line_manager
 * Description     : Header for MIACmdInputErrorHandler class
 * Copyright       : 2016 Curlin Group. All rights reserved.
 * Creation Date   : Tue Dec 6 2016
 * Original Author : Kent Miller
 *
 ******************************************************************************/

#ifndef SRC_APP_MIA_SRC_MIA_CMD_INPUT_ERROR_HANDLER_H_
#define SRC_APP_MIA_SRC_MIA_CMD_INPUT_ERROR_HANDLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>

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
class MIACmdInputErrorHandler {
 public:
  MIACmdInputErrorHandler() {}

  void GenericInputError(char* input) {
    std::cerr << "Error: Invalid input: " << input << std::endl;
  }
  void NoInputFileError() {
    std::cerr << "Error: No input file detected. Commands require "
              << "an input file to operate on." << std::endl;
  }
  void FileDoesNotExistError(char* input) {
    std::cerr << "Error: File does not exist: " << input << std::endl;
    std::cerr << "(Make sure to include the class path leading to the file)"
              << std::endl;
  }
  void FileInvalidTypeError(char* input) {
    std::cerr << "Error: File extension invalid: " << input << std::endl;
  }
  void NoOutputFileError() {
    std::cerr << "Error: No output file detected" << std::endl;
  }
  void TooManyFileArgsError(char* input) {
    std::cerr << "Error: Too many files detected. There must be exactly two "
              << "file arguments: one input, one output." << std::endl;
  }
  void CommandMissingArgsError(char* input, const char* expected,
                               int num_expected) {
    std::cerr << "Error: Command \'" << input << "\' is missing its arguments. "
              << "Expecting " << num_expected << " " << expected
              << " argument(s)" << std::endl;
  }
  void CommandArgTypeMismatchError(char* input, const char* expected) {
    std::cerr << "Error: Input \'" << input
              << "\' expected as arg of type: " << expected << std::endl;
  }
  void CommandArgOutOfBoundsError(char* input, const char* bounds) {
    std::cerr << "Error: Value: " << input << " outside of bounds. Valid range "
              << "is " << bounds << std::endl;
  }
};

} /* namespace image_tools */

#endif /* SRC_APP_MIA_SRC_MIA_CMD_INPUT_ERROR_HANDLER_H_ */
