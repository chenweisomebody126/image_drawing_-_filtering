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
#include "lib/libimgtools/src/include/tool.h"

#include <iostream>
#include <cmath>

namespace image_tools {

Tool::Tool(int width, int height) {
  mask_width_ = width;
  mask_height_ = height;
}

Tool::~Tool(void) {
  for (int i = 0; i < mask_width_; i++) {
    delete [] mask_[i];
  }
  delete [] mask_;
  std::cout << "Mask deleted" << std::endl;
}

void Tool::fill(int x, int y , int prev_x, int prev_y,
                PixelBuffer* canvas, ColorData curr_color) {
  // Fill function will not fill for tools
  // that don't need them
  if (mask_ == nullptr) {
    return;
  }

  float slope;
  float intercept;

  int sign_x;
  int sign_y;
  int FILL_GAP = 1;
  float OPACITY_LEVEL = 1;

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
      new_x += (sign_x * FILL_GAP);
      new_y = (slope * new_x) + intercept;
      paint(new_x, (canvas->height() - new_y),
            canvas, curr_color, OPACITY_LEVEL);
    }
  } else {
    for (int i = 0; i < num_steps_y; i++) {
      new_y += (sign_y * FILL_GAP);
      if (std::isfinite(slope)) {
        new_x = (new_y - intercept) / slope;
      }
      paint(new_x, canvas->height()-new_y, canvas, curr_color, OPACITY_LEVEL);
    }
  }
}

void Tool::paint(int x, int y, PixelBuffer* canvas,
                 ColorData curr_color, int opa_lvl) {
  float slimmed_mask;
  int a = x - floor(mask_width_/2);
  int b = y - floor(mask_height_/2);

  for (int i = 0; i < mask_width_; i ++) {
    for (int j = 0; j < mask_height_; j++) {
      if ((a + i >= 0) && (a + i < canvas->width()) &&
          (b + j >= 0) && (b + j < canvas->height())) {
        slimmed_mask = powf(mask_[j][i], opa_lvl);
        ColorData new_color = (canvas->get_pixel(a + i, b + j)
            * (1 - slimmed_mask) + (curr_color * slimmed_mask));
        canvas->set_pixel(a + i, b + j, new_color);
      }
    }
  }
}
}  // namespace image_tools
