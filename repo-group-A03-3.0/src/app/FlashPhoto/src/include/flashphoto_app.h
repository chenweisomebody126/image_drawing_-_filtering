/*******************************************************************************
 * Name            : flashphoto_app.h
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Header file for FlashPhotoApp class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_APP_FLASHPHOTO_SRC_INCLUDE_FLASHPHOTO_APP_H_
#define SRC_APP_FLASHPHOTO_SRC_INCLUDE_FLASHPHOTO_APP_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "app/FlashPhoto/src/include/flashphoto_io_manager.h"
#include "app/FlashPhoto/src/include/flashphoto_filter_manager.h"
#include "lib/libimgtools/src/include/base_gfx_app.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/filter_manager.h"
#include "lib/libimgtools/src/include/io_manager.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"
#include "lib/libimgtools/src/include/state_manager.h"
#include "lib/libimgtools/src/include/tool.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This is a graphics applications class for Flash Photo built on top of
 * the GLUT and GLUI toolkits.
 */
class FlashPhotoApp : public BaseGfxApp {
 public:
  FlashPhotoApp(int width, int height);
  virtual ~FlashPhotoApp(void);

  /**
   * @brief The function that will be called when mouse is dragged.
   */
  void MouseDragged(int x, int y);

  /**
   * @brief The function that will be called when mouse is moved.
   */
  void MouseMoved(int x, int y);

  /**
   * @brief The function that will be called when left click is down.
   */
  void LeftMouseDown(int x, int y);

  /**
   * @brief The function that will be called when left click is up.
   */
  void LeftMouseUp(int x, int y);
  void Display(void);
  void GluiControl(int control_id);

  /**
   * @brief Initialize the FlashPhotoApp
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
   * @brief Update the colors displayed on the GLUI control panel after updating
   * their values in FlashPhoto
   *
   */
  void update_colors(void);

  /**
   * @brief Initialize the GLUI interface
   *
   */
  void InitGlui(void);

  /**
   * @brief Initialize OpenGL
   *
   */
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
     *        prevent memory leak.
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
  FlashPhotoApp(const FlashPhotoApp &rhs) = delete;
  FlashPhotoApp& operator=(const FlashPhotoApp &rhs) = delete;

  /**
   * @brief Manager for all filter operations
   */
  FlashPhotoFilterManager filter_manager_;

  /**
   * @brief Manager for all I/O operations
   */
  FlashPhotoIOManager io_manager_;

  /**
   * @brief Manager for redo/undo stack
   */
  StateManager state_manager_;

  /**
   * @brief A collection of GLUI spinners for RGB control elements.
   */
  struct {
    GLUI_Spinner *spinner_red;
    GLUI_Spinner *spinner_green;
    GLUI_Spinner *spinner_blue;
  } glui_ctrl_hooks_;

  /** Pointer to pixel data for the screen */
  PixelBuffer *display_buffer_;

  // These are used to store the selections from the GLUI user interface
  int cur_tool_;  /**< Currently selected tool from UI */

  float cur_color_red_;
  float cur_color_green_;
  float cur_color_blue_;

  // stores position of mouse one step before current position
  // drag only
  int prev_x_;
  int prev_y_;

  int num_tools_; /** Allocation size */
  Tool** tools_; /** Hook for accessing Tools */
};

}  /* namespace image_tools */

#endif  // SRC_APP_FLASHPHOTO_SRC_INCLUDE_FLASHPHOTO_APP_H_
