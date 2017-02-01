/*******************************************************************************
 * Name            : calligraphy.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for CalligraphyPen class
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/16/2016
 * Original Author : Julina Duan
 *
 ******************************************************************************/
#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_CALLIGRAPHY_PEN_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_CALLIGRAPHY_PEN_H_

#include "lib/libimgtools/src/include/tool.h"

namespace image_tools {
/**
 * @brief This tool simulates the usage of a caligraphy pen.
 * It has a rectangular mask with an opacity of 1 every where.
 * The height of mask should be larger than the width.
 * Caligraphy pen uses the generic paint function from Tool class.
 */
class CalligraphyPen : public Tool {
 public:
  CalligraphyPen(int width, int height);
  virtual ~CalligraphyPen();
  /**
   * @brief The mask of caligraphy pen is retangualr and completely
   * opaque every where.
   */
  void intializeMask();
};
}  // namespace image_tools
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_CALLIGRAPHY_PEN_H_
