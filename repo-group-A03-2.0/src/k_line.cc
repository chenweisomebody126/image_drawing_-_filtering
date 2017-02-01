/*******************************************************************************
 * Name            : k_line.cc
 * Project         : image_tools
 * Module          : Kernel
 * Description     : Implementation of line shape kernel class
 * Copyright       : 2016 CSCI3081W Group A03.
 * Creation Date   : 11/7/15
 * Original Author : Dawei Luo
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/k_line.h"
#include <cmath>
#include <iostream>
#include "include/ui_ctrl.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
KLine::KLine(float radius, UICtrl::MotionBlurDirection direction)
  : Kernel(radius),
   direction_(direction) {
  int points_num = get_radius() * 2 + 1;
  set_factor(1.0 / points_num);
  GenerateKernel();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
float KLine::value(int x, int y) {
  switch (direction_) {
    case UICtrl::UI_DIR_N_S:
      if (x == 0) {
        return 1.0;
      } else {
        return 0.0;
      }
      break;
    case UICtrl::UI_DIR_E_W:
      if (y == 0) {
        return 1.0;
      } else {
        return 0.0;
      }
      break;
    case UICtrl::UI_DIR_NE_SW:
      if (x == y) {
        return 1.0;
      } else {
        return 0.0;
      }
      break;
    case UICtrl::UI_DIR_NW_SE:
      if (x == -y) {
        return 1.0;
      } else {
        return 0.0;
      }
      break;
  }
}

}  /* namespace image_tools */
