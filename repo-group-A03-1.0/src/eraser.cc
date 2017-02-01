/*******************************************************************************
 * Name            : eraser.cc
 * Project         : BrushWork
 * Module          : utils
 * Description     : Implementation of Eraser class
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/17/2016
 * Original Author : Wei Chen
 *
 ******************************************************************************/
#include "include/eraser.h"

#include <cmath>

#include "include/tool.h"
#include "include/color_data.h"
#include "include/pixel_buffer.h"

namespace image_tools {

  Eraser::Eraser() {
    // 3-pixel in diameters
    mask_height_ = 21;
    mask_width_ = 21;

    mask_ = new float* [mask_height_];
    for (int i = 0; i < mask_height_ ; i++) {
      mask_[i] = new float[mask_width_];
    }
    for (int i = 0; i < mask_height_; i++) {
      for (int j = 0; j < mask_width_; j++) {
        if (pow(i - 10, 2) + pow(j - 10, 2) < (10.5 * 10.5)) {
          mask_[i][j] = 1;
        } else {
          mask_[i][j] = 0;
        }
      }
    }
  }

  Eraser::~Eraser() {}

  void Eraser::paint(int x, int y, PixelBuffer* canvas, ColorData curr_color) {
    // top-left coordinates relative to (x,y) on canvas
    int a = x - floor(mask_width_ / 2);
    int b = y - floor(mask_height_ / 2);

    for (int i = 0; i < mask_width_; i ++) {
      for (int j = 0; j < mask_height_; j++) {
        if ((a + i >= 0) && (a + i < canvas->width()) &&
                (b + j >= 0) && (b + j < canvas->height())) {
          ColorData new_color = canvas->get_pixel(a+i, b+j) * (1 - mask_[i][j]);
          new_color = new_color + (canvas->background_color() * mask_[i][j]);
          canvas->set_pixel(a + i, b + j, new_color);
        }
      }
    }
  }
}  // namespace image_tools
