/*******************************************************************************
 * Name            : chalk.cc
 * Project         : BrushWork
 * Module          : utils
 * Description     : Implementation of Chalk class
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/17/2016
 * Original Author : Wei Chen
 *
 ******************************************************************************/
#include "include/chalk.h"

#include <cmath>
#include <iostream>

namespace image_tools {

  Chalk::Chalk() {
    // 3-pixel in diameters
    mask_height_ = 21;
    mask_width_ = 21;

    mask_ = new float*[mask_height_];
    for (int i = 0; i < mask_height_; i++) {
      mask_[i] = new float[mask_width_];
    }

    /** seed value for rand_r function */
    unsigned int chalk_seed;

    for (int i = 0; i < mask_height_; i++) {
      for (int j = 0; j < mask_width_; j++) {
        rand_r(&chalk_seed);
        if (pow(i-10, 2) + pow(j-10, 2) < (10.5 * 10.5)) {
          mask_[i][j] =  (static_cast<float>(chalk_seed) / RAND_MAX) * 0.05;
        } else {
          mask_[i][j] = (static_cast<float>(chalk_seed) / RAND_MAX) * 0.01;
        }
      }
    }
  }

  Chalk::~Chalk() {}
}  // namespace image_tools
