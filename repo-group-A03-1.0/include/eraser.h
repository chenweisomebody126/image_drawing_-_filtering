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
#ifndef INCLUDE_ERASER_H_
#define INCLUDE_ERASER_H_

#include "include/tool.h"

namespace image_tools {

class Eraser : public Tool {
 public:
  Eraser();
  virtual ~Eraser();
  void paint(int x, int y, PixelBuffer* canvas, ColorData curr_color);
};
}  // namespace image_tools
#endif  // INCLUDE_ERASER_H_
