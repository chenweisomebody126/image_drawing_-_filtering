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
#ifndef SRC_INCLUDE_FILE_IO_FACTORY_H_
#define SRC_INCLUDE_FILE_IO_FACTORY_H_

#include <iostream>
#include <string>
#include "include/file_io.h"

namespace image_tools {
class FileIOFactory {
 public:
  FileIOFactory(void);
  virtual ~FileIOFactory(void);
  FileIO* createFileIO(const std::string& file_name);

 protected:
 private:
};
}  // namespace image_tools
#endif  // SRC_INCLUDE_FILE_IO_FACTORY_H_
