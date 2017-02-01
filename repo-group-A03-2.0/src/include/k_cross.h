/*******************************************************************************
 * Name            : k_cross.h
 * Project         : image_tools
 * Module          : Kernel
 * Description     : Header File for cross shape kernel class
 * Copyright       : 2016 CSCI3081W Group A03
 * Creation Date   : 11/7/16
 * Original Author : Dawei Luo
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_K_CROSS_H_
#define SRC_INCLUDE_K_CROSS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/kernel.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief KCross is a Kernel that is cross shape filled with 1
 */
class KCross : public Kernel {
 public:
  explicit KCross(float radius);

 protected:
  float value(int x, int y);
 private:
};
}  /* namespace image_tools */
#endif  /* SRC_INCLUDE_K_CROSS_H_ */
