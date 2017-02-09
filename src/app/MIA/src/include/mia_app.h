/*******************************************************************************
> * Name            : mia_app.h
 * Project         : MIA
 * Module          : App
 * Description     : Header file for MIA class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 5/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_APP_MIA_SRC_INCLUDE_MIA_APP_H_
#define SRC_APP_MIA_SRC_INCLUDE_MIA_APP_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "lib/libimgtools/src/include/base_gfx_app.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"
#include "lib/libimgtools/src/include/state_manager.h"
#include "lib/libimgtools/src/include/tool.h"
#include "app/MIA/src/include/mia_filter_manager.h"
#include "app/MIA/src/include/mia_io_manager.h"

/* FIXME: ADDITIONAL INCLUDES AS NECESSARY HERE :-) */

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This is a graphics applications class for Medical Images that is
 * built on top of the GLUT and GLUI toolkits and utilize libimgtools library.
 */
class MIAApp : public BaseGfxApp {
 public:
  MIAApp(int width, int height, const std::string& marker_fname);
  virtual ~MIAApp(void);

  void MouseDragged(int x, int y);
  void MouseMoved(int x, int y) {}
  void LeftMouseDown(int x, int y);
  void LeftMouseUp(int x, int y) {}
  void Display(void);
  void GluiControl(int control_id);

  /**
   * @brief Initialize MIA
   *
   * @param[in] argc Unused--required by BaseGfxApp
   * @param[in] argv Unused--required by BaseGfxApp
   * @param[in] x Unused--required by BaseGfxApp
   * @param[in] y Unused--required by BaseGfxApp
   * @param[in] background_color The initial canvas color
   */
  void Init(
      int argc,
      char *argv[],
      int x,
      int y,
      ColorData background_color);

 private:
  /**
   * @brief Initialize the GLUI interface
   *
   */
  void InitGlui(void);
  void InitGraphics(void);

  /**
   * @brief Initialize the buffers for the main window
   */
  void InitializeBuffers(ColorData initial_color,
                         int width, int height);

  /**
   * @Brief When adding new Tool:
   *      - increment number of tools
   *      - instanciate tool and added to tools array
   *      - number of tools is essential for clean exit and
   *	      prevent memory leak.
   * @caution index of tools corresponds to how the UI tools
   *          radio buttons are placed.
   *          top button (0) to bottom button (num_tools_)
   */
  void InitializeTools();
  /**
   * @Brief Changes the current canvas to new image
   *        set size of canvas to the new image size
   *        and redraws canvas.
   */
  void redraw_canvas(PixelBuffer* new_canvas);

  /* Copy/move assignment/construction disallowed */
  MIAApp(const MIAApp &rhs) = delete;
  MIAApp& operator=(const MIAApp &rhs) = delete;

  /**
   * @brief Manager for all filter operations
   */
  MIAFilterManager filter_manager_;

  /**
   * @brief Manager for all I/O operations
   */
  MIAIOManager io_manager_;

  /**
   * @brief Manager for redo/undo stack
   */
  StateManager state_manager_;

  // This is the pointer to the buffer where the display PixelBuffer is stored
  PixelBuffer* display_buffer_;

  // The path to the marker file
  std::string marker_fname_;

  int cur_tool_;

  // stores position of mouse one step before current position
  // drag only
  int prev_x_;
  int prev_y_;

  int num_tools_; /** Allocation size */
  Tool** tools_; /** Hook for accessing Tools */
};

}  /* namespace image_tools */

#endif  // SRC_APP_MIA_SRC_INCLUDE_MIA_APP_H_
