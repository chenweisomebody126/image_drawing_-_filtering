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
#ifndef INCLUDE_HIGHLIGHTER_H_
#define INCLUDE_HIGHLIGHTER_H_

#include "include/tool.h"

namespace image_tools {

class Highlighter : public Tool{
 public:
  Highlighter();
  virtual ~Highlighter();
};
}  // namespace image_tools
#endif  // INCLUDE_HIGHLIGHTER_H_
