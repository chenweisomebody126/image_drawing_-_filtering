/*******************************************************************************
 * Name            : pen.cc
 * Project         : BrushWork
 * Module          : utils
 * Description     : Implementation of Pen class
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/17/2016
 * Original Author : Natnael Seifu
 *
 ******************************************************************************/
#include "include/pen.h"

#include <cmath>
#include <iostream>

#include "include/tool.h"

namespace image_tools {

  Pen::Pen(int width, int height) : Tool(width, height) {}

  void Pen::intializeMask() {
  float** mask = nullptr;
  float mid_x = getMaskWidth() / 2;
  float mid_y = getMaskHeight() / 2;

    // Allocating memory for mask
    mask = new float*[getMaskHeight()];
    for (int i = 0; i < getMaskHeight(); i++) {
      mask[i] = new float[getMaskWidth()];
    }

    // Initializing allocated mask
    for (int i = 0; i < getMaskHeight(); i++) {
      for (int j = 0; j < getMaskWidth(); j++) {
        if (pow(i - mid_y, 2) + pow(j - mid_x, 2) < (mid_x * mid_y)) {
          mask[i][j] = 1;
        } else {
          mask[i][j] = 0.5;
        }
      }
    }
  setMask(mask);
  }

  /**
   * @Brief we will use parents(Tool) Destructors
   * for deleting child tools. So Implimentation
   * not needed here.
   */
  Pen::~Pen(void) {}
}  // namespace image_tools
