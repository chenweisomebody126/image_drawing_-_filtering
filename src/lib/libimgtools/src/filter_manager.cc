/*******************************************************************************
 * Name            : filter_manager.cc
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Implementation of FilterManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 18:47:02 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lib/libimgtools/src/include/filter_manager.h"
#include <iostream>
#include <cmath>
#include "lib/libimgtools/src/include/ui_ctrl.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/kernel.h"
#include "lib/libimgtools/src/include/k_cross.h"
#include "lib/libimgtools/src/include/k_line.h"
#include "lib/libimgtools/src/include/k_square.h"
#include "lib/libimgtools/src/include/k_emboss.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FilterManager::FilterManager(void) :
    channel_color_red_(0.0),
    channel_color_green_(0.0),
    channel_color_blue_(0.0),
    saturation_amount_(0.0),
    threshold_amount_(0.0),
    blur_amount_(0.0),
    sharpen_amount_(0.0),
    motion_blur_amount_(0.0),
    motion_blur_direction_(UICtrl::UI_DIR_E_W),
    quantize_bins_(0) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void FilterManager::ApplyChannel(PixelBuffer* display_buffer) {
  for (int x = 0; x < display_buffer->width(); x++) {
    for (int y = 0; y < display_buffer->height(); y++) {
      ColorData pixel_color_ = display_buffer->get_pixel(x, y);
      float alpha = pixel_color_.alpha();
      float red = pixel_color_.red() * channel_color_red_;
      float green = pixel_color_.green() * channel_color_green_;
      float blue = pixel_color_.blue() * channel_color_blue_;
      red = fmin(red, 1);
      green = fmin(green, 1);
      blue = fmin(blue, 1);
      display_buffer->set_pixel(x, y, ColorData(red, green, blue, alpha));
    }
  }
  std::cout << "Apply has been clicked for Channels with red = "
            << channel_color_red_
            << ", green = " << channel_color_green_
            << ", blue = " << channel_color_blue_ << std::endl;
}

void FilterManager::ApplySaturate(PixelBuffer* display_buffer) {
  for (int x = 0; x < display_buffer->width(); x++) {
    for (int y = 0; y < display_buffer-> height(); y++) {
      ColorData pixel_color = display_buffer->get_pixel(x, y);
      float gray = pixel_color.luminance();
      float red = gray * (1 - saturation_amount_) + pixel_color.red()
                                                  * saturation_amount_;
      float green = gray * (1 - saturation_amount_) + pixel_color.green()
                                                    * saturation_amount_;
      float blue = gray * (1 - saturation_amount_) + pixel_color.blue()
                                                   * saturation_amount_;
      float alpha = pixel_color.alpha();
      red = fmin(fmax(red, 0.0), 1.0);
      green = fmin(fmax(green, 0.0), 1.0);
      blue = fmin(fmax(blue, 0.0), 1.0);
      display_buffer->set_pixel(x, y, ColorData(red, green, blue, alpha));
    }
  }

  std::cout << "Apply has been clicked for Saturate with amount = "
            << saturation_amount_ << std::endl;
}

void FilterManager::ApplyBlur(PixelBuffer* display_buffer) {
  std::cout << "Apply has been clicked for Blur with amount = "
            << blur_amount_ << std::endl;
  int radius = floor(blur_amount_ / 2);
  Kernel* blur_kernel = new KCross(radius);
  apply_kernel(blur_kernel, display_buffer);
}

void FilterManager::ApplySharpen(PixelBuffer* display_buffer) {
  std::cout << "Apply has been clicked for Sharpen with amount = "
            << sharpen_amount_ << std::endl;
  float cell_value = -sharpen_amount_ / 5;
  float center_value = -8 * cell_value + 1;
  Kernel* sharpen_kernel = new KSquare(1, center_value, cell_value);
  apply_kernel(sharpen_kernel, display_buffer);
}

void FilterManager::ApplyMotionBlur(PixelBuffer* display_buffer) {
  std::cout << "Apply has been clicked for Sharpen with amount = "
            << motion_blur_amount_
            << " and direction " << motion_blur_direction_ << std::endl;
  int radius = floor(motion_blur_amount_ / 2);
  Kernel* motion_blur_kernel = new KLine(radius, motion_blur_direction_);
  apply_kernel(motion_blur_kernel, display_buffer);
}

void FilterManager::ApplyEdgeDetect(PixelBuffer* display_buffer) {
  std::cout << "Apply has been clicked for Edge Detect" << std::endl;
  Kernel* edge_detect_kernel = new KSquare(1, 8, -1);
  apply_kernel(edge_detect_kernel, display_buffer);
}

void FilterManager::ApplyQuantize(PixelBuffer* display_buffer) {
  // quantize_bins_ ranges [2,256]
  float bin_size = 1./(quantize_bins_-1.);
  for (int y = 0; y < display_buffer->height(); y++) {
    for (int x = 0; x < display_buffer->width(); x++) {
      float red;
      float green;
      float blue;
      float alpha;
      ColorData pixel_color = display_buffer->get_pixel(x, y);
      red = ApplyChannelQuantize(pixel_color.red(), bin_size);
      green = ApplyChannelQuantize(pixel_color.green(), bin_size);
      blue = ApplyChannelQuantize(pixel_color.blue(), bin_size);
      alpha = pixel_color.alpha();
      display_buffer->set_pixel(x, y, ColorData(red, green, blue, alpha));
    }
  }
  std::cout << "Apply has been clicked for Quantize with bins = "
            << quantize_bins_ << std::endl;
}

float FilterManager::ApplyChannelQuantize(const float &color_value,
                                          const float &bin_size) {
  float bin_gap = bin_size / 2;
  int factor = color_value / bin_gap;
  if (factor % 2 == 0) {
    return bin_size * factor / 2;
  } else {
    return bin_size * (factor + 1) / 2;
  }
}

void FilterManager::ApplyThreshold(PixelBuffer* display_buffer) {
  for (int x = 0; x < display_buffer->width(); x++) {
    for (int y = 0; y < display_buffer->height(); y++) {
      ColorData pixel_color_ = display_buffer->get_pixel(x, y);
      float red = pixel_color_.red();
      float green = pixel_color_.green();
      float blue = pixel_color_.blue();
      float alpha = pixel_color_.alpha();
      red = RoundChannel(red);
      green = RoundChannel(green);
      blue = RoundChannel(blue);
      display_buffer->set_pixel(x, y, ColorData(red, green, blue, alpha));
    }
  }
  std::cout << "Apply Threshold has been clicked with amount ="
            << threshold_amount_ << std::endl;
}

float FilterManager::RoundChannel(const float& color_channel) {
  if (color_channel> threshold_amount_) {
    return 1.0;
  } else {
    return 0.0;
  }
}

void FilterManager::ApplySpecial(PixelBuffer *display_buffer) {
  std::cout << "Apply has been clicked for Special" << std::endl;
  Kernel* emboss_kernel = new KEmboss(1);
  apply_kernel(emboss_kernel, display_buffer);
}

void FilterManager::apply_kernel(Kernel* kernel, PixelBuffer* buffer) {
  PixelBuffer temp_buffer = PixelBuffer(buffer->width(), buffer->height(),
                                 buffer->background_color());
  temp_buffer = *buffer;

  int kernel_width = kernel->get_width();
  int kernel_height = kernel->get_height();
  int buffer_width = buffer->width();
  int buffer_height = buffer->height();

  for (int y = 0; y < buffer_height; y++) {
    for (int x = 0; x < buffer_width; x++) {
      float red = 0.0;
      float green = 0.0;
      float blue = 0.0;
      float alpha;
      for (int kernelY = 0; kernelY < kernel_height; kernelY++) {
        for (int kernelX = 0; kernelX < kernel_width; kernelX++) {
          int bufferX = kernelX + x - kernel_width / 2;
          int bufferY = kernelY + y - kernel_height / 2;
          if (bufferX >= 0 && bufferX < buffer_width &&
              bufferY >= 0 && bufferY < buffer_height) {
            red += temp_buffer.get_pixel(bufferX, bufferY).red()
             * kernel->get_value(kernelX, kernelY);
            green += temp_buffer.get_pixel(bufferX, bufferY).green()
             * kernel->get_value(kernelX, kernelY);
            blue += temp_buffer.get_pixel(bufferX, bufferY).blue()
             * kernel->get_value(kernelX, kernelY);
          }
        }
      }
      red = fmin(red + kernel->get_bias(), 1.0);
      green = fmin(green + kernel->get_bias(), 1.0);
      blue = fmin(blue + kernel->get_bias(), 1.0);
      alpha = buffer->get_pixel(x, y).alpha();
      buffer->set_pixel(x , y, ColorData(red, green, blue, alpha));
    }
  }
}

GLUI_Panel* FilterManager::InitGlui(const GLUI *const glui,
                             void (*s_gluicallback)(int)) {
  new GLUI_Column(const_cast<GLUI*>(glui), true);
  GLUI_Panel *filter_panel = new GLUI_Panel(const_cast<GLUI*>(glui), "Filters");
  {
    GLUI_Panel *blur_panel = new GLUI_Panel(filter_panel, "Blur");
    {
      GLUI_Spinner * blur_amount = new GLUI_Spinner(blur_panel, "Amount:",
                                                    &blur_amount_);
      blur_amount->set_int_limits(0, 20);
      blur_amount->set_int_val(5);

      new GLUI_Button(blur_panel, "Apply",
                      UICtrl::UI_APPLY_BLUR, s_gluicallback);
    }

    GLUI_Panel *motion_blur_panel = new GLUI_Panel(filter_panel, "MotionBlur");
    {
      GLUI_Spinner*motion_blur_amount = new GLUI_Spinner(motion_blur_panel,
                                                         "Amount:",
                                                         &motion_blur_amount_);
      motion_blur_amount->set_int_limits(0, 100);
      motion_blur_amount->set_int_val(5);

      motion_blur_direction_ = UICtrl::UI_DIR_E_W;
      GLUI_RadioGroup *dir_blur = new GLUI_RadioGroup(
          motion_blur_panel,
          reinterpret_cast<int*>(&motion_blur_direction_));
      new GLUI_RadioButton(dir_blur, "North/South");
      new GLUI_RadioButton(dir_blur, "East/West");
      new GLUI_RadioButton(dir_blur, "NorthEast/SouthWest");
      new GLUI_RadioButton(dir_blur, "NorthWest/SouthEast");

      new GLUI_Button(motion_blur_panel, "Apply",
                      UICtrl::UI_APPLY_MOTION_BLUR, s_gluicallback);
    }
    GLUI_Panel *sharpen_panel = new GLUI_Panel(filter_panel, "Sharpen");
    {
      GLUI_Spinner * sharp_amount = new GLUI_Spinner(sharpen_panel,
                                                     "Amount:",
                                                     &sharpen_amount_);
      sharp_amount->set_int_limits(0, 100);
      sharp_amount->set_int_val(5);

      new GLUI_Button(sharpen_panel, "Apply",
                      UICtrl::UI_APPLY_SHARP, s_gluicallback);
    }
    GLUI_Panel *edge_det_panel = new GLUI_Panel(filter_panel, "Edge Detect");

    {
      new GLUI_Button(edge_det_panel, "Apply",
                      UICtrl::UI_APPLY_EDGE, s_gluicallback);
    }
    GLUI_Panel *thres_panel = new GLUI_Panel(filter_panel, "Threshold");
    {
      GLUI_Spinner *threshold_amount = new GLUI_Spinner(thres_panel,
                                                        "Level:",
                                                        &threshold_amount_);
      threshold_amount->set_float_limits(0, 1);
      threshold_amount->set_float_val(0.5);

      new GLUI_Button(thres_panel, "Apply",
                      UICtrl::UI_APPLY_THRESHOLD, s_gluicallback);
    }

    new GLUI_Column(filter_panel, true);

    GLUI_Panel *satur_panel = new GLUI_Panel(filter_panel, "Saturation");
    {
      GLUI_Spinner * saturation_amount = new GLUI_Spinner(satur_panel,
                                                          "Amount:",
                                                          &saturation_amount_);
      saturation_amount->set_float_limits(-10, 10);
      saturation_amount->set_float_val(1);

      new GLUI_Button(satur_panel, "Apply",
                      UICtrl::UI_APPLY_SATURATE,
                      s_gluicallback);
    }

    GLUI_Panel *channel_panel = new GLUI_Panel(filter_panel, "Channels");
    {
      GLUI_Spinner *channel_red = new GLUI_Spinner(channel_panel, "Red:",
                                                   &channel_color_red_);
      GLUI_Spinner *channel_green = new GLUI_Spinner(channel_panel,
                                                     "Green:",
                                                     &channel_color_green_);
      GLUI_Spinner *channel_blue = new GLUI_Spinner(channel_panel,
                                                    "Blue:",
                                                    &channel_color_blue_);

      channel_red->set_float_limits(0, 10);
      channel_red->set_float_val(1);
      channel_green->set_float_limits(0, 10);
      channel_green->set_float_val(1);
      channel_blue->set_float_limits(0, 10);
      channel_blue->set_float_val(1);

      new GLUI_Button(channel_panel, "Apply",
                      UICtrl::UI_APPLY_CHANNEL,
                      s_gluicallback);
    }

    GLUI_Panel *quant_panel = new GLUI_Panel(filter_panel, "Quantize");
    {
      GLUI_Spinner * quantize_bins = new GLUI_Spinner(quant_panel, "Bins:",
                                                      &quantize_bins_);
      quantize_bins->set_int_limits(2, 256);
      quantize_bins->set_int_val(8);
      quantize_bins->set_speed(0.1);

      new GLUI_Button(quant_panel, "Apply",
                      UICtrl::UI_APPLY_QUANTIZE,
                      s_gluicallback);
    }

    // YOUR SPECIAL FILTER PANEL
    GLUI_Panel *specialFilterPanel = new GLUI_Panel(filter_panel, "Emboss");
    {
      new GLUI_Button(specialFilterPanel,
                      "Apply",
                      UICtrl::UI_APPLY_SPECIAL_FILTER,
                      s_gluicallback);
    }
  }
  return filter_panel;
} /* FilterManager::InitGlui() */

void FilterManager::AddBlurToGLUI(GLUI_Panel *filter_panel,
                                  void (*s_gluicallback)(int)) {
  GLUI_Panel *blur_panel = new GLUI_Panel(filter_panel, "Blur");
  GLUI_Spinner * blur_amount = new GLUI_Spinner(blur_panel, "Amount:",
                                                &blur_amount_);
  blur_amount->set_int_limits(0, 20);
  blur_amount->set_int_val(5);

  new GLUI_Button(blur_panel, "Apply",
                  UICtrl::UI_APPLY_BLUR, s_gluicallback);
}

void FilterManager::AddMotionBlurToGLUI(GLUI_Panel *filter_panel,
                                        void (*s_gluicallback)(int)) {
  GLUI_Panel *motion_blur_panel = new GLUI_Panel(filter_panel, "MotionBlur");
  GLUI_Spinner*motion_blur_amount = new GLUI_Spinner(motion_blur_panel,
                                                     "Amount:",
                                                     &motion_blur_amount_);
  motion_blur_amount->set_int_limits(0, 100);
  motion_blur_amount->set_int_val(5);

  motion_blur_direction_ = UICtrl::MotionBlurDirection::UI_DIR_N_S;
  GLUI_RadioGroup *dir_blur = new GLUI_RadioGroup(
      motion_blur_panel,
      reinterpret_cast<int*>(&motion_blur_direction_));
  new GLUI_RadioButton(dir_blur, "North/South");
  new GLUI_RadioButton(dir_blur, "East/West");
  new GLUI_RadioButton(dir_blur, "NorthEast/SouthWest");
  new GLUI_RadioButton(dir_blur, "NorthWest/SouthEast");

  new GLUI_Button(motion_blur_panel, "Apply",
                  UICtrl::UI_APPLY_MOTION_BLUR, s_gluicallback);
}

void FilterManager::AddSharpenToGLUI(GLUI_Panel *filter_panel,
                                     void (*s_gluicallback)(int)) {
  GLUI_Panel *sharpen_panel = new GLUI_Panel(filter_panel, "Sharpen");
      GLUI_Spinner * sharp_amount = new GLUI_Spinner(sharpen_panel,
                                                     "Amount:",
                                                     &sharpen_amount_);
      sharp_amount->set_int_limits(0, 100);
      sharp_amount->set_int_val(5);

      new GLUI_Button(sharpen_panel, "Apply",
                      UICtrl::UI_APPLY_SHARP, s_gluicallback);
}

void FilterManager::AddEdgeDetectToGLUI(GLUI_Panel *filter_panel,
                                        void (*s_gluicallback)(int)) {
GLUI_Panel *edge_det_panel = new GLUI_Panel(filter_panel, "Edge Detect");
  new GLUI_Button(edge_det_panel, "Apply",
                  UICtrl::UI_APPLY_EDGE, s_gluicallback);
}

void FilterManager::AddThresholdToGLUI(GLUI_Panel *filter_panel,
                                        void (*s_gluicallback)(int)) {
  GLUI_Panel *thres_panel = new GLUI_Panel(filter_panel, "Threshold");
  GLUI_Spinner *threshold_amount = new GLUI_Spinner(thres_panel,
                                                    "Level:",
                                                    &threshold_amount_);
  threshold_amount->set_float_limits(0, 1);
  threshold_amount->set_float_val(0.5);

  new GLUI_Button(thres_panel, "Apply",
                  UICtrl::UI_APPLY_THRESHOLD, s_gluicallback);
}

void FilterManager::AddSaturationToGLUI(GLUI_Panel *filter_panel,
                                        void (*s_gluicallback)(int)) {
GLUI_Panel *satur_panel = new GLUI_Panel(filter_panel, "Saturation");
  GLUI_Spinner * saturation_amount = new GLUI_Spinner(satur_panel,
                                                      "Amount:",
                                                      &saturation_amount_);
  saturation_amount->set_float_limits(-10, 10);
  saturation_amount->set_float_val(1);

  new GLUI_Button(satur_panel, "Apply",
                  UICtrl::UI_APPLY_SATURATE,
                  s_gluicallback);
}

void FilterManager::AddChannelToGLUI(GLUI_Panel *filter_panel,
                                        void (*s_gluicallback)(int)) {
    GLUI_Panel *channel_panel = new GLUI_Panel(filter_panel, "Channels");
      GLUI_Spinner *channel_red = new GLUI_Spinner(channel_panel, "Red:",
                                                   &channel_color_red_);
      GLUI_Spinner *channel_green = new GLUI_Spinner(channel_panel,
                                                     "Green:",
                                                     &channel_color_green_);
      GLUI_Spinner *channel_blue = new GLUI_Spinner(channel_panel,
                                                    "Blue:",
                                                    &channel_color_blue_);

      channel_red->set_float_limits(0, 10);
      channel_red->set_float_val(1);
      channel_green->set_float_limits(0, 10);
      channel_green->set_float_val(1);
      channel_blue->set_float_limits(0, 10);
      channel_blue->set_float_val(1);

      new GLUI_Button(channel_panel, "Apply",
                      UICtrl::UI_APPLY_CHANNEL,
                      s_gluicallback);
}

void FilterManager::AddQuantizationToGLUI(GLUI_Panel *filter_panel,
                                          void (*s_gluicallback)(int)) {
  GLUI_Panel *quant_panel = new GLUI_Panel(filter_panel, "Quantize");
  GLUI_Spinner * quantize_bins = new GLUI_Spinner(quant_panel, "Bins:",
                                                      &quantize_bins_);
  quantize_bins->set_int_limits(2, 256);
  quantize_bins->set_int_val(8);
  quantize_bins->set_speed(0.1);

  new GLUI_Button(quant_panel, "Apply",
                  UICtrl::UI_APPLY_QUANTIZE,
                  s_gluicallback);
}


}  /* namespace image_tools */
