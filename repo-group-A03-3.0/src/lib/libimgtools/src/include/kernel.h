/*******************************************************************************
 * Name            : Kernel.h
 * Project         : image_tools
 * Module          : Kernel
 * Description     : Header file for Kernel base class
 * Copyright       : 2016 CSCI3081W Group A03.
 * Creation Date   : 11/07/15
 * Original Author : Dawei Luo
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_KERNEL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_KERNEL_H_

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Base class for representing a filter matrix apply to convolution
 * filter. Its size has to be odd, so that it has a center.
 * It will calculate the how the center will be effected by the color nearby.
 * It does not have a shape; shapes are defined implicitly with
 * value().
 */
class Kernel {
 public:
  Kernel(void);
  explicit Kernel(float radius);
  virtual ~Kernel(void);

  /**
   * @brief Get a handle on the underlying array of float values representing
   * the shape of the kernel and how the center will be effected.
   * @return The float array
   */
  float const *get_kernel_array(void) const { return kernel_array_; }

  /**
   * @brief Get the width of the filter matrix
   * @return The width
   */
  int get_width(void) const { return width_;}

  /**
   * @brief Get the height of the filter matrix
   * @return The height
   */
  int get_height(void) const {return height_;}

  /**
   * @brief get the bias value of the kernel
   */
  float get_bias(void) {return bias_;}

  /**
   * @brief Get the radius of the Kernel
   * @return The radius
   */
  float get_radius(void) const {return radius_;}

  /**
   * @brief Get the value of the Kernel at (x,y)
   * @return The value
   */
  float get_value(int x, int y) const;

 protected:
  /**
   * @brief Set the value of the kernel at (x,y)
   */
  void set_value(int x, int y, float v);

  /**
   * @brief Set the bias value of the kernel
   */
  void set_bias(float bias);

  /**
   * @brief Set the factor of the kernel
   */
  void set_factor(float factor) {factor_ = factor;}

  /**
   * @brief Generate the filter matrix that defines the shape and effect
   * of the filter.
   * Relies on the derived class implementation of value() to do so.
   */
  void GenerateKernel(void);

  /**
   * @brief Define the certain filter matrix of the kernel.
   * @param x The X coordinate of the pixel filter is working on
   * @param y The Y coordinate of the pixel filter is working on
   */
  virtual float value(int x, int y) = 0;

 private:
  /* Copy/move assignment/construction are disallowed */
  Kernel(const Kernel& rhs) = delete;
  Kernel& operator=(const Kernel& rhs) = delete;

  int height_; /**< number of pixel rows available in the kernel  */
  int width_; /**< number pixel columns available in the kernel  */
  float radius_;
  float factor_;
  float bias_;
  float *kernel_array_;
};

}  /* namespace image_tools */

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_KERNEL_H_
