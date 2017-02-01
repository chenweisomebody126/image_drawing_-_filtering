/*******************************************************************************
 * Name            : highlighter.cc
 * Project         : BrushWork
 * Module          : utils
 * Description     : Implementation of Highlighter class
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/17/2016
 * Original Author : Julina Duan
 *
 ******************************************************************************/
#include "include/highlighter.h"
#include <cmath>
#include <iostream>
namespace image_tools {

  Highlighter::Highlighter(int width, int height) : Tool(width, height) {}

  void Highlighter::intializeMask() {
    float** mask = nullptr;
    mask = new float*[getMaskHeight()];
    for (int i = 0; i < getMaskHeight(); i++) {
      mask[i] = new float[getMaskWidth()];
    }

    // Initializing allocated mask
    for (int i = 0; i < getMaskHeight(); i++) {
      for (int j = 0; j < getMaskWidth(); j++) {
        mask[i][j] = 0.4;
      }
    }
    setMask(mask);
  }

  Highlighter::~Highlighter() {}
}  // namespace image_tools
