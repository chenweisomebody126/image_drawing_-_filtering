/*******************************************************************************
 * Name            : mia_io_manager.h
 * Project         : MIO
 * Module          : io_manager
 * Description     : Header for MIA IOManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 20:40:20 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

#ifndef SRC_APP_MIA_SRC_INCLUDE_MIA_IO_MANAGER_H_
#define SRC_APP_MIA_SRC_INCLUDE_MIA_IO_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "GL/glui.h"
#include "lib/libimgtools/src/include/io_manager.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"
#include "lib/libimgtools/src/include/file_io_factory.h"
#include "lib/libimgtools/src/include/base_gfx_app.h"
/* FIXME: ADDITIONAL INCLUDES AS NECESSARY HERE :-) */

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The manager for I/O operations in MIA. This includes
 * initializing GLUI control elements related to image loading/saving, as well
 * as handling the load/save operations themselves. The load operation includes
 * validating the image type and filesystem permissions before the load will
 * proceed. It also handles loading an image from a file to the stamp.
 */
class MIAIOManager : public IOManager {
 public:
  MIAIOManager();
  ~MIAIOManager() {}

  /**
   * @brief Initialize GLUI control elements for IO management
   *
   * @param glui GLUI handle
   * @param s_gluicallback Callback to install
   * @return The initialized IO panel handle
   */
  GLUI_Panel* InitGlui(const GLUI *const glui,
                       void (*s_gluicallback)(int));

  PixelBuffer* LoadImageToCanvas(void);
  PixelBuffer* LoadImageToCanvas(const std::string& filename);
  PixelBuffer* LoadNextImage(void);
  PixelBuffer* LoadPreviousImage(void);
  void SaveCanvasToFile(const PixelBuffer* curr_canvas);
  void SaveCanvasToFile(const PixelBuffer* curr_canvas,
                        const std::string& file_name);
  std::string next_file_name() {return next_file_name_;};
  std::string prev_file_name() {return prev_file_name_;};
  std::string start_file_name() {return start_file_name_;};
  bool has_next_image() {return has_next_image_;};
  bool has_prev_image() {return has_prev_image_;};
  void set_start_image_file_name(const std::string & start_file_name){
    start_file_name_ = start_file_name;
  }
  void set_image_file(const std::string & fname_in);
  std::string image_name_plus_seq_offset(const std::string& filename,
                                         int offset);

 private:
  const int kDigitCount = 3;

  /* Copy/move assignment/construction disallowed */
  MIAIOManager(const MIAIOManager &rhs) = delete;
  MIAIOManager& operator=(const MIAIOManager &rhs) = delete;

  void prev_image_toggle(bool enabled) {
    UICtrl::button_toggle(prev_image_btn_, enabled);
  }
  void next_image_toggle(bool enabled) {
    UICtrl::button_toggle(next_image_btn_, enabled);
  }

  /* data members */
  GLUI_Button* next_image_btn_;
  GLUI_Button* prev_image_btn_;
  std::string prev_file_name_;
  std::string next_file_name_;
  std::string start_file_name_;
  bool has_next_image_;
  bool has_prev_image_;
};

}  /* namespace image_tools */

#endif  /* SRC_APP_MIA_SRC_INCLUDE_MIA_IO_MANAGER_H_ */
