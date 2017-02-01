/*******************************************************************************
 * Name            : tool.cc
 * Project         : BrushWork
 * Module          : utils
 * Description     : Implementation of Tool class
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/17/2016
 * Original Author : Julina Duan
 *
 ******************************************************************************/
#include "include/tool.h"

#include <iostream>
#include <cmath>

namespace image_tools {

  Tool::Tool() {}

  Tool::~Tool(void) {
    for (int i = 0; i < mask_width_; i++) {
      delete [] mask_[i];
    }
    delete [] mask_;
    std::cout << "Mask deleted" << std::endl;
  }

  /**
   * @Brief when tool moves fast there will be gaps between each mask
   *        drawn. This function fills in that gap.
   */
  void Tool::fill(int x, int y , int prev_x, int prev_y,
                  PixelBuffer* canvas, ColorData curr_color) {
    float slope;
    float intercept;

    int sign_x;
    int sign_y;
    int FILL_GAP = 1;

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

  // @Brief draws a single print of mask
  void Tool::paint(int x, int y, PixelBuffer* canvas, ColorData curr_color) {
    int a = x - floor(mask_width_/2);
    int b = y - floor(mask_height_/2);

    for (int i = 0; i < mask_width_; i ++) {
      for (int j = 0; j < mask_height_; j++) {
        if ((a + i >= 0) && (a + i < canvas->width()) &&
            (b + j >= 0) && (b + j < canvas->height())) {
              ColorData new_color = (canvas->get_pixel(a + i, b + j)
                * (1 - mask_[j][i])) + (curr_color * mask_[j][i]);
              canvas->set_pixel(a + i, b + j, new_color);
          }
        }
      }
    }
}  // namespace image_tools
