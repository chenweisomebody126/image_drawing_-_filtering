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
#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_CHALK_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_CHALK_H_

#include "lib/libimgtools/src/include/tool.h"

namespace image_tools {
/**
 * @brief This tool simulates the usage of a chalk.
 * It has a mask with randomized opcacities.
 * Chalk uses the generic paint function from Tool class.
 */
class Chalk : public Tool{
 public:
  Chalk(int width, int height);
  virtual ~Chalk();
  /**
   * @brief The mask of chalk has randomized opacities.
   */
  void intializeMask();
};
}  // namespace image_tools
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_CHALK_H_
