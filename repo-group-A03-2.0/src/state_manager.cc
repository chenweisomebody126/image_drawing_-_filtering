/*******************************************************************************
 * Name            : state_manager.cc
 * Project         : FlashPhoto
 * Module          : state_manager
 * Description     : Implementation of StateManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Sun Oct 2 20:47:05 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/state_manager.h"
#include <iostream>
#include <vector>
#include "include/pixel_buffer.h"
#include "include/ui_ctrl.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
StateManager::StateManager(void) :
    undo_btn_(nullptr),
    redo_btn_(nullptr),
    enable_undo_(false),
    enable_redo_(false) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void StateManager::InitGlui(const GLUI *const glui,
                            void (*s_gluicallback)(int)) {
  undo_btn_ = new GLUI_Button(const_cast<GLUI*>(glui), "Undo", UICtrl::UI_UNDO,
                              s_gluicallback);
  undo_toggle(enable_undo_);

  redo_btn_  = new GLUI_Button(const_cast<GLUI*>(glui), "Redo", UICtrl::UI_REDO,
                               s_gluicallback);
  redo_toggle(enable_redo_);
}

void StateManager::UndoOperation(PixelBuffer *curr_state) {
  std::cout << "Undoing..." << std::endl;
  // active redo buttom
  if (!enable_redo_) {
    enable_redo_ = true;
    redo_toggle(enable_redo_);
  }
  std::cout << undo_vector_.size() << std::endl;
  PixelBuffer undo_state = undo_vector_.back();
  redo_vector_.push_back(*curr_state);
  *curr_state = undo_state;
  undo_vector_.pop_back();

  // after erase undo state from vector, if undo_counter equal to 0,
  // then disable undo buttom.
  if (undo_vector_.size() == 0) {
    enable_undo_ = false;
    undo_toggle(enable_undo_);
  }
}

void StateManager::RedoOperation(PixelBuffer *curr_state) {
  std::cout << "Redoing..." << std::endl;
  // active undo buttom
  if (!enable_undo_) {
    enable_undo_ = true;
    undo_toggle(enable_undo_);
  }

  std::cout << redo_vector_.size() << std::endl;
  PixelBuffer redo_state = redo_vector_.back();
  undo_vector_.push_back(*curr_state);
  *curr_state = redo_state;
  redo_vector_.pop_back();

  // after erase undo state from vector, if undo_counter equal to 0,
  // then disable undo buttom.
  if (redo_vector_.size() == 0) {
    enable_redo_ = false;
    redo_toggle(enable_redo_);
  }
}

void StateManager::update_states(PixelBuffer *curr_state) {
  // Step 1: active undo and disable undo buttom
  if (enable_redo_) {
    enable_redo_ = false;
    redo_toggle(enable_redo_);
  }
  if (!enable_undo_) {
    enable_undo_ = true;
    undo_toggle(enable_undo_);
  }
  // Step 2: store cuur_state to undo_vector_
  undo_vector_.push_back(*curr_state);
  // if it reaches the max_size_ remove the first element
  std::cout << "undo_vector_ size is: " << undo_vector_.size() << std::endl;
  if (undo_vector_.size() > max_size_) {
    std::cout << "  size reach max!!" << std::endl;
    // delete undo_vector_[0];
    undo_vector_.erase(undo_vector_.begin());
    std::cout << "  now size is: " << undo_vector_.size() << std::endl;
  }

  // STEP 3: remove all the elements in redo_vector_
  if (redo_vector_.size() != 0) {
    std::cout << "redo_vector_ size is: " << redo_vector_.size() << std::endl;
    redo_vector_.clear();
    std::cout << "  now size is: " << redo_vector_.size() << std::endl;
  }
}

}  /* namespace image_tools */
