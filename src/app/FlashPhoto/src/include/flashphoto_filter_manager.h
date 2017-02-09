/*******************************************************************************
 * Name            : flashphoto_filter_manager.h
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Header for FlashPhotoFilterManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 18:40:20 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

#ifndef SRC_APP_FLASHPHOTO_SRC_INCLUDE_FLASHPHOTO_FILTER_MANAGER_H_
#define SRC_APP_FLASHPHOTO_SRC_INCLUDE_FLASHPHOTO_FILTER_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
/* FIXME: ADDITIONAL INCLUDES AS NECESSARY HERE :-) */
#include "GL/glui.h"
#include "lib/libimgtools/src/include/filter_manager.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"
#include "lib/libimgtools/src/include/kernel.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Manager for all aspects of filters in FlashPhoto, including
 * initialization of GLUI control elements for filters, filter creation,
 * application, deletion.
 */
class FlashPhotoFilterManager : public FilterManager {
 public:
  FlashPhotoFilterManager();

  GLUI_Panel* InitGlui(const GLUI *const glui,
                       void (*s_gluicallback)(int));
};

}  /* namespace image_tools */

#endif  // SRC_APP_FLASHPHOTO_SRC_INCLUDE_FLASHPHOTO_FILTER_MANAGER_H_
