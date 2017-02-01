/*******************************************************************************
 * Name            : blur_tool.cc
 * Project         : FlashPhoto
 * Module          : utils
 * Description     : Implementation of Blur Tool class
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 11/07/2016
 * Original Author : Julina Duan
 *
 ******************************************************************************/
#include <cmath>
#include <iostream>
#include "include/blur_tool.h"
#include "include/tool.h"
#include "include/color_data.h"
#include "include/pixel_buffer.h"
#include "include/kernel.h"
#include "include/k_cross.h"

namespace image_tools {

  BlurTool::BlurTool(int width, int height) : Tool(width, height) {}

  BlurTool::~BlurTool(void) {}

  void BlurTool::intializeMask() {
    float** mask = nullptr;
    float opacity = 10;
    float mid_x = getMaskWidth() / 2;
    float mid_y = getMaskHeight() / 2;

    // Allocating memory for mask
    mask = new float*[getMaskHeight()];
    for (int p = 0; p < getMaskHeight(); p++) {
      mask[p] = new float[getMaskWidth()];
    }

    // Generate a mask with linear falloff
    for (int i = 0; i < getMaskWidth(); i++) {
      for (int j = 0; j < getMaskHeight(); j++) {
        float distance = calc_distance(static_cast<float>(i),
         static_cast<float>(j), mid_x, mid_y);
        if (distance > mid_x) {
          mask[i][j] = 0.0;
        } else {
          mask[i][j] = opacity - (opacity / mid_x) * distance;
        }
      }
    }
    setMask(mask);
  }

  float BlurTool::calc_distance(float x, float y, float x_, float y_) {
    float distance = 0;
    // Use the Pythagorean Theorem to calculate distance
    // between (x,y) and (x_, y_)
    float a = pow((y_ - y), 2.0);
    float b = pow((x_ - x), 2.0);
    distance = sqrt(a + b);
    return distance;
  }

  /**
   * @brief The paint() of blur tool is written to perform its
   * special functionality. Blurring is implemented by convolving
   * a small kernel with the pixels (within mask) in the image.
   */
  void BlurTool::paint(int x, int y, PixelBuffer* canvas,
   ColorData curr_color, int opa_lvl) {
    std::cout << "******CALLING BLURTOOL PAINT.******" << std::endl;
    PixelBuffer temp_buffer = *canvas;
    int a = x - floor(getMaskWidth()/2);
    int b = y - floor(getMaskHeight()/2);

    // loop every pixel within mask
    for (int i = 0; i < getMaskWidth(); i ++) {
      for (int j = 0; j < getMaskHeight(); j++) {
        Kernel *blur_kernel = new KCross(maskValueAt(i, j));
        int cor_x = a + i;
        int cor_y = b + j;
        int kernel_width = blur_kernel->get_width();
        int kernel_height = blur_kernel->get_height();

        if ((cor_x >= 0) && (cor_x < canvas->width()) &&
            (cor_y >= 0) && (cor_y < canvas->height())) {
            float red = 0.0;
            float green = 0.0;
            float blue = 0.0;
            float alpha;
            // loop every "neighbor" pixel within kernel
            for (int kernelY = 0; kernelY < kernel_height; kernelY++) {
              for (int kernelX = 0; kernelX < kernel_width; kernelX++) {
                int bufferX = kernelX + cor_x - kernel_width/2;
                int bufferY = kernelY + cor_y - kernel_height/2;
                if (bufferX >= 0 && bufferX < canvas->width() &&
                  bufferY >= 0 && bufferY < canvas->height()) {
                  // gather color data from the "neighbor" pixel
                  red += temp_buffer.get_pixel(bufferX, bufferY).red()
                        * blur_kernel->get_value(kernelX, kernelY);
                  green += temp_buffer.get_pixel(bufferX, bufferY).green()
                        * blur_kernel->get_value(kernelX, kernelY);
                  blue += temp_buffer.get_pixel(bufferX, bufferY).blue()
                        * blur_kernel->get_value(kernelX, kernelY);
          }
        }
      }
      red = fmin(red + blur_kernel->get_bias(), 1.0);
      green = fmin(green + blur_kernel->get_bias(), 1.0);
      blue = fmin(blue + blur_kernel->get_bias(), 1.0);
      alpha = canvas->get_pixel(x, y).alpha();
      canvas->set_pixel(cor_x , cor_y, ColorData(red, green, blue, alpha));
      delete blur_kernel;
    }
  }
}
}
}  // namespace image_tools
