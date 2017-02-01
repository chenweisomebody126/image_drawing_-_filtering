/*******************************************************************************
 * Name            : calligraphy_pen.cc
 * Project         : BrushWork
 * Module          : utils
 * Description     : Implementation of CalligraphyPen class
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/17/2016
 * Original Author : Julina Duan
 *
 ******************************************************************************/
#include "include/calligraphy_pen.h"

namespace image_tools {

  CalligraphyPen::CalligraphyPen() {
    // 15 pixels * 5 pixels mask with opacity 1
    mask_height_ = 15;
    mask_width_ = 5;

    mask_ = new float*[mask_height_];
    for (int i = 0; i < mask_height_; i++) {
      mask_[i] = new float[mask_width_];
    }

    // Initializing allocated mask
    for (int i = 0; i < mask_height_; i++) {
      for (int j = 0; j < mask_width_; j++) {
        mask_[i][j] = 1;
      }
    }
  }

  CalligraphyPen::~CalligraphyPen() {}
}  // namespace image_tools
