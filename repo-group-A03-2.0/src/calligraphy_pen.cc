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

  CalligraphyPen::CalligraphyPen(int width, int height) : Tool(width, height) {}

  void CalligraphyPen::intializeMask() {
    float** mask = nullptr;
    mask = new float*[getMaskHeight()];
    for (int i = 0; i < getMaskHeight(); i++) {
      mask[i] = new float[getMaskWidth()];
    }

    // Initializing allocated mask
    for (int i = 0; i < getMaskHeight(); i++) {
      for (int j = 0; j < getMaskWidth(); j++) {
        mask[i][j] = 1;
      }
    }
    setMask(mask);
  }

  CalligraphyPen::~CalligraphyPen() {}
}  // namespace image_tools
