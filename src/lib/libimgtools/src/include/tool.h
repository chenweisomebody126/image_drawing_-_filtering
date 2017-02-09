/*******************************************************************************
 * Name            : tool.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for Tool class.
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/14/16
 * Original Author : Julina Duan
 *
 ******************************************************************************/
#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_TOOL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_TOOL_H_

#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

namespace image_tools {
/**
 * @brief Tool is the representation of a particular BrushWork tool.
 * This baseclass is abstract and defines a generic paint function for 
 * child classes, but it does not provide a default mask.
 */
class Tool {
 public:
  Tool(int width, int height);
  virtual ~Tool(void);
  /**
   * @Brief This function implements painting of tools when mouse is dragged
   */
  virtual void fill(int x, int y, int prev_x, int prev_y, PixelBuffer* canvas,
                    ColorData curr_color);
  /**
   * @brief This generic paint function implements painting of tools by
   * calculating ColorData of each pixel within the mask by a formula:
   * new_canvas_color = tool_color * intensity + canvas_color * (1 - intensity)
   */
  virtual void paint(int x, int y, PixelBuffer* canvas, ColorData curr_color,
                     int opa_lvl);
  virtual void intializeMask() = 0;

 protected:
  inline int getMaskWidth() {
    return mask_width_;
  }
  inline int getMaskHeight() {
    return mask_height_;
  }
  inline void setMaskWidth(int width) {
    mask_width_ = width;
  }
  inline void setMaskHeight(int height) {
    mask_height_ = height;
  }
  inline float maskValueAt(int x, int y) {
    return mask_[x][y];
  }
  inline void setMask(float** mask) {
    mask_ = mask;
  }

 private:
  int mask_width_;
  int mask_height_;
  float** mask_;
};
}  // namespace image_tools

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_TOOL_H_
