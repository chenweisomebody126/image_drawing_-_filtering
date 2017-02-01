/*******************************************************************************
 * Name            : spray_paint.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for SprayPaint class.
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/16/16
 * Original Author : Natnael Seifu
 *
 ******************************************************************************/
#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SPRAY_PAINT_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SPRAY_PAINT_H_

#include <iostream>
#include "lib/libimgtools/src/include/tool.h"

namespace image_tools {
/**
 * @brief This tool simulates the usage of a spray can.
 * It has a circular mask with linear fall-out with 0.1 at center.
 * Spray can uses the generic paint function from Tool class.
 */
class SprayPaint : public Tool {
 public:
  SprayPaint(int width, int height);
  virtual ~SprayPaint(void);
  /**
   * @brief The mask of spray can has a linear falloff to make the
   * spraying feel natural, where the pixels near the center are more
   * opaque and the pixels farther away are less opaque.
   */
  void intializeMask();
 protected:
 private:
  /**
   * @brief Calculate the distance between two x-y coordinates
   * @return The distance
   */
  float calc_distance(float x, float y, float x_, float y_);
};
}  // namespace image_tools

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SPRAY_PAINT_H_
