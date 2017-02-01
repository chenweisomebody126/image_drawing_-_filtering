/*******************************************************************************
 * Name            : eraser.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for Eraser class
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/16/2016
 * Original Author : Wei Chen
 *
 ******************************************************************************/
#ifndef SRC_INCLUDE_ERASER_H_
#define SRC_INCLUDE_ERASER_H_

#include "include/tool.h"

namespace image_tools {

class Eraser : public Tool {
 public:
  Eraser(int width, int height);
  virtual ~Eraser();
  void intializeMask();
  void paint(int x, int y, PixelBuffer* canvas,
    ColorData curr_color, int opa_lvl);

 protected:
 private:
};
}  // namespace image_tools
#endif  // SRC_INCLUDE_ERASER_H_
