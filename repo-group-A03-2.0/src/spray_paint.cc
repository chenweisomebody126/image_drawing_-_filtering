/*******************************************************************************
 * Name            : spray_paint.cc
 * Project         : BrushWork
 * Module          : utils
 * Description     : Implementation of SprayPaint class
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/17/2016
 * Original Author : Natnael Seifu
 *
 ******************************************************************************/
#include "include/spray_paint.h"

#include <cmath>
#include <iostream>

#include "include/tool.h"
#include "include/color_data.h"
#include "include/pixel_buffer.h"

namespace image_tools {

  SprayPaint::SprayPaint(int width, int height) : Tool(width, height) {}

  void SprayPaint::intializeMask() {
  float** mask = nullptr;
  float opacity = 0.1;
  float mid_x = getMaskWidth() / 2;
  float mid_y = getMaskHeight() / 2;

      // Allocating memory for mask
      mask = new float*[getMaskHeight()];
      for (int i = 0; i < getMaskHeight(); i++) {
        mask[i] = new float[getMaskWidth()];
      }

      for (int i = 0; i < getMaskWidth(); i++) {
        for (int j = 0; j < getMaskHeight(); j++) {
          float distance = calc_distance(static_cast<float>(i),
                                         static_cast<float>(j), mid_x, mid_y);
          if (distance >= mid_x) {
            mask[i][j] = 0.0;
          } else {
            mask[i][j] = opacity - ((opacity / mid_x) *
              calc_distance(static_cast<float>(i),
                   static_cast<float>(j), mid_x, mid_y));
          }
        }
      }

  setMask(mask);
  }

  float SprayPaint::calc_distance(float x, float y, float x_, float y_) {
    float distance = 0;
    float a = pow((y_ - y), 2.0);
    float b = pow((x_ - x), 2.0);

    distance = sqrt(a + b);
    return distance;
  }

  /**
   * @Brief we will use parents(Tool) Destructors
   * for deleting child tools. So Implimentation
   * not needed here.
   */
  SprayPaint::~SprayPaint(void) {}
}  // namespace image_tools
