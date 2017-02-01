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

#include <iostream>

#include "include/tool.h"

namespace image_tools {

  Pen::Pen() : Tool() {
    mask_width_ = 3;
    mask_height_ = 3;

    // Hard Coded Values for Initializing Mask
    float mask_initializer[mask_width_][mask_height_] = {{0.5, 1.0, 0.5},
                                                         {1.0, 1.0, 1.0},
                                                         {0.5, 1.0, 0.5}};
    // Allocating memory for mask
    mask_ = new float*[mask_height_];
    for (int i = 0; i < mask_height_; i++) {
      mask_[i] = new float[mask_width_];
    }

    // Initializing allocated mask
    for (int i = 0; i < mask_height_; i++) {
      for (int j = 0; j < mask_width_; j++) {
        mask_[i][j] = mask_initializer[i][j];
      }
    }
  }

  /**
   * @Brief we will use parents(Tool) Destructors
   * for deleting child tools. So Implimentation
   * not needed here.
   */
  Pen::~Pen(void) {}
}  // namespace image_tools
