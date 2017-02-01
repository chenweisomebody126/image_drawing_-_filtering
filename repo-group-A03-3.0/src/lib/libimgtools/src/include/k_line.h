/*******************************************************************************
 * Name            : k_line.h
 * Project         : image_tools
 * Module          : Kernel
 * Description     : Header File for line shape kernel class
 * Copyright       : 2016 CSCI3081W Group A03
 * Creation Date   : 11/9/16
 * Original Author : Dawei Luo
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_K_LINE_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_K_LINE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/kernel.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief KLine is kernel with a line shape in it. The line is consist of 1.
 * the other part of kernel is 0.
 */
class KLine : public Kernel {
 public:
  KLine(float radius, UICtrl::MotionBlurDirection direction);

 protected:
  float value(int x, int y);

 private:
  enum UICtrl::MotionBlurDirection direction_;
};
}  /* namespace image_tools */
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_K_LINE_H_
