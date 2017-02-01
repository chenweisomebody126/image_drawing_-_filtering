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
#ifndef SRC_INCLUDE_PEN_H_
#define SRC_INCLUDE_PEN_H_

#include <iostream>
#include "include/tool.h"

namespace image_tools {

class Pen : public Tool {
 public:
  Pen(int width, int height);
  virtual ~Pen(void);
  void intializeMask();
};
}  // namespace image_tools
#endif  // SRC_INCLUDE_PEN_H_