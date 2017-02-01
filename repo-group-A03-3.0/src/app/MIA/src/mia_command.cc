/*******************************************************************************
> * Name            : mia_command.cc
 * Project         : MIA
 * Module          : App
 * Description     : Header file for MIA class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 12/14/16
 * Original Author : Natnael Seifu, Dawei Luo
 *
 ******************************************************************************/
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <iostream>
#include "app/MIA/src/include/mia_io_manager.h"
#include "app/MIA/src/include/mia_filter_manager.h"
#include "app/MIA/src/include/mia_command.h"

namespace image_tools {

MiaCommand::MiaCommand(int argc, char** argv)
    : io_manager_(),
      f_manager_() {
  set_arg_count(argc);
  set_arguments(argv);
}

MiaCommand::~MiaCommand(void) {
}

void MiaCommand::executeCmd() {
    /**
     * Image to be processed
     */
    std::string image_file = cmd_args_[1];
    std::string output_file_name = cmd_args_[args_count_ - 1];
    PixelBuffer* image_buffer_ = io_manager_.LoadImageToCanvas(image_file);
    if (image_buffer_ == nullptr && cmd_args_[1][0] != '-') {
      std::cout << "Error Opening File: " << image_file <<std::endl;
      exit(1);
    }

    int option_index = 0;

    while ((flag = getopt_long_only(args_count_, cmd_args_,
            short_option_, long_options_, &option_index)) != -1) {

  			switch (flag) {
  			case 's':
  				// -sharpen <float>
          std::cout << "option -sharpen with value " << optarg << ".\n";
          f_manager_.set_sharpen(atoi(optarg));
          f_manager_.ApplySharpen(image_buffer_);
          if (io_manager_.has_next_image()){
            io_manager_.SaveCanvasToFile(image_buffer_, output_file_name);
            while(io_manager_.has_next_image()){
              image_buffer_ = io_manager_.LoadImageToCanvas(io_manager_.next_file_name());
              f_manager_.ApplySharpen(image_buffer_);
              output_file_name = io_manager_.image_name_plus_seq_offset(output_file_name, 1);
              io_manager_.SaveCanvasToFile(image_buffer_, output_file_name);
            }
            image_file = io_manager_.start_file_name();
            output_file_name = io_manager_.start_file_name();
            image_buffer_ = io_manager_.LoadImageToCanvas(image_file);
          }
  				break;
  			case 'e':
  				// -edge
          std::cout << "option -edge" << optarg << ".\n";
          f_manager_.ApplyEdgeDetect(image_buffer_);
          if (io_manager_.has_next_image()){
            io_manager_.SaveCanvasToFile(image_buffer_, output_file_name);
            while(io_manager_.has_next_image()){
              image_buffer_ = io_manager_.LoadImageToCanvas(io_manager_.next_file_name());
              f_manager_.ApplyEdgeDetect(image_buffer_);
              output_file_name = io_manager_.image_name_plus_seq_offset(output_file_name, 1);
              io_manager_.SaveCanvasToFile(image_buffer_, output_file_name);
            }
            image_file = io_manager_.start_file_name();
            output_file_name = io_manager_.start_file_name();
            image_buffer_ = io_manager_.LoadImageToCanvas(image_file);
          }
  				break;
  			case 't':
  				// -threhold <float>
          std::cout << "option -threhold with value " << optarg << ".\n";
          f_manager_.set_threshold(atoi(optarg));
          f_manager_.ApplyThreshold(image_buffer_);
          if (io_manager_.has_next_image()){
            io_manager_.SaveCanvasToFile(image_buffer_, output_file_name);
            while(io_manager_.has_next_image()){
              image_buffer_ = io_manager_.LoadImageToCanvas(io_manager_.next_file_name());
              f_manager_.ApplyThreshold(image_buffer_);
              output_file_name = io_manager_.image_name_plus_seq_offset(output_file_name, 1);
              io_manager_.SaveCanvasToFile(image_buffer_, output_file_name);
            }
            image_file = io_manager_.start_file_name();
            output_file_name = io_manager_.start_file_name();
            image_buffer_ = io_manager_.LoadImageToCanvas(image_file);
          }
  				break;
  			case 'q':
  				// -quantize <int>
          std::cout << "option -quantize with value " << optarg << ".\n";
          f_manager_.set_quantize_bins(atoi(optarg));
          f_manager_.ApplyQuantize(image_buffer_);
          if (io_manager_.has_next_image()){
            io_manager_.SaveCanvasToFile(image_buffer_, output_file_name);
            while(io_manager_.has_next_image()){
              image_buffer_ = io_manager_.LoadImageToCanvas(io_manager_.next_file_name());
              f_manager_.ApplyQuantize(image_buffer_);
              output_file_name = io_manager_.image_name_plus_seq_offset(output_file_name, 1);
              io_manager_.SaveCanvasToFile(image_buffer_, output_file_name);
            }
            image_file = io_manager_.start_file_name();
            output_file_name = io_manager_.start_file_name();
            image_buffer_ = io_manager_.LoadImageToCanvas(image_file);
          }
  				break;
  			case 'b':
  				// -blur <float>
          std::cout << "option -blur with value " << optarg << ".\n";
          f_manager_.set_blur(atoi(optarg));
          f_manager_.ApplyBlur(image_buffer_);
          if (io_manager_.has_next_image()){
            io_manager_.SaveCanvasToFile(image_buffer_, output_file_name);
            while(io_manager_.has_next_image()){
              image_buffer_ = io_manager_.LoadImageToCanvas(io_manager_.next_file_name());
              f_manager_.ApplyBlur(image_buffer_);
              output_file_name = io_manager_.image_name_plus_seq_offset(output_file_name, 1);
              io_manager_.SaveCanvasToFile(image_buffer_, output_file_name);
            }
            image_file = io_manager_.start_file_name();
            output_file_name = io_manager_.start_file_name();
            image_buffer_ = io_manager_.LoadImageToCanvas(image_file);
          }
  				break;
  			case 'a':
  				// -saturate <float>
          std::cout << "option -saturate with value " << optarg << ".\n";
          f_manager_.set_saturate(atoi(optarg));
          f_manager_.ApplySaturate(image_buffer_);
          if (io_manager_.has_next_image()){
            io_manager_.SaveCanvasToFile(image_buffer_, output_file_name);
            while(io_manager_.has_next_image()){
              image_buffer_ = io_manager_.LoadImageToCanvas(io_manager_.next_file_name());
              f_manager_.ApplySaturate(image_buffer_);
              output_file_name = io_manager_.image_name_plus_seq_offset(output_file_name, 1);
              io_manager_.SaveCanvasToFile(image_buffer_, output_file_name);
            }
            image_file = io_manager_.start_file_name();
            output_file_name = io_manager_.start_file_name();
            image_buffer_ = io_manager_.LoadImageToCanvas(image_file);
          }
  				break;
  			case 'c':{
  				// -channel <float> <float> <float>
          int red;
          int green;
          int blue;

          std::cout << "option -channel with value " << cmd_args_[optind - 1]
                                                     << cmd_args_[optind]
                                                     << cmd_args_[optind + 1]
                                                     << ".\n";
          red = atoi(cmd_args_[optind - 1]);
          green = atoi(cmd_args_[optind]);
          blue = atoi(cmd_args_[optind + 1]);

          f_manager_.set_channel_color(red, green, blue);
          f_manager_.ApplyChannel(image_buffer_);
          if (io_manager_.has_next_image()){
            io_manager_.SaveCanvasToFile(image_buffer_, output_file_name);
            while(io_manager_.has_next_image()){
              image_buffer_ = io_manager_.LoadImageToCanvas(io_manager_.next_file_name());
              f_manager_.ApplyChannel(image_buffer_);
              output_file_name = io_manager_.image_name_plus_seq_offset(output_file_name, 1);
              io_manager_.SaveCanvasToFile(image_buffer_, output_file_name);
            }
            image_file = io_manager_.start_file_name();
            output_file_name = io_manager_.start_file_name();
            image_buffer_ = io_manager_.LoadImageToCanvas(image_file);
          }
  				break;
        }
  			case 'p':{
  				// -compare
  				// do something
          std::cout << "option -compare with file" << cmd_args_[optind] << ".\n";
          PixelBuffer* image2 = io_manager_.LoadImageToCanvas(output_file_name);
          std::cout << (*image_buffer_ == *image2) << std::endl;
          return;
  				break;
        }
  			case 'h':
  				// -h
  			default:
  				// invalid arguments or -h
  				// show argument help message
  				showHelpMessage();
  				exit(1);
      }
	  }

if (optind < args_count_ && image_file != output_file_name){
  std::cout << output_file_name << " will be save " << std::endl;
  io_manager_.SaveCanvasToFile(image_buffer_, output_file_name);
  if (io_manager_.has_next_image()){
    io_manager_.SaveCanvasToFile(image_buffer_, output_file_name);
    while(io_manager_.has_next_image()){
      image_buffer_ = io_manager_.LoadImageToCanvas(io_manager_.next_file_name());
      output_file_name = io_manager_.image_name_plus_seq_offset(output_file_name, 1);
      io_manager_.SaveCanvasToFile(image_buffer_, output_file_name);
    }
    image_file = io_manager_.start_file_name();
    output_file_name = io_manager_.start_file_name();
    image_buffer_ = io_manager_.LoadImageToCanvas(image_file);
  }
} else if (image_file == output_file_name){
  return;
} else {
  std::cout << "Invalid output file format!" << std::endl;
}
  }
}  // namespace image_tools
