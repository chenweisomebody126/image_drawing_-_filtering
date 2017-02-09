/*******************************************************************************
 * Name            : k_special.cc
 * Project         : image_tools
 * Module          : Kernel
 * Description     : Implementation of special kernel class
 * Copyright       : 2016 CSCI3081W Group A03.
 * Creation Date   : 11/7/15
 * Original Author : Dawei Luo
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/k_emboss.h"
#include <cmath>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
KEmboss::KEmboss(float radius) : Kernel(radius) {
  set_bias(0.5);
  GenerateKernel();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
float KEmboss::value(int x, int y) {
  if (x == y) {
    return 0;
  } else if (x > y) {
    return 1;
  } else {
    return -1;
  }
}

}  /* namespace image_tools */
