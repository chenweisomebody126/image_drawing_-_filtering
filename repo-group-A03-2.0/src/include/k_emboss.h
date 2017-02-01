/*******************************************************************************
 * Name            : k_emboss.h
 * Project         : image_tools
 * Module          : Kernel
 * Description     : Header File for a Special kernel class
 * Copyright       : 2016 CSCI3081W Group A03
 * Creation Date   : 11/9/16
 * Original Author : Dawei Luo
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_K_EMBOSS_H_
#define SRC_INCLUDE_K_EMBOSS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/kernel.h"
#include "include/ui_ctrl.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief KSpecial is the kernel with no specific pattern. It just takes
 * the kerenl_array you enter as the kernel.
 */
class KEmboss : public Kernel {
 public:
  explicit KEmboss(float radius);

 protected:
  float value(int x, int y);
 private:
};
}  /* namespace image_tools */
#endif  /* SRC_INCLUDE_K_EMBOSS_H_ */
