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
#ifndef SRC_INCLUDE_HIGHLIGHTER_H_
#define SRC_INCLUDE_HIGHLIGHTER_H_

#include "include/tool.h"

namespace image_tools {

class Highlighter : public Tool{
 public:
  Highlighter(int width, int height);
  virtual ~Highlighter();
  void intializeMask();
};
}  // namespace image_tools
#endif  // SRC_INCLUDE_HIGHLIGHTER_H_
