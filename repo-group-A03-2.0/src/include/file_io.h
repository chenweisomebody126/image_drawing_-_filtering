/*******************************************************************************
 * Name            : file_io.h
 * Project         : FlashPhoto
 * Module          : io_manager
 * Description     : Header file for FileReader class.
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 11/09/16
 * Original Author : Natnael Seifu
 *
 ******************************************************************************/
#ifndef SRC_INCLUDE_FILE_IO_H_
#define SRC_INCLUDE_FILE_IO_H_

#include <string>
#include <iostream>
#include "include/pixel_buffer.h"

namespace image_tools {
class FileIO {
 public:
  FileIO(void);
  virtual ~FileIO(void);
  virtual PixelBuffer* readFile(const std::string& file_name) = 0;
  virtual void saveToFile(const std::string& file_name,
                       const PixelBuffer* curr_canvas) = 0;

 protected:
 private:
};
}  // namespace image_tools
#endif  // SRC_INCLUDE_FILE_IO_H_
