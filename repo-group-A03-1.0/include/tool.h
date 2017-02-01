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
#ifndef INCLUDE_TOOL_H_
#define INCLUDE_TOOL_H_

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
  Tool(void);
  virtual ~Tool(void);
  virtual void fill(int x, int y, int prev_x, int prev_y,
    PixelBuffer* canvas, ColorData curr_color);
  virtual void paint(int x, int y, PixelBuffer* canvas, ColorData curr_color);
 protected:
  int mask_width_;
  int mask_height_;
  float** mask_;

 private:
};
}  // namespace image_tools

#endif  // INCLUDE_TOOL_H_
