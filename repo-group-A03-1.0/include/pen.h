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
#ifndef INCLUDE_PEN_H_
#define INCLUDE_PEN_H_

#include <iostream>
#include "include/tool.h"

namespace image_tools {

class Pen : public Tool {
 public:
  Pen();
  virtual ~Pen(void);
};
}  // namespace image_tools

#endif  // INCLUDE_PEN_H_
