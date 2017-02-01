/*******************************************************************************
* Name            : png_io.h
* Project         : FlashPhoto
* Module          : io_manager
* Description     : Header file for FileReader class.
* Copyright       : 2016 CSCI3081W. All rights reserved.
* Creation Date   : 11/10/16
* Original Author : Natnael Seifu
*
******************************************************************************/
#ifndef SRC_INCLUDE_PNG_IO_H_
#define SRC_INCLUDE_PNG_IO_H_

#include <string>
#include "include/file_io.h"
#include "include/pixel_buffer.h"

namespace image_tools {
class PngIO : public FileIO {
 public:
  PngIO(void);
  virtual ~PngIO(void);
  PixelBuffer* readFile(const std::string& file_name);
  void saveToFile(const std::string& file_name,
    const PixelBuffer* curr_canvas);

 protected:
 private:
};
}  // namespace image_tools
#endif  // SRC_INCLUDE_PNG_IO_H_
