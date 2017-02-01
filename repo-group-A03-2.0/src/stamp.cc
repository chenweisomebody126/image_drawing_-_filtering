/*******************************************************************************
 * Name            : Stamp.cc
 * Project         : FlashPhoto
 * Module          : utils
 * Description     : Implementation of Stamp class
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 11/14/2016
 * Original Author : Xinran Duan
 *
 ******************************************************************************/
#include <cmath>
#include <iostream>

#include "include/tool.h"
#include "include/stamp.h"

namespace image_tools {

  Stamp::Stamp(int width, int height) : Tool(width, height) {}

  void Stamp::intializeMask() {}

  void Stamp::loadStampFromFile(PixelBuffer* image) {
    setStampBuffer(image);
    // because opacities are 1's everywhere in the mask, no 2D
    // array will be created to represent the mask.
    int mask_width = image->width();
    int mask_height = image->height();
    setMaskWidth(mask_width);
    setMaskHeight(mask_height);
    // set mask to null to disable fill function
    setMask(nullptr);
  }

  /**
   * @Brief This function paints image loaded from
   *        file instead of applying mask
   */
  void Stamp::paint(int x, int y, PixelBuffer* canvas,
                    ColorData curr_color, int opa_lvl) {
    ColorData color;
    if (getMaskWidth() != 0 && getMaskHeight() != 0) {
      int a = x - floor(getMaskWidth()/2);
      int b = y - floor(getMaskHeight()/2);

      for (int i = 0; i < getMaskWidth(); i ++) {
        for (int j = 0; j < getMaskHeight(); j++) {
          if ((a + i >= 0) && (a + i < canvas->width()) &&
              (b + j >= 0) && (b + j < canvas->height())) {
            // takes advantage of the image's alpha channel
            if (stamp_buffer_->get_pixel(i, j).alpha() == 1.0) {
              color = stamp_buffer_->get_pixel(i, j);
              canvas->set_pixel(a + i, b + j, color);
            }
          }
        }
      }
    }
  }

  /**
   * @Brief we will use parents(Tool) Destructors
   * for deleting child tools, so implimentation is
   * not needed here.
   */
  Stamp::~Stamp(void) {}
}  // namespace image_tools
