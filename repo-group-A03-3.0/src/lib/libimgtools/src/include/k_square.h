/*******************************************************************************
 * Name            : k_square.h
 * Project         : image_tools
 * Module          : Kernel
 * Description     : Header File for square shape kernel class
 * Copyright       : 2016 CSCI3081W Group A03
 * Creation Date   : 11/9/16
 * Original Author : Dawei Luo
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_K_SQUARE_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_K_SQUARE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/kernel.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief KSquare is a Kernel that is a square shape, which is -1 everywhere
 * and the center with a center_value.
 */
class KSquare : public Kernel {
 public:
  KSquare(float radius, float center_value, float cell_value);
 protected:
  float value(int x, int y);
 private:
  float center_value_;
  float cell_value_;
};
}  /* namespace image_tools */
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_K_SQUARE_H_
