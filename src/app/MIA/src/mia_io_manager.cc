/*******************************************************************************
 * Name            : io_manager.cc
 * Project         : FlashPhoto
 * Module          : io_manager
 * Description     : Implementation of MIAIOManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 20:47:05 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app/MIA/src/include/mia_io_manager.h"
#include <assert.h>
#include <iostream>
#include <sstream>
#include "lib/libimgtools/src/include/io_manager.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"
#include "lib/libimgtools/src/include/file_io.h"
#include "lib/libimgtools/src/include/file_io_factory.h"

/* FIXME: ADDITIONAL INCLUDES AS NECESSARY HERE :-) */

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MIAIOManager::MIAIOManager(void) :
    IOManager(),
    next_image_btn_(nullptr),
    prev_image_btn_(nullptr),
    prev_file_name_(),
    next_file_name_(),
    start_file_name_(""),
    has_next_image_(false),
    has_prev_image_(false) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
GLUI_Panel* MIAIOManager::InitGlui(const GLUI *const glui,
                         void (*s_gluicallback)(int)) {
  new GLUI_Column(const_cast<GLUI*>(glui), true);
  GLUI_Panel *image_panel = new GLUI_Panel(const_cast<GLUI*>(glui),
                                           "Image I/O");
  AddFileBrowserToGLUI(image_panel, s_gluicallback);
  AddSaveCanvasToGLUI(image_panel, s_gluicallback);
  AddLoadStampToGLUI(image_panel, s_gluicallback);
  new GLUI_Separator(image_panel);

  prev_image_btn_  = new GLUI_Button(image_panel, "Previous Image",
                                     UICtrl::UI_PREV_IMAGE_BUTTON,
                                     s_gluicallback);
  next_image_btn_ = new GLUI_Button(image_panel, "Next Image",
                                    UICtrl::UI_NEXT_IMAGE_BUTTON,
                                    s_gluicallback);

  next_image_toggle(has_next_image_);
  prev_image_toggle(has_prev_image_);
  return image_panel;
}

PixelBuffer* MIAIOManager::LoadNextImage(void) {
  set_image_file(next_file_name_);
  LoadImageToCanvas();
}

PixelBuffer* MIAIOManager::LoadPreviousImage(void) {
  set_image_file(prev_file_name_);
  LoadImageToCanvas();
}

PixelBuffer* MIAIOManager::LoadImageToCanvas(const std::string& filename){
  std::string image_file_name = filename;
  size_t pound_pos = filename.find_last_of("#");
  if (pound_pos == filename.find_last_of(".") - 1){
    while (image_file_name[pound_pos] == '#'){
      image_file_name.replace(pound_pos, 1, "0");
      pound_pos = pound_pos - 1;
    }
    while (!is_valid_image_file(image_file_name)){
      image_file_name = image_name_plus_seq_offset(image_file_name, 1);
    }
  }
  next_file_name_ = image_name_plus_seq_offset(image_file_name, 1);
  has_next_image_ = is_valid_image_file(next_file_name_);
  // Determining whether there are next or previous images
  return IOManager::LoadImageToCanvas(image_file_name);
}

PixelBuffer* MIAIOManager::LoadImageToCanvas(void) {
  // Determining whether there are next or previous images
  next_file_name_ = image_name_plus_seq_offset(file_name(), 1);
  prev_file_name_ = image_name_plus_seq_offset(file_name(), -1);

  has_prev_image_ = is_valid_image_file(prev_file_name_);
  has_next_image_ = is_valid_image_file(next_file_name_);

  next_image_toggle(is_valid_image_file(next_file_name_));
  prev_image_toggle(is_valid_image_file(prev_file_name_));
  return IOManager::LoadImageToCanvas();
}

void MIAIOManager::set_image_file(const std::string & fname_in) {
  // If a directory was selected instead of a file, use the
  // latest file typed or selected.
  std::string image_file = fname_in;
  if (!is_valid_image_file_name(image_file)) {
    image_file = file_name();
  }

  // TOGGLE SAVE FEATURE
  // If no file is selected or typed, don't allow file to be saved. If
  // there is a file name, then allow file to be saved to that name.

  if (!is_valid_image_file_name(image_file)) {
    save_file_label()->set_text("Will save image: none");
    save_canvas_toggle(false);
  } else {
    save_file_label()->set_text((std::string("Will save image: ") +
                                 image_file).c_str());
    save_canvas_toggle(true);
  }

  // TOGGLE LOAD FEATURE

  // If the file specified cannot be opened, then disable stamp and canvas
  // loading.
  if (is_valid_image_file(image_file)) {
    load_canvas_toggle(true);
    load_stamp_toggle(true);
    current_file_label()->set_text((std::string("Will load: ") +
                                    image_file).c_str());
    file_name_box()->set_text(image_file);
  } else {
    load_canvas_toggle(false);
    load_stamp_toggle(false);
    current_file_label()->set_text("Will load: none");
  }
}

std::string MIAIOManager::image_name_plus_seq_offset(
    const std::string& filename,
    int offset) {

  std::string extension, name, number;
  size_t dot_pos = filename.find_last_of(".");
  if (dot_pos ==  std::string::npos || dot_pos == 0) {
    return "";
  }

  extension = filename.substr(dot_pos+1);
  name = filename.substr(0, dot_pos);
  if (static_cast<int>(name.length()) < kDigitCount) {
    return "";
  }

  number = name.substr(name.length()-kDigitCount);
  name = name.substr(0, name.length()-kDigitCount);
  int num;
  std::istringstream(number) >> num;
  int output_num = num +offset;
  if (output_num < 0) {
    return "";
  }
  std::stringstream ss;
  ss << output_num;
  std::string output_number;
  ss >> output_number;

  // Append zero chars
  int str_length = output_number.length();
  for (int i = 0; i < kDigitCount - str_length; i++) {
    output_number = "0" + output_number;
  }

  return (name + output_number + "." + extension);
}

void MIAIOManager::SaveCanvasToFile(const PixelBuffer* curr_canvas) {
  return IOManager::SaveCanvasToFile(curr_canvas);
}

void MIAIOManager::SaveCanvasToFile(const PixelBuffer* curr_canvas,
                                    const std::string& file_name){
  std::string image_file_name = file_name;
  size_t pound_pos = file_name.find_last_of("#");
  if (pound_pos == file_name.find_last_of(".") - 1){
    while (image_file_name[pound_pos] == '#'){
      image_file_name.replace(pound_pos, 1, "0");
      pound_pos = pound_pos - 1;
    }
    set_start_image_file_name(image_file_name);
  }
  IOManager::SaveCanvasToFile(curr_canvas, image_file_name);
}
}  /* namespace image_tools */
