/*******************************************************************************
 * Name            : chalk.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for Chalk class
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/16/2016
 * Original Author : Wei Chen
 *
 ******************************************************************************/
#ifndef SRC_INCLUDE_CHALK_H_
#define SRC_INCLUDE_CHALK_H_

#include "include/tool.h"

namespace image_tools {

class Chalk : public Tool{
 public:
  Chalk(int width, int height);
  virtual ~Chalk();
  void intializeMask();
};
}  // namespace image_tools
#endif  // SRC_INCLUDE_CHALK_H_
