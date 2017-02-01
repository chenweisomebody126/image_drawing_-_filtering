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
#ifndef INCLUDE_CHALK_H_
#define INCLUDE_CHALK_H_

#include "include/tool.h"

namespace image_tools {

class Chalk : public Tool{
 public:
  Chalk();
  virtual ~Chalk();
};
}  // namespace image_tools
#endif  // INCLUDE_CHALK_H_
