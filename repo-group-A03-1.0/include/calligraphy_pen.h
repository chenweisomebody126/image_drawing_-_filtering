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
#ifndef INCLUDE_CALLIGRAPHY_PEN_H_
#define INCLUDE_CALLIGRAPHY_PEN_H_

#include "include/tool.h"

namespace image_tools {

class CalligraphyPen : public Tool {
 public:
  CalligraphyPen();
  virtual ~CalligraphyPen();
};
}  // namespace image_tools
#endif  // INCLUDE_CALLIGRAPHY_PEN_H_
