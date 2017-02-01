/*******************************************************************************
 * Name            : k_square.cc
 * Project         : image_tools
 * Module          : Kernel
 * Description     : Implementation of square shape kernel class
 * Copyright       : 2016 CSCI3081W Group A03.
 * Creation Date   : 11/7/15
 * Original Author : Dawei Luo
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/k_square.h"
#include <cmath>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
KSquare::KSquare(float radius, float center_value, float cell_value)
  : Kernel(radius),
  center_value_(center_value),
  cell_value_(cell_value) {
  GenerateKernel();
}

/*******************************************************************************
* Member Functions
******************************************************************************/
float KSquare::value(int x, int y) {
  if (x == 0 && y == 0) {
    return center_value_;
  } else {
    return cell_value_;
  }
}

}  /* namespace image_tools */
