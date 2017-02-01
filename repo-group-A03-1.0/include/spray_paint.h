/*******************************************************************************
 * Name            : spray_paint.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for SprayPaint class.
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/16/16
 * Original Author : Natnael Seifu
 *
 ******************************************************************************/
#ifndef INCLUDE_SPRAY_PAINT_H_
#define INCLUDE_SPRAY_PAINT_H_

#include "include/spray_paint.h"
#include <iostream>
#include "include/tool.h"

namespace image_tools {

class SprayPaint : public Tool {
 public:
  SprayPaint();
  virtual ~SprayPaint(void);
  void fill(int x, int y, int prev_x, int prev_y,
    PixelBuffer* canvas, ColorData curr_color);
 protected:
 private:
  float calc_distance(float x, float y, float x_, float y_);
};
}  // namespace image_tools

#endif  // INCLUDE_SPRAY_PAINT_H_
