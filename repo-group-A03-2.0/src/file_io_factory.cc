/*******************************************************************************
* Name            : file_io_factory.cc
* Project         : FlashPhoto
* Module          : io_manager
* Description     : Header file for FileReader class.
* Copyright       : 2016 CSCI3081W. All rights reserved.
* Creation Date   : 11/10/16
* Original Author : Natnael Seifu
*
******************************************************************************/

#include "include/file_io_factory.h"
#include "include/file_io.h"
#include "include/png_io.h"
#include "include/jpeg_io.h"

namespace image_tools {

  FileIOFactory::FileIOFactory() {}
  FileIOFactory::~FileIOFactory() {}

  FileIO* FileIOFactory::createFileIO(const std::string& file_name) {
    FileIO* file_io = nullptr;
    const std::string period = ".";
    size_t pos = file_name.find_last_of(period);
    std::string suffix = file_name.substr(pos+1);

    if (suffix == "png") {
      file_io = new PngIO();
    } else if (suffix == "jpg" || suffix == "jpeg") {
      file_io = new JpegIO();
    } else {
      if (file_name.empty()) {
        fprintf(stderr, "Please Enter File name\n");
      } else {
        fprintf(stderr, "File not supported\n");
      }
    }

    return file_io;
  }
}  // namespace image_tools
