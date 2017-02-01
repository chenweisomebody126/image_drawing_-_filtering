/*******************************************************************************
 * Name            : Kernel.cc
 * Project         : image_tools
 * Module          : Kernel
 * Description     : Implementation of Kernel class
 * Copyright       : 2016 CSCI3081W Group A03
 * Creation Date   : 11/7/15
 * Original Author : Dawei Luo
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/kernel.h"
#include <cmath>
#include <iostream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Kernel::Kernel(void) : radius_(0.0),
               factor_(0.0),
               height_(0),
               width_(0),
               bias_(0.0),
               kernel_array_(nullptr) {}

Kernel::Kernel(float radius)
    : radius_(floor(radius)),
      factor_(1.0),
      height_(floor(radius)*2+1),
      width_(floor(radius)*2+1),
      bias_(0.0),
      kernel_array_(new float[width_*height_]) {
    std::fill(kernel_array_, kernel_array_+width_*height_, 0.f);
}

Kernel::~Kernel(void) {
  delete [] kernel_array_;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

float Kernel::get_value(int x, int y) const {
  if (kernel_array_ == nullptr || x < 0 || x > width_ || y < 0 || y > width_) {
    return 0.f;
  } else {
    return kernel_array_[y*width_ + x];
  }
}

void Kernel::set_value(int x, int y, float v) {
  if (kernel_array_ == nullptr || x < 0 || x > width_ || y < 0 || y > width_) {
    return;
  } else {
    kernel_array_[y*width_ + x] = v;
  }
}

void Kernel::set_bias(float bias) {
  if (bias > 1 || bias < 0) {
    return;
  } else {
    bias_ = bias;
  }
}

void Kernel::GenerateKernel(void) {
  for (int j = 0; j < get_height(); j++) {
    for (int i = 0; i < get_width(); i++) {
      int x = i-get_width()/2;
      int y = j-get_height()/2;
      float temp_value = factor_*value(x, y);
      set_value(i, j, temp_value);
    }
  }
}

}  /* namespace image_tools */
