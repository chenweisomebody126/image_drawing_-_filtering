/*******************************************************************************
> * Name            : mia_command.h
 * Project         : MIA
 * Module          : App
 * Description     : Header file for MIA class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 5/15/15
 * Original Author : Natnael Seifu
 *
 ******************************************************************************/

#ifndef SRC_APP_MIA_SRC_INCLUDE_MIA_COMMAND_H
#define SRC_APP_MIA_SRC_INCLUDE_MIA_COMMAND_H

#include <iostream>
#include <getopt.h>
#include "app/MIA/src/include/mia_io_manager.h"
#include "app/MIA/src/include/mia_filter_manager.h"

namespace image_tools {
/**
 * @brief This is a application class for Medical Images Command Line Mode.
 */
class MiaCommand {
 public:
  MiaCommand(int argc, char** argv);
  virtual ~MiaCommand();

  /**
   * @brief Parse and Execute string from command line
   */
  void executeCmd(void);

  /**
   * @brief If --h flag is set or arguments are invalid, this function will
   * print help message to console
   */
  inline void showHelpMessage(void) {
    std::cout << "" << std::endl;
    std::cout << "Usage: %s [input_image] [arg_1] [arg_2] ...";
    std::cout << "[output_image]" << std::endl;

    std::cout << "Both [input_image] and [output_image]";
    std::cout << "are required arguments" << std::endl;

    std::cout << "All [arg]'s are optional" << std::endl;
    std::cout << "Arguments Infomation:" << std::endl;
    std::cout << "-h: display help message" << std::endl;
    std::cout << "-sharpen <float>: sharpen an image by amount" << std::endl;
    std::cout << "-edge: detect the edge of an image" << std::endl;

    std::cout << "-thredhold <float>: adjust the thredhold";
    std::cout << "of an image by amount" << std::endl;

    std::cout << "-quantize <int>: adjust the quantize";
    std::cout << "of an image by amount" << std::endl;

    std::cout << "-blur <float>: blur an image by amount" << std::endl;
    std::cout << "-blur <float>: adjust the saturate of";
    std::cout << "an image by amount" << std::endl;

    std::cout << "-saturate <float>: adjust the";
    std::cout << "saturate of an image by amount" << std::endl;
    std::cout << "-channel <float> <float> <float>:";

    std::cout << "adjust the channel of an image by amount" << std::endl;
    std::cout << "-compare: compare input and output images" << std::endl;
    std::cout << "" << std::endl;
  }

 protected:
  inline void set_arg_count(int argc) { args_count_ = argc;}
  inline void set_arguments(char** argv) { cmd_args_ = argv;}

 private:
  int flag;
  int args_count_;
  char** cmd_args_;
  PixelBuffer* image_buffer_;
  MIAFilterManager f_manager_;
  MIAIOManager io_manager_;
  const char * short_option_ = "";
  struct option long_options_[10] = {
      {"sharpen", required_argument, 0, 's'},
      {"edge", no_argument, 0, 'e'},
      {"thredhold", required_argument, 0, 't'},
      {"quantize", required_argument, 0, 'q'},
      {"blur", required_argument, 0, 'b'},
      {"saturate", required_argument, 0, 'a'},
      {"channel", required_argument, 0, 'c'},
      {"compare", no_argument, 0, 'p'},
      {"h", no_argument, 0, 'h'},
      {0, 0, 0, 0}
  };
};
}  // namespace image_tools
#endif  // SRC_APP_MIA_SRC_INCLUDE_MIA_COMMAND_H_
