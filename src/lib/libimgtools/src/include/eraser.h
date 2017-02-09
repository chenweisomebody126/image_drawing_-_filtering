/*******************************************************************************
 * Name            : eraser.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for Eraser class
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/16/2016
 * Original Author : Wei Chen
 *
 ******************************************************************************/
#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_ERASER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_ERASER_H_

#include "lib/libimgtools/src/include/tool.h"

namespace image_tools {
/**
 * @brief This tool simulates the usage of an eraser.
 * It has a rectangular mask with an opacity of 1 every where.
 * Eraser overrides the paint function to provide its special
 * functionality of recovering background color.
 */
class Eraser : public Tool {
 public:
  Eraser(int width, int height);
  virtual ~Eraser();
  /**
   * @brief The mask of eraser has a rectangular shape and is full of
   * 1's every where.
   */
  void intializeMask();
  /**
   * @brief The paint() of eraser is overwritten to perform its
   * special functionality. Erasing is implemented by recover all pixels
   * in mask to background color.
   */
  void paint(int x, int y, PixelBuffer* canvas,
    ColorData curr_color, int opa_lvl);

 protected:
 private:
};
}  // namespace image_tools
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_ERASER_H_
