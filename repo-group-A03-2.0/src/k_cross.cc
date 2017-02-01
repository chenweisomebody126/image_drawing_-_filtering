/*******************************************************************************
 * Name            : k_cross.cc
 * Project         : image_tools
 * Module          : Kernel
 * Description     : Implementation of cross shape kernel class
 * Copyright       : 2016 CSCI3081W Group A03.
 * Creation Date   : 11/7/15
 * Original Author : Dawei Luo
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/k_cross.h"
#include <stdlib.h>
#include <cmath>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
KCross::KCross(float radius)
  : Kernel(radius) {
  int points_num;
  float factor;
  if (radius == 0) {
    set_factor(1);
  } else {
     points_num = (1 + get_height() - 2) * get_radius() + get_height();
     factor = 1.0 / points_num;
     set_factor(factor);
  }
  GenerateKernel();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
float KCross::value(int x, int y) {
  float radius = get_radius();
  if (y >= 0) {
    if (x < (y - radius) || x > (radius - y)) {
      return 0;
    } else {
      return 1;
    }
  } else {
    if (x < -radius - y  || x > radius + y) {
      return 0;
    } else {
      return 1;
    }
  }
}
}  /* namespace image_tools */
