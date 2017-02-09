/*******************************************************************************
 * Name            : io_manager.cc
 * Project         : FlashPhoto
 * Module          : io_manager
 * Description     : Implementation of FlashPhotoIOManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 20:47:05 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <assert.h>
#include <iostream>
#include <sstream>
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"
#include "lib/libimgtools/src/include/file_io.h"
#include "lib/libimgtools/src/include/file_io_factory.h"
#include "lib/libimgtools/src/include/io_manager.h"
#include "app/FlashPhoto/src/include/flashphoto_io_manager.h"

/* FIXME: ADDITIONAL INCLUDES AS NECESSARY HERE :-) */

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FlashPhotoIOManager::FlashPhotoIOManager(void) :
    IOManager() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
GLUI_Panel* FlashPhotoIOManager::InitGlui(const GLUI *const glui,
                         void (*s_gluicallback)(int)) {
  new GLUI_Column(const_cast<GLUI*>(glui), true);
  GLUI_Panel *image_panel = new GLUI_Panel(const_cast<GLUI*>(glui),
                                           "Image I/O");
  AddFileBrowserToGLUI(image_panel, s_gluicallback);
  AddSaveCanvasToGLUI(image_panel, s_gluicallback);
  AddLoadStampToGLUI(image_panel, s_gluicallback);
  new GLUI_Separator(image_panel);
  return image_panel;
}

}  /* namespace image_tools */
