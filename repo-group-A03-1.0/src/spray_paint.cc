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

  SprayPaint::SprayPaint() : Tool() {
      mask_width_ = 41;
      mask_height_ = 41;

      float opacity = 0.1;

      // Allocating memory for mask
      mask_ = new float*[mask_height_];
      for (int i = 0; i < mask_height_; i++) {
        mask_[i] = new float[mask_width_];
      }

      for (int i = 0; i < mask_width_; i++) {
        for (int j = 0; j < mask_height_; j++) {
          float distance = calc_distance(static_cast<float>(i),
                                         static_cast<float>(j), 20.0, 20.0);
          if (distance >= 20.0) {
            mask_[i][j] = 0.0;
          } else {
            mask_[i][j] = opacity - ((opacity / 20.0) *
              calc_distance(static_cast<float>(i),
                static_cast<float>(j), 20.0, 20.0));
          }
        }
      }
  }

  void SprayPaint::fill(int x, int y , int prev_x, int prev_y,
                        PixelBuffer* canvas, ColorData curr_color) {
    float slope;
    float intercept;

    int sign_x;
    int sign_y;
    int FILL_GAP = 2;

    if (x < prev_x) {
      sign_x = -1;
    } else {
      sign_x = 1;
    }

    if (y < prev_y) {
      sign_y = -1;
    } else {
      sign_y = 1;
    }

    float horizontal_dist = static_cast<float>(x - prev_x);
    float vertical_dist = static_cast<float>(y - prev_y);

    slope = vertical_dist / horizontal_dist;
    intercept = y - (slope * x);

    int num_steps_x = abs(horizontal_dist / FILL_GAP);
    int num_steps_y = abs(vertical_dist / FILL_GAP);

    int new_x = prev_x;
    int new_y = prev_y;

    if (num_steps_x >= num_steps_y) {
      for (int i = 0; i < num_steps_x; i++) {
        paint(new_x, canvas->height()-new_y, canvas, curr_color);
        new_x += (sign_x * FILL_GAP);
        new_y = (slope * new_x) + intercept;
      }
    } else {
      for (int i = 0; i < num_steps_y; i++) {
        paint(new_x, canvas->height()-new_y, canvas, curr_color);
        new_y += (sign_y * FILL_GAP);
        if (std::isfinite(slope)) {
          new_x = (new_y - intercept) / slope;
        }
      }
    }
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
