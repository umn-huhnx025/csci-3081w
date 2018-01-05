/*******************************************************************************
 * Name            : mia_cmd_manager.cc
 * Project         : MIA
 * Module          : command_line_manager
 * Description     : Implementation of MIACmdManager class
 * Copyright       : 2016 Curlin Group. All rights reserved.
 * Creation Date   : Sun Dec 4 2016
 * Original Author : Kent Miller
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app/MIA/src/mia_cmd_manager.h"
#include <iomanip>
#include <string>
#include "lib/libimgtools/src/include/filter_factory.h"
#include "lib/libimgtools/src/include/image_handler.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MIACmdManager::MIACmdManager(int argc, char** argv)
    : num_args_(argc),
      commands_(argv),
      in_file_set_(false),
      out_file_set_(false),
      err_handler_(new MIACmdInputErrorHandler()),
      output_buffer_(nullptr),
      input_file_(),
      output_file_() {}

MIACmdManager::~MIACmdManager() {
  delete err_handler_;
  delete output_buffer_;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
int MIACmdManager::RunMain() {
  // Check for valid commands
  if (!ValidInput()) {
    DisplayHelp();
    return 1;
  }

  // Run the commands
  MIAIOManager* io_mngr = new MIAIOManager();
  input_file_ = commands_[1];
  output_file_ = commands_[num_args_ - 1];
  io_mngr->file_name(input_file_);
  if (!io_mngr->is_valid_image_file(
          io_mngr->image_name_plus_seq_offset(input_file_, 0))) {
    RunCommands();
  } else {
    while (io_mngr->is_valid_image_file(
        io_mngr->image_name_plus_seq_offset(input_file_, 0))) {
      std::string next_input_file =
          io_mngr->image_name_plus_seq_offset(input_file_, 1);
      io_mngr->file_name(output_file_);
      std::string next_output_file =
          io_mngr->image_name_plus_seq_offset(output_file_, 1);
      io_mngr->file_name(input_file_);

      // std::cout << "Processing " << input_file_ << std::endl;
      RunCommands();
      input_file_ = next_input_file;
      output_file_ = next_output_file;
    }
  }
  return 0;
}

// Input handlers
void MIACmdManager::RunCommands() {
  // std::cout << "Input file: " << input_file_ << std::endl;
  // std::cout << "Output file: " << output_file_ << std::endl;
  output_buffer_ = ImageHandler::LoadImage(input_file_);

  for (int arg = 1; arg < num_args_; ++arg) {
    int current_cmd = GetCurrentCmd(commands_[arg]);
    switch (current_cmd) {
      case HELP:
        DisplayHelp();
        return;
      case SHARPEN:
        Sharpen(std::stof(commands_[++arg]));
        break;
      case EDGE:
        EdgeDetect();
        break;
      case THRESHOLD:
        Threshold(std::stof(commands_[++arg]));
        break;
      case QUANTIZE:
        Quantize(std::stoi(commands_[++arg]));
        break;
      case BLUR:
        Blur(std::stof(commands_[++arg]));
        break;
      case SATURATE:
        Saturate(std::stof(commands_[++arg]));
        break;
      case CHANNEL: {
        float red = std::stof(commands_[++arg]);
        float green = std::stof(commands_[++arg]);
        float blue = std::stof(commands_[++arg]);
        Channel(red, green, blue);
        break;
      }
      case COMPARE:
        Compare(input_file_.c_str(), output_file_.c_str());
        return;
      default:
        break;
    }
  }

  ImageHandler::SaveImage(output_file_, output_buffer_);
  return;
}

bool MIACmdManager::ValidInput() {
  for (int cmd = 1; cmd < num_args_; ++cmd) {
    int current_cmd = GetCurrentCmd(commands_[cmd]);
    std::string cmd_str(commands_[cmd]);

    if (cmd > 1 && in_file_set_ == false) {
      err_handler_->NoInputFileError();
      return false;
    }

    // If/Else block to verify commands fit expected context
    // i.e. Sharpen must have a following float, etc.
    if (current_cmd == INVALID) {
      err_handler_->GenericInputError(commands_[cmd]);
      return false;

    } else if (current_cmd == FILE) {
      IOManager* io_mngr = new IOManager();

      if (!in_file_set_) {
        if (io_mngr->is_valid_image_file(cmd_str)) {
          in_file_set_ = true;
          delete io_mngr;
        } else {
          err_handler_->FileDoesNotExistError(commands_[cmd]);
          delete io_mngr;
          return false;
        }
      } else if (!out_file_set_) {
        if (io_mngr->is_valid_image_file_name(cmd_str)) {
          out_file_set_ = true;
          delete io_mngr;
        } else {
          err_handler_->FileInvalidTypeError(commands_[cmd]);
          delete io_mngr;
          return false;
        }
      } else {
        err_handler_->TooManyFileArgsError(commands_[cmd]);
        delete io_mngr;
        return false;
      }

    } else if (current_cmd == HELP) {
      // Return true if '-h' is the first and only arg, false otherwise
      return cmd == 1 && num_args_ == 2;

    } else if (current_cmd == SHARPEN) {
      // If there is no next argument.
      // Also increments cmd, so that it properly references the next cmd
      // which should be a float. cmd will then automatically, properly move
      // on to the next cmd after sharpen has been checked.
      if (++cmd >= num_args_) {
        err_handler_->CommandMissingArgsError(commands_[cmd - 1], flt, 1);
        return false;
      }
      // Check type
      // ptr points to the next char after strtof() finishes reading the float
      // Should never point to a non-space (*ptr != 0)
      char* ptr;
      float sharpen_val = std::strtof(commands_[cmd], &ptr);
      if (*ptr != 0) {
        err_handler_->CommandArgTypeMismatchError(commands_[cmd], flt);
        return false;
      }
      // Check bounds
      if (sharpen_val > 100 || sharpen_val < 0) {
        const char* bounds = "0.0-100.0";
        err_handler_->CommandArgOutOfBoundsError(commands_[cmd], bounds);
        return false;
      }

    } else if (current_cmd == EDGE) {
      // No special context required

    } else if (current_cmd == THRESHOLD) {
      // If there is no next argument.
      if (++cmd >= num_args_) {
        err_handler_->CommandMissingArgsError(commands_[cmd - 1], flt, 1);
        return false;
      }
      // Check type
      char* ptr;
      float threshold_val = std::strtof(commands_[cmd], &ptr);
      if (*ptr != 0) {
        err_handler_->CommandArgTypeMismatchError(commands_[cmd], flt);
        return false;
      }
      // Check bounds
      if (threshold_val > 1 || threshold_val < 0) {
        const char* bounds = "0.0-1.0";
        err_handler_->CommandArgOutOfBoundsError(commands_[cmd], bounds);
        return false;
      }

    } else if (current_cmd == QUANTIZE) {
      // If there is no next argument.
      if (++cmd >= num_args_) {
        err_handler_->CommandMissingArgsError(commands_[cmd - 1], intgr, 1);
        return false;
      }
      // Check type
      char* ptr;
      int quant_val = std::strtol(commands_[cmd], &ptr, 0);
      if (*ptr != 0) {
        err_handler_->CommandArgTypeMismatchError(commands_[cmd], flt);
        return false;
      }
      // Check bounds
      if (quant_val > 256 || quant_val < 2) {
        const char* bounds = "2-256";
        err_handler_->CommandArgOutOfBoundsError(commands_[cmd], bounds);
        return false;
      }

    } else if (current_cmd == BLUR) {
      // If there is no next argument.
      if (++cmd >= num_args_) {
        err_handler_->CommandMissingArgsError(commands_[cmd - 1], flt, 1);
        return false;
      }
      // Check type
      char* ptr;
      float blur_val = std::strtof(commands_[cmd], &ptr);
      if (*ptr != 0) {
        err_handler_->CommandArgTypeMismatchError(commands_[cmd], flt);
        return false;
      }
      // Check bounds
      if (blur_val > 20 || blur_val < 0) {
        const char* bounds = "0.0-20.0";
        err_handler_->CommandArgOutOfBoundsError(commands_[cmd], bounds);
        return false;
      }

    } else if (current_cmd == SATURATE) {
      // If there is no next argument.
      if (++cmd >= num_args_) {
        err_handler_->CommandMissingArgsError(commands_[cmd - 1], flt, 1);
        return false;
      }
      // Check type
      char* ptr;
      float sat_val = std::strtof(commands_[cmd], &ptr);
      if (*ptr != 0) {
        err_handler_->CommandArgTypeMismatchError(commands_[cmd], flt);
        return false;
      }
      // Check bounds
      if (sat_val > 10 || sat_val < -10) {
        const char* bounds = "-10.0-10.0";
        err_handler_->CommandArgOutOfBoundsError(commands_[cmd], bounds);
        return false;
      }

    } else if (current_cmd == CHANNEL) {
      // If there are not 3 more arguments
      cmd += 3;
      if (cmd >= num_args_) {
        err_handler_->CommandMissingArgsError(commands_[cmd - 3], flt, 3);
        return false;
      }
      cmd -= 3;
      // Check type
      int num_channels = 3;
      for (int curr_clr = 0; curr_clr < num_channels; ++curr_clr) {
        char* ptr;
        float color_val = std::strtof(commands_[++cmd], &ptr);
        if (*ptr != 0) {
          err_handler_->CommandArgTypeMismatchError(commands_[cmd], flt);
          return false;
        }
        // Check bounds
        if (color_val > 10 || color_val < 0) {
          const char* bounds = "0.0-10.0";
          err_handler_->CommandArgOutOfBoundsError(commands_[cmd], bounds);
          return false;
        }
      }

    } else if (current_cmd == COMPARE) {
    } else {
      // ERROR!
      return false;
    }
  }
  if (in_file_set_ && !out_file_set_) {
    // No output file
    err_handler_->NoOutputFileError();
    return false;
  }
  return true;
}

int MIACmdManager::GetCurrentCmd(char* cur_cmd) {
  std::string cmd_str(cur_cmd);
  if (cur_cmd[0] != '-') {
    IOManager* io_mngr = new IOManager();

    if (!io_mngr->is_valid_image_file_name(cmd_str)) {
      delete io_mngr;
      return INVALID;
    }
    delete io_mngr;
    return FILE;

  } else {
    int length = cmd_str.size();
    if (length == 1) {
      return INVALID;
    }
    if (cmd_str == "-h") {
      return HELP;
    }
    if (!in_file_set_) {
      return INVALID;
    }
    std::string cmd(cmd_str.substr(1, length - 1));

    // If there is no command 'cmd' in the map, that cmd is invalid
    if (cmd_types_.count(cmd) == 0) {
      return INVALID;
    }

    return cmd_types_[cmd];
  }
}

void MIACmdManager::DisplayHelp() {
  std::cout << "Usage: build/bin/MIA input-file [options] output-file"
            << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << std::setw(32) << std::left << "  -h"
            << "Display this help message" << std::endl;
  std::cout << std::setw(32) << std::left << "  -sharpen <float>"
            << "Sharpen an image by the provided amount" << std::endl;
  std::cout << std::setw(32) << std::left << "  -edge"
            << "Perform edge detection on an image" << std::endl;
  std::cout << std::setw(32) << std::left << "  -threshold <float>"
            << "Round each RGB value up to 1.0 or down "
               "to 0.0 based on the argument"
            << std::endl;
  std::cout << std::setw(32) << std::left << "  -quantize <int>"
            << "Restrict each RGB channel to one of <int> "
               "values between 0 and 1"
            << std::endl;
  std::cout << std::setw(32) << std::left << "  -blur <float>"
            << "Blur an image by the provided amount" << std::endl;
  std::cout << std::setw(32) << std::left << "  -saturate <float>"
            << "Increase, decrease, or invert the "
               "colorfulness of an image"
            << std::endl;
  std::cout << std::setw(32) << std::left
            << "  -channel <float> <float> <float>"
            << " Increase/decrease the "
               "intensity of each color channel (RGB) by a factor of <float>"
            << std::endl;
  std::cout << std::setw(32) << std::left << "  -compare"
            << "Print '1' if the images are equivalent, '0' otherwise"
            << std::endl;
}

// Filter functions
void MIACmdManager::Sharpen(float amount) {
  // std::cout << "Sharpen with amount: " << amount << std::endl;
  Filter* filter_sharpen = FilterFactory::CreateFilter(
      FilterFactory::Filters::FILTER_SHARPEN, 1, amount);
  FilterFactory::ApplyFilter(*filter_sharpen, &output_buffer_);
  delete filter_sharpen;
}

void MIACmdManager::EdgeDetect() {
  // std::cout << "Edge Detect" << std::endl;
  Filter* filter_edge_detect = FilterFactory::CreateFilter(
      FilterFactory::Filters::FILTER_EDGE_DETECT, 0);
  FilterFactory::ApplyFilter(*filter_edge_detect, &output_buffer_);
  delete filter_edge_detect;
}

void MIACmdManager::Threshold(float amount) {
  // std::cout << "Threshold with amount: " << amount << std::endl;
  Filter* filter_threshold = FilterFactory::CreateFilter(
      FilterFactory::Filters::FILTER_THRESHOLD, 1, amount);
  FilterFactory::ApplyFilter(*filter_threshold, &output_buffer_);
  delete filter_threshold;
}

void MIACmdManager::Quantize(int bins) {
  // std::cout << "Quantize with bins: " << bins << std::endl;
  Filter* filter_quantize = FilterFactory::CreateFilter(
      FilterFactory::Filters::FILTER_QUANTIZE, 1, bins);
  FilterFactory::ApplyFilter(*filter_quantize, &output_buffer_);
  delete filter_quantize;
}

void MIACmdManager::Blur(float amount) {
  // std::cout << "Blur with amount: " << amount << std::endl;
  Filter* filter_blur = FilterFactory::CreateFilter(
      FilterFactory::Filters::FILTER_BLUR, 1, amount);
  FilterFactory::ApplyFilter(*filter_blur, &output_buffer_);
  delete filter_blur;
}

void MIACmdManager::Saturate(float amount) {
  // std::cout << "Saturate with amount: " << amount << std::endl;
  Filter* filter_saturate = FilterFactory::CreateFilter(
      FilterFactory::Filters::FILTER_SATURATION, 1, amount);
  FilterFactory::ApplyFilter(*filter_saturate, &output_buffer_);
  delete filter_saturate;
}

void MIACmdManager::Channel(float r, float g, float b) {
  // std::cout << "Channels with RGB: " << r << " " << g << " " << b <<
  // std::endl;
  Filter* filter_channels = FilterFactory::CreateFilter(
      FilterFactory::Filters::FILTER_CHANNELS, 3, r, g, b);
  FilterFactory::ApplyFilter(*filter_channels, &output_buffer_);
  delete filter_channels;
}

// Image handlers
void MIACmdManager::Compare(std::string img1, std::string img2) {
  PixelBuffer* buffer1 = ImageHandler::LoadImage(img1);
  PixelBuffer* buffer2 = ImageHandler::LoadImage(img2);
  int result = *buffer1 == *buffer2;
  std::cout << result << std::endl;
  delete buffer1;
  delete buffer2;
}

// void MIACmdManager::Convert(char* img1, char* img2) {}

} /* namespace image_tools */
