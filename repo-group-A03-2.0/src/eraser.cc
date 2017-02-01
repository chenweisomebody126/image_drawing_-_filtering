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

  Eraser::Eraser(int width, int height) : Tool(width, height) {
    intializeMask();
  }

  void Eraser::intializeMask() {
  float** mask = nullptr;
  float mid_x = getMaskWidth() / 2;
  float mid_y = getMaskHeight() / 2;

  mask = new float* [getMaskHeight()];
    for (int i = 0; i < getMaskHeight() ; i++) {
      mask[i] = new float[getMaskWidth()];
    }
    for (int i = 0; i < getMaskHeight(); i++) {
      for (int j = 0; j < getMaskWidth(); j++) {
        if (pow(i - mid_y, 2) + pow(j - mid_x, 2) < (mid_x * mid_y)) {
          mask[i][j] = 1;
        } else {
          mask[i][j] = 0;
        }
      }
    }
  setMask(mask);
  }

  Eraser::~Eraser() {}

  void Eraser::paint(int x, int y, PixelBuffer* canvas,
                     ColorData curr_color, int opa_lvl) {
    float slimmed_mask;
    int a = x - floor(getMaskWidth() / 2);
    int b = y - floor(getMaskHeight() / 2);

    for (int i = 0; i < getMaskWidth(); i ++) {
      for (int j = 0; j < getMaskHeight(); j++) {
        if ((a + i >= 0) && (a + i < canvas->width()) &&
            (b + j >= 0) && (b + j < canvas->height())) {
          slimmed_mask = powf(maskValueAt(j, i), opa_lvl);
          canvas->set_pixel(a + i, b + j, canvas->background_color());
        }
      }
    }
  }
}  // namespace image_tools
