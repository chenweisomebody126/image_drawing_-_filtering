/*******************************************************************************
 * Name            : file_io_factory.h
 * Project         : FlashPhoto
 * Module          : io_manager
 * Description     : Header file for FileReaderFactory class.
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 11/09/16
 * Original Author : Natnael Seifu
 *
 ******************************************************************************/
#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILE_IO_FACTORY_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILE_IO_FACTORY_H_

#include <iostream>
#include <string>
#include "lib/libimgtools/src/include/file_io.h"

namespace image_tools {
/**
 * @brief File IO Factory creates a FileIO Object depending
 * on the extension of the file
 * e.g. if file name is snaily.jpg
 * File IO Factory will create JPEGIO object
 */
class FileIOFactory {
 public:
  FileIOFactory(void);
  virtual ~FileIOFactory(void);
  FileIO* createFileIO(const std::string& file_name);

 protected:
 private:
};
}  // namespace image_tools
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILE_IO_FACTORY_H_
