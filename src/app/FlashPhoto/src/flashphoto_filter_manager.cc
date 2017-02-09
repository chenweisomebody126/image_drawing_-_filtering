/*******************************************************************************
 * Name            : flashphoto_filter_manager.cc
 * Project         : flashphoto
 * Module          : filter_manager
 * Description     : Implementation of FlashPhotoFilterManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 18:47:02 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <cmath>
#include "lib/libimgtools/src/include/ui_ctrl.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/kernel.h"
#include "lib/libimgtools/src/include/k_cross.h"
#include "lib/libimgtools/src/include/k_line.h"
#include "lib/libimgtools/src/include/k_square.h"
#include "lib/libimgtools/src/include/k_emboss.h"
#include "lib/libimgtools/src/include/filter_manager.h"
#include "app/FlashPhoto/src/include/flashphoto_filter_manager.h"
/* FIXME: ADDITIONAL INCLUDES AS NECESSARY HERE :-) */

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FlashPhotoFilterManager::FlashPhotoFilterManager(void) :
    FilterManager() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
GLUI_Panel* FlashPhotoFilterManager::InitGlui(const GLUI *const glui,
                             void (*s_gluicallback)(int)) {
  new GLUI_Column(const_cast<GLUI*>(glui), true);
  GLUI_Panel *filter_panel = new GLUI_Panel(const_cast<GLUI*>(glui), "Filters");
  {
    AddBlurToGLUI(filter_panel, s_gluicallback);
    AddMotionBlurToGLUI(filter_panel, s_gluicallback);
    AddSharpenToGLUI(filter_panel, s_gluicallback);
    AddEdgeDetectToGLUI(filter_panel, s_gluicallback);
    AddThresholdToGLUI(filter_panel, s_gluicallback);
    new GLUI_Column(filter_panel, true);
    AddSaturationToGLUI(filter_panel, s_gluicallback);
    AddChannelToGLUI(filter_panel, s_gluicallback);
    AddQuantizationToGLUI(filter_panel, s_gluicallback);
    GLUI_Panel *specialFilterPanel = new GLUI_Panel(filter_panel, "Emboss");
    {
      new GLUI_Button(specialFilterPanel,
                      "Apply",
                      UICtrl::UI_APPLY_SPECIAL_FILTER,
                      s_gluicallback);
    }
  }

  return filter_panel;
} /* FlashPhotoFilterManager::InitGlui() */

}  /* namespace image_tools */
