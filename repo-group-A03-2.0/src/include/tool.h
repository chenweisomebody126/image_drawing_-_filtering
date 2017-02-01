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
#ifndef SRC_INCLUDE_TOOL_H_
#define SRC_INCLUDE_TOOL_H_

#include "include/color_data.h"
#include "include/pixel_buffer.h"
/**
 * @brief This Tool Class handles painting.
 */
namespace image_tools {

class Tool {
 public:
  /**
   * @brief There can never be a generic tool
   */
  Tool(int width, int height);
  virtual ~Tool(void);
  virtual void fill(int x, int y, int prev_x, int prev_y,
    PixelBuffer* canvas, ColorData curr_color);
  virtual void paint(int x, int y, PixelBuffer* canvas,
    ColorData curr_color, int opa_lvl);
  virtual void intializeMask() = 0;

 protected:
  inline int getMaskWidth() { return mask_width_; }
  inline int getMaskHeight() { return mask_height_; }
  inline void setMaskWidth(int width) { mask_width_ = width; }
  inline void setMaskHeight(int height) { mask_height_ = height; }
  inline float maskValueAt(int x, int y) { return mask_[x][y]; }
  inline void setMask(float** mask) { mask_ = mask; }


 private:
  int mask_width_;
  int mask_height_;
  float** mask_;
};
}  // namespace image_tools

#endif  // SRC_INCLUDE_TOOL_H_
