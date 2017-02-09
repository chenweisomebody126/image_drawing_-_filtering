/*******************************************************************************
 * Name            : highlighter.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for HighLighter class
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/16/2016
 * Original Author : Julina Duan
 *
 ******************************************************************************/
#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_HIGHLIGHTER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_HIGHLIGHTER_H_

#include "lib/libimgtools/src/include/tool.h"

namespace image_tools {
/**
 * @brief This tool simulates the usage of a highlighter.
 * It has a rectangular mask with an opacity of 0.4 every where.
 * The height of mask should be larger than the width.
 * Highlighter uses the generic paint function from Tool class.
 */
class Highlighter : public Tool{
 public:
  Highlighter(int width, int height);
  virtual ~Highlighter();
  /**
   * @brief The mask of caligraphy pen is retangualr and has an opacity of
   * 0.4 every where.
   */
  void intializeMask();
};
}  // namespace image_tools
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_HIGHLIGHTER_H_
