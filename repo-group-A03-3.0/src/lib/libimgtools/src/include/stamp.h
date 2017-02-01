/*******************************************************************************
 * Name            : stamp.h
 * Project         : FlashPhoto
 * Module          : Stamp
 * Description     : Header file for Stamp class
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 11/14/2016
 * Original Author : Xinran Duan
 *
 ******************************************************************************/
#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_STAMP_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_STAMP_H_

#include <iostream>
#include "lib/libimgtools/src/include/tool.h"

namespace image_tools {

/**
 * @brief This tool simulates the usage of a rubber stamp.
 * It has a mask that will be loaded from a picture file.
 * Before a stamp is loaded, using stamp will do nothing.
 * Stamp will not overrides the paint function.
 */
class Stamp : public Tool {
 public:
  Stamp(int width, int height);
  virtual ~Stamp(void);

 /**
  * @brief This function will do nothing if a stamp is not loaded yet.
  */
  void intializeMask();

 /**
  * @brief This function will load a mask to stamp tool from a picture.
  */
  void loadStampFromFile(PixelBuffer* image);
  inline void setStampBuffer(PixelBuffer* buffer) {stamp_buffer_ = buffer;}
  inline PixelBuffer* getStampBuffer() {return stamp_buffer_;}
  void paint(int x, int y, PixelBuffer* canvas,
    ColorData curr_color, int opa_lvl);
 protected:
 private:
  PixelBuffer* stamp_buffer_;
};
}  // namespace image_tools
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_STAMP_H_
