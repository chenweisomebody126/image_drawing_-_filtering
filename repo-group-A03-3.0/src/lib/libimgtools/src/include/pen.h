/*******************************************************************************
 * Name            : pen.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for Pen class
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/16/2016
 * Original Author : Natnael Seifu
 *
 ******************************************************************************/
#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_PEN_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_PEN_H_

#include <iostream>
#include "lib/libimgtools/src/include/tool.h"

namespace image_tools {
/**
 * @brief This tool simulates the usage of a pen.
 * It has a circular mask with an opacity of 1 in circle.
 * Pen uses the generic paint function from Tool class.
 */
class Pen : public Tool {
 public:
  Pen(int width, int height);
  virtual ~Pen(void);
  /**
   * @brief The mask of pen is circular and completely opaque in circle.
   */
  void intializeMask();
};
}  // namespace image_tools
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_PEN_H_
