/*******************************************************************************
 * Name            : flashphoto_app.cc
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of FlashPhoto
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/flashphoto_app.h"
#include <cmath>
#include <iostream>
#include "include/color_data.h"
#include "include/pixel_buffer.h"
#include "include/ui_ctrl.h"
#include "include/blur_tool.h"
#include "include/pen.h"
#include "include/eraser.h"
#include "include/spray_paint.h"
#include "include/calligraphy_pen.h"
#include "include/highlighter.h"
#include "include/chalk.h"
#include "include/stamp.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FlashPhotoApp::FlashPhotoApp(int width, int height) : BaseGfxApp(width, height),
                                                      filter_manager_(),
                                                      io_manager_(),
                                                      state_manager_(),
                                                      glui_ctrl_hooks_(),
                                                      display_buffer_(nullptr),
                                                      cur_tool_(0),
                                                      cur_color_red_(0.0),
                                                      cur_color_green_(0.0),
                                                      cur_color_blue_(0.0) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void FlashPhotoApp::Init(
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
  set_caption("FlashPhoto");

  // Initialize Interface
  InitializeBuffers(background_color, width(), height());
  InitializeTools();

  InitGlui();
  InitGraphics();
}

void FlashPhotoApp::Display(void) {
  DrawPixels(0, 0, width(), height(), display_buffer_->data());
}

FlashPhotoApp::~FlashPhotoApp(void) {
  if (display_buffer_) {
      delete display_buffer_;
      for (int i = 0; i < num_tools_; i++) {
          delete tools_[i];
      }
  }
}


void FlashPhotoApp::MouseDragged(int x, int y) {
  ColorData myColor(cur_color_red_, cur_color_green_, cur_color_blue_, 1);
  Tool* tool = tools_[cur_tool_];
  tool->fill(x, y, prev_x_, prev_y_, display_buffer_, myColor);

  prev_x_ = x;
  prev_y_ = y;
}
void FlashPhotoApp::MouseMoved(int x, int y) {}

void FlashPhotoApp::LeftMouseDown(int x, int y) {
  state_manager_.update_states(display_buffer_);
  prev_x_ = x;
  prev_y_ = y;

  ColorData myColor(cur_color_red_, cur_color_green_, cur_color_blue_, 1);
  Tool* tool = tools_[cur_tool_];
  tool->paint(x, (display_buffer_->height() - y), display_buffer_, myColor, 1);
}

void FlashPhotoApp::LeftMouseUp(int x, int y) {
  std::cout << "mouseReleased " << x << " " << y << std::endl;
}

void FlashPhotoApp::InitializeTools() {
    /** Need to change when new tool is added */
    num_tools_ = 8;
    tools_ = new Tool*[num_tools_];
    tools_[0] = new Pen(3, 3);
    tools_[1] = new Eraser(20, 20);
    tools_[2] = new SprayPaint(41, 41);
    tools_[3] = new CalligraphyPen(5, 15);
    tools_[4] = new Highlighter(5, 15);
    tools_[5] = new Stamp(0, 0);
    tools_[6] = new BlurTool(41, 41);
    tools_[7] = new Chalk(20, 20);

    tools_[0]->intializeMask();
    tools_[1]->intializeMask();
    tools_[2]->intializeMask();
    tools_[3]->intializeMask();
    tools_[4]->intializeMask();
    tools_[5]->intializeMask();
    tools_[6]->intializeMask();
    tools_[7]->intializeMask();
}

void FlashPhotoApp::InitializeBuffers(ColorData background_color,
                                      int width, int height) {
  display_buffer_ = new PixelBuffer(width, height, background_color);
}

void FlashPhotoApp::InitGlui(void) {
  // Select first tool (this activates the first radio button in glui)
  cur_tool_ = 0;

  GLUI_Panel *toolPanel = new GLUI_Panel(glui(), "Tool Type");
  {
    GLUI_RadioGroup *radio = new GLUI_RadioGroup(toolPanel, &cur_tool_,
                                                 UICtrl::UI_TOOLTYPE,
                                                 s_gluicallback);
    // Create interface buttons for different tools:
    new GLUI_RadioButton(radio, "Pen");
    new GLUI_RadioButton(radio, "Eraser");
    new GLUI_RadioButton(radio, "Spray Can");
    new GLUI_RadioButton(radio, "Caligraphy Pen");
    new GLUI_RadioButton(radio, "Highlighter");
    new GLUI_RadioButton(radio, "Stamp");
    new GLUI_RadioButton(radio, "Blur");
    new GLUI_RadioButton(radio, "Chalk");
  }

  GLUI_Panel *color_panel = new GLUI_Panel(glui(), "Tool Color");
  {
    cur_color_red_ = 0;
    glui_ctrl_hooks_.spinner_red  = new GLUI_Spinner(color_panel, "Red:",
                                                     &cur_color_red_,
                                                     UICtrl::UI_COLOR_R,
                                                     s_gluicallback);
    glui_ctrl_hooks_.spinner_red->set_float_limits(0, 1.0);

    cur_color_green_ = 0;
    glui_ctrl_hooks_.spinner_green = new GLUI_Spinner(color_panel, "Green:",
                                                      &cur_color_green_,
                                                      UICtrl::UI_COLOR_G,
                                                      s_gluicallback);
    glui_ctrl_hooks_.spinner_green->set_float_limits(0, 1.0);

    cur_color_blue_ = 0;
    glui_ctrl_hooks_.spinner_blue  = new GLUI_Spinner(color_panel, "Blue:",
                                                      &cur_color_blue_,
                                                      UICtrl::UI_COLOR_B,
                                                      s_gluicallback);
    glui_ctrl_hooks_.spinner_blue->set_float_limits(0, 1.0);

    new GLUI_Button(color_panel, "Red", UICtrl::UI_PRESET_RED,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Orange", UICtrl::UI_PRESET_ORANGE,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Yellow", UICtrl::UI_PRESET_YELLOW,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Green", UICtrl::UI_PRESET_GREEN,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Blue", UICtrl::UI_PRESET_BLUE,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Purple", UICtrl::UI_PRESET_PURPLE,
                    s_gluicallback);
    new GLUI_Button(color_panel, "White", UICtrl::UI_PRESET_WHITE,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Black", UICtrl::UI_PRESET_BLACK,
                    s_gluicallback);
  }

  new GLUI_Button(const_cast<GLUI*>(glui()),
                "Quit", UICtrl::UI_QUIT,
                static_cast<GLUI_Update_CB>(exit));

  /* Initialize state management (undo, redo, quit) */
  state_manager_.InitGlui(glui(), s_gluicallback);

  /* Initialize Filtering */
  filter_manager_.InitGlui(glui(), s_gluicallback);

  /* Initialize image I/O */
  io_manager_.InitGlui(glui(), s_gluicallback);
  io_manager_.setIOFactory(new FileIOFactory());
  return;
}

void FlashPhotoApp::GluiControl(int control_id) {
  switch (control_id) {
    case UICtrl::UI_PRESET_RED:
      cur_color_red_ = 1;
      cur_color_green_ = 0;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_PRESET_ORANGE:
      cur_color_red_ = 1;
      cur_color_green_ = 0.5;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_PRESET_YELLOW:
      cur_color_red_ = 1;
      cur_color_green_ = 1;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_PRESET_GREEN:
      cur_color_red_ = 0;
      cur_color_green_ = 1;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_PRESET_BLUE:
      cur_color_red_ = 0;
      cur_color_green_ = 0;
      cur_color_blue_ = 1;
      update_colors();
      break;
    case UICtrl::UI_PRESET_PURPLE:
      cur_color_red_ = 0.5;
      cur_color_green_ = 0;
      cur_color_blue_ = 1;
      update_colors();
      break;
    case UICtrl::UI_PRESET_WHITE:
      cur_color_red_ = 1;
      cur_color_green_ = 1;
      cur_color_blue_ = 1;
      update_colors();
      break;
    case UICtrl::UI_PRESET_BLACK:
      cur_color_red_ = 0;
      cur_color_green_ = 0;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_APPLY_BLUR:
      state_manager_.update_states(display_buffer_);
      filter_manager_.ApplyBlur(display_buffer_);
      break;
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
    case UICtrl::UI_APPLY_DITHER:
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
    case UICtrl::UI_APPLY_SPECIAL_FILTER:
      state_manager_.update_states(display_buffer_);
      filter_manager_.ApplySpecial(display_buffer_);
      break;
    case UICtrl::UI_FILE_BROWSER:
      io_manager_.set_image_file(io_manager_.file_browser()->get_file());
      break;
    case UICtrl::UI_LOAD_CANVAS_BUTTON:
      // redraws canvas with pixel buffer returned
      // from io_manager_'s LoadImageToCanvas method
      state_manager_.update_states(display_buffer_);
      redraw_canvas(io_manager_.LoadImageToCanvas());
      break;
    case UICtrl::UI_LOAD_STAMP_BUTTON: {
      // Special case stamp tools needs to load image
      // Since tools are created from parent class point of view
      // to access special function that only exist in Stamp
      // dynamic_cast is neccessary
      Stamp* temp_conv = dynamic_cast<Stamp *>(tools_[5]);
      temp_conv->loadStampFromFile(io_manager_.LoadImageToStamp());
      break;
    }
    case UICtrl::UI_SAVE_CANVAS_BUTTON:
      io_manager_.SaveCanvasToFile(display_buffer_);
      // Reload the current directory:
      io_manager_.file_browser()->fbreaddir(".");
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

/*******************************************************************************
 * Member Functions For Managing GLUI Interface
 ******************************************************************************/
void FlashPhotoApp::update_colors(void) {
  glui_ctrl_hooks_.spinner_blue->set_float_val(cur_color_blue_);
  glui_ctrl_hooks_.spinner_green->set_float_val(cur_color_green_);
  glui_ctrl_hooks_.spinner_red->set_float_val(cur_color_red_);
}

void FlashPhotoApp::redraw_canvas(PixelBuffer* new_canvas) {
  if (new_canvas != nullptr) {
    display_buffer_ = new_canvas;
    this->SetWindowDimensions(display_buffer_->width(),
                              display_buffer_->height());
    this->Display();
  } else {
    fprintf(stderr, "No Image to Load to canvas\n");
  }
}

void FlashPhotoApp::InitGraphics(void) {
  // Initialize OpenGL for 2D graphics as used in the FlashPhoto App
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
