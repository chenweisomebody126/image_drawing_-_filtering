/*******************************************************************************
 * Name            : mia_app.cc
 * Project         : MIA
 * Module          : App
 * Description     : Implementation of MIA
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 5/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <iostream>
#include <cmath>
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"
#include "lib/libimgtools/src/include/pen.h"
#include "lib/libimgtools/src/include/stamp.h"
#include "app/MIA/src/include/mia_app.h"

/* FIXME: ADDITIONAL INCLUDES AS NECESSARY HERE :-) */

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MIAApp::MIAApp(int width, int height,
               const std::string& marker_fname) : BaseGfxApp(width, height),
                   filter_manager_(),
                   io_manager_(),
                   state_manager_(),
                   display_buffer_(nullptr),
                   marker_fname_(marker_fname),
                   cur_tool_(0) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void MIAApp::Init(
    int argc,
    char* argv[],
    int x,
    int y,
    ColorData background_color) {
  BaseGfxApp::Init(argc, argv,
                   x, y,
                   GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH,
                   true,
                   width()+51,
                   50);

  // Set the name of the window
  set_caption("MIA");

  // Initialize Interface
  InitializeBuffers(background_color, width(), height());
  InitializeTools();

  InitGlui();
  InitGraphics();
}

void MIAApp::Display(void) {
  DrawPixels(0, 0, width(), height(), display_buffer_->data());
}

MIAApp::~MIAApp(void) {
  if (display_buffer_) {
    delete display_buffer_;
    for (int i = 0; i < num_tools_; i++) {
      delete tools_[i];
    }
  }
}


void MIAApp::MouseDragged(int x, int y) {
  ColorData penColor(1.0, 0.0, 0.0, 1);
  Tool* tool = tools_[cur_tool_];
  tool->fill(x, y, prev_x_, prev_y_, display_buffer_, penColor);

  prev_x_ = x;
  prev_y_ = y;
}

void MIAApp::LeftMouseDown(int x, int y) {
  state_manager_.update_states(display_buffer_);
  prev_x_ = x;
  prev_y_ = y;

  ColorData penColor(1.0, 0.0, 0.0, 1);
  Tool* tool = tools_[cur_tool_];
  tool->paint(x, (display_buffer_->height() - y), display_buffer_, penColor, 1);
}

void MIAApp::InitializeTools() {
  /** Need to change when new tool is added */
  num_tools_ = 2;
  tools_ = new Tool*[num_tools_];
  tools_[0] = new Pen(3, 3);
  tools_[0]->intializeMask();


  tools_[1] = new Stamp(0, 0);
  tools_[1]->intializeMask();
  Stamp* temp_conv = dynamic_cast<Stamp *>(tools_[1]);
  PixelBuffer* marker = io_manager_.LoadImageToStamp(marker_fname_);
  if (marker != nullptr) {
    temp_conv->loadStampFromFile(marker);
  } else {
    fprintf(stderr, "Unable to read Marker image: %s\n",
            marker_fname_.c_str());
  }
}

void MIAApp::InitializeBuffers(ColorData background_color,
                               int width, int height) {
  display_buffer_ = new PixelBuffer(width, height, background_color);
}

void MIAApp::InitGlui(void) {
  // Select first tool (this activates the first radio button in glui)
  cur_tool_ = 0;

  new GLUI_Column(glui(), false);
  GLUI_Panel *tool_panel = new GLUI_Panel(glui(), "Tool Type");
  {
    GLUI_RadioGroup *radio = new GLUI_RadioGroup(tool_panel, &cur_tool_,
                                                 UICtrl::UI_TOOLTYPE,
                                                 s_gluicallback);
    // Create interface buttons for different tools:
    new GLUI_RadioButton(radio, "Pen");
    new GLUI_RadioButton(radio, "Marker");
  }

  /* Initialize state management (undo, redo, quit) */
  state_manager_.InitGlui(glui(), s_gluicallback);

  new GLUI_Button(const_cast<GLUI*>(glui()),
                  "Quit", UICtrl::UI_QUIT,
                  static_cast<GLUI_Update_CB>(exit));

  /* Initialize Filtering */
  filter_manager_.InitGlui(glui(), s_gluicallback);

  /* Initialize image I/O */
  io_manager_.InitGlui(glui(), s_gluicallback);
  return;
}

void MIAApp::GluiControl(int control_id) {
  switch (control_id) {
    case UICtrl::UI_APPLY_SHARP:
      state_manager_.update_states(display_buffer_);
      filter_manager_.ApplySharpen(display_buffer_);
      break;
    case UICtrl::UI_APPLY_MOTION_BLUR:
      state_manager_.update_states(display_buffer_);
      filter_manager_.ApplyMotionBlur(display_buffer_);
      break;
    case UICtrl::UI_APPLY_EDGE:
      state_manager_.update_states(display_buffer_);
      filter_manager_.ApplyEdgeDetect(display_buffer_);
      break;
    case UICtrl::UI_APPLY_THRESHOLD:
      state_manager_.update_states(display_buffer_);
      filter_manager_.ApplyThreshold(display_buffer_);
      break;
    case UICtrl::UI_APPLY_SATURATE:
      state_manager_.update_states(display_buffer_);
      filter_manager_.ApplySaturate(display_buffer_);
      break;
    case UICtrl::UI_APPLY_CHANNEL:
      state_manager_.update_states(display_buffer_);
      filter_manager_.ApplyChannel(display_buffer_);
      break;
    case UICtrl::UI_APPLY_QUANTIZE:
      state_manager_.update_states(display_buffer_);
      filter_manager_.ApplyQuantize(display_buffer_);
      break;
    case UICtrl::UI_APPLY_BLUR:
      state_manager_.update_states(display_buffer_);
      filter_manager_.ApplyBlur(display_buffer_);
      break;
    case UICtrl::UI_FILE_BROWSER:
      io_manager_.set_image_file(io_manager_.file_browser()->get_file());
      break;
    case UICtrl::UI_LOAD_CANVAS_BUTTON:
      state_manager_.update_states(display_buffer_);
      redraw_canvas(io_manager_.LoadImageToCanvas());
      break;
    case UICtrl::UI_LOAD_STAMP_BUTTON: {
      Stamp* temp_conv = dynamic_cast<Stamp *>(tools_[1]);
      io_manager_.set_image_file(marker_fname_);
      temp_conv->loadStampFromFile(io_manager_.LoadImageToStamp());
      break;
    }
    case UICtrl::UI_SAVE_CANVAS_BUTTON:
      io_manager_.SaveCanvasToFile(display_buffer_);
      // Reload the current directory:
      io_manager_.file_browser()->fbreaddir(".");
      break;
    case UICtrl::UI_NEXT_IMAGE_BUTTON:
      state_manager_.update_states(display_buffer_);
      redraw_canvas(io_manager_.LoadNextImage());
      break;
    case UICtrl::UI_PREV_IMAGE_BUTTON:
      state_manager_.update_states(display_buffer_);
      redraw_canvas(io_manager_.LoadPreviousImage());
      break;
    case UICtrl::UI_FILE_NAME:
      io_manager_.set_image_file(io_manager_.file_name());
      break;
    case UICtrl::UI_UNDO:
      state_manager_.UndoOperation(display_buffer_);
      redraw_canvas(display_buffer_);
      break;
    case UICtrl::UI_REDO:
      state_manager_.RedoOperation(display_buffer_);
      redraw_canvas(display_buffer_);
      break;
    default:
      break;
  }

  // Forces canvas to update changes made in this function
  glui()->post_update_main_gfx();
}

void MIAApp::redraw_canvas(PixelBuffer* new_canvas) {
  if (new_canvas != nullptr) {
    display_buffer_ = new_canvas;
    this->SetWindowDimensions(display_buffer_->width(),
                              display_buffer_->height());
    this->Display();
  } else {
    fprintf(stderr, "No Image to Load to canvas\n");
  }
}

void MIAApp::InitGraphics(void) {
  // Initialize OpenGL for 2D graphics as used in the BrushWork app
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(0, width(), 0, height());
  glViewport(0, 0, width(), height());
}


}  /* namespace image_tools */
