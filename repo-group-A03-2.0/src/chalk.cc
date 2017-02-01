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

  Chalk::Chalk(int width, int height) : Tool(width, height) {}

  void Chalk::intializeMask() {
  float** mask = nullptr;
  mask = new float*[getMaskHeight()];
    for (int i = 0; i < getMaskHeight(); i++) {
      mask[i] = new float[getMaskWidth()];
    }

    /** seed value for rand_r function */
    unsigned int chalk_seed = 0;
  float mid_x = getMaskWidth() / 2;
  float mid_y = getMaskHeight() / 2;

    for (int i = 0; i < getMaskHeight(); i++) {
      for (int j = 0; j < getMaskWidth(); j++) {
        rand_r(&chalk_seed);
        if (pow(i-mid_y, 2) + pow(j-mid_x, 2) < (mid_x * mid_y)) {
          mask[i][j] =  (static_cast<float>(chalk_seed) / RAND_MAX) * 0.05;
        } else {
          mask[i][j] = (static_cast<float>(chalk_seed) / RAND_MAX) * 0.01;
        }
      }
    }
  setMask(mask);
  }

  Chalk::~Chalk() {}
}  // namespace image_tools
