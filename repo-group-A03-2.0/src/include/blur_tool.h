/*******************************************************************************
 * Name            : blur_tool.h
 * Project         : FlashPhoto
 * Module          : utils
 * Description     : Implementation of Blur Tool class
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 11/07/2016
 * Original Author : Julina Duan
 *
 ******************************************************************************/
#ifndef SRC_INCLUDE_BLUR_TOOL_H_
#define SRC_INCLUDE_BLUR_TOOL_H_

#include "include/tool.h"
#include "include/kernel.h"

namespace image_tools {
/**
 * @brief This tool simulates the usage of a blur tool.
 * It has a mask with linear fall-out and an opacity of xx at center.
 * It has a kernel of diamond shape with 1's inside of the "diamond".
 * Eraser overrides the paint function to provide its special
 * bluring functionality.
 */
class BlurTool : public Tool {
 public:
  BlurTool(int width, int height);
  virtual ~BlurTool();
  /**
   * @brief The mask of blur tool has a linear falloff to make the
   * blur feel natural, where the pixels near the center of blur
   * are the blurriest and the pixels farther away are less blurry.
   */
  void intializeMask();
  void paint(int x, int y, PixelBuffer* canvas,
    ColorData curr_color, int opa_lvl);

 protected:
 private:
   /**
    * @brief Calculate the distance between two x-y coordinates
    * @return The distance
    */
  float calc_distance(float x, float y, float x_, float y_);
};
}  // namespace image_tools
#endif  // SRC_INCLUDE_BLUR_TOOL_H_
