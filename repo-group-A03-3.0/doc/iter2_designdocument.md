
# Design Justifications for FlashPhoto
#### Group Name:
A03

#### Members: (ordered by last name)
- Wei Chen
- Xinran Duan
- Dawei Luo
- Natnael Seifu

#### Instructions
> Respond to each of the design questions below.  Make your answers factual and compelling.  Where appropriate, reference alternative designs you considered, code snippets, and diagrams within your writing in order to be clear and back up your claims.  As we have discussed in class, when writing with reference to figures make sure to tell the reader what to look for in the diagram or what exactly you want the reader to notice in the code snippet.  Remember that the design of your project is worth 1/3 of the total project grade.  Also remember that when grading the design portion of the project, this design justification document is the only thing we will look at.  This document must stand on its own.  Rather than linking to your actual code, carefully pick the most important code snippets from your project to include here in order to provide convincing detail for your answers to the questions below.  
> A few tips to maximize the success of your design document:  
>   1. Make sure the **description** of your design decision only contains an objective description of how you structured your design and how it was implemented (specifically how your solution solves the problem given in the prompt). Save any arguments in favor of your design for the **justification** section.
>
>   2. Your justification will probably need to compare against at least one alternative, and you will need to provide a compelling argument for why your solution is better than the alternative.
>
>   3. Edit this file when writing your design document. Do not move or rename this file. Do not direct to any outside resources for your images or code. Place all images and code in this document. Please match the formatting of the [Example Design Document](https://github.umn.edu/umn-csci-3081F16/Example-Design-Document/blob/master/doc/DesignDocument.md) and [its source](https://raw.github.umn.edu/umn-csci-3081F16/Example-Design-Document/master/doc/DesignDocument.md?token=AAADyd5L8wd57F_qLX4Nf-2nVvfRlMj5ks5YH-qHwA%3D%3D) as precisely as possible, especially in regards to:
>     - **Formatting code** (do not include images of your code, make sure that your code is formatted with C++ coloring)
>     - **Inserting images**
>     - **Numbered lists for your tutorial**
>     - **Captioning your Figures**
>     - **Including the original prompts in their original quote form**  
>
>  This formatting helps us grade your assignments effectively, and thus failure to meet these requirements may result in point deductions. Any material that is not presented in this design document will not be graded.
>   4. When including a class diagram, only show the classes and members that convey the point you're trying to make. For example, showing the class BaseGfxApp in a UML diagram will probably not be appropriate.





## 1  Design Question One
> This iteration of the project introduces the concept of filters. You had to implement several filters, which fell into two types: pixel-independent (where each pixel is filtered independently), and convolution-based (where filtering a pixel requires information about its neighboring pixels by means of a kernel). Naturally, a key design decision is how these filters are represented. Each filter has a different algorithm for modifying the canvas, and only some of these algorithms require kernels.
> First, in the **Design Description** section below, describe the design you developed to address this challenge. We expect that you will include at least one figure showing the relationships of the classes affected by your design. Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 1.1 Design Description
When we implemented the filter_manager, we had to implement two kinds of filters, including convolution-based filters(five upper ApplyFunction() in the following diagram) and pixel-independent filters(four lower ApplyFunction() in the diagram).            
![Image of Kernel](https://github.umn.edu/umn-csci-3081F16/repo-group-A03/blob/master/doc/images/kernel.png)        
Concrete examples of each type of kernel and its usage context are listed here:                 
![Image of filter](https://github.umn.edu/umn-csci-3081F16/repo-group-A03/blob/master/doc/images/filter.png)

As for the five convolution-based filter ApplyFucntion(), we use a helper function called apply_kernel() to convolve the kernel with that pixel and its neighbors to determine a new color for the pixel. You can replace ApplyEdgeDetect() with any other convolution-based filter method in a subsequent instance, since they share the same approach, “first initialize a particular kernel then call apply_kernel() using that kernel.     

  > ApplyEdgeDetect() function in FilterManager class (src/filter_manager.cc)     
  

``` C++
void FilterManager::ApplyEdgeDetect(PixelBuffer* display_buffer) {
  Kernel* edge_detect_kernel = new KSquare(1, 8, -1);
  apply_kernel(edge_detect_kernel, display_buffer);
}
```

### 1.2 Design Justification
We choose to initialize concrete kernel within the filter method in FilterManager Class once users click the filter buttons. Because we do not know the blur amount, sharpen amount and so on to set the size of kernel until users set the amount value.      
      
  > ApplyBlur() function in FilterManager class (src/filter_manager.cc)           
  
``` C++ 
void FilterManager::ApplyBlur(PixelBuffer* display_buffer) {
  int radius = floor(blur_amount_ / 2);
  Kernel* blur_kernel = new KCross(radius);
  apply_kernel(blur_kernel, display_buffer);
}
```

Since all convolution-based filter methods need to convolve the kernel with pixels in the same way(multiplication and sum), we isolate the kernel that varies with a particular method, and we create a generic class for the kernel.    

  > apply_kernel() function in FilterManager class (src/filter_manager.cc)           
  
``` C++
void FilterManager::apply_kernel(Kernel* kernel, PixelBuffer* buffer) {
  for (int y = 0; y < buffer_height; y++) {
    for (int x = 0; x < buffer_width; x++) {
        for (int kernelY = 0; kernelY < kernel_height; kernelY++) {
          for (int kernelX = 0; kernelX < kernel_width; kernelX++) {
            red += temp_buffer.get_pixel(bufferX, bufferY).red()
             * kernel->get_value(kernelX, kernelY);
    ...
         }
      }
    }
  }
}
```
      
Similarly, we apply helper function in many places, such as in ApplyQuantize, we create ApplyChannelQuantize to avoid duplicate quantize three channels.  

  > ApplyQuantize() function in FilterManager class (src/filter_manager.cc)     
  
``` C++
void FilterManager::ApplyQuantize(PixelBuffer* display_buffer) {
  for (int y = 0; y < display_buffer->height(); y++) {
    for (int x = 0; x < display_buffer->width(); x++) {
      float red;
      float green;
      float blue;
      float alpha;
      ColorData pixel_color = display_buffer->get_pixel(x, y);
      red = ApplyChannelQuantize(pixel_color.red(), bin_size);
      green = ApplyChannelQuantize(pixel_color.green(), bin_size);
      blue = ApplyChannelQuantize(pixel_color.blue(), bin_size);
      alpha = pixel_color.alpha();
      display_buffer->set_pixel(x, y, ColorData(red, green, blue, alpha));
    }
  }
}
```
## 2  Design Question Two
> One common software feature included in this iteration is the undo/redo mechanic, where any modification to the canvas can be reversed, and then optionally re-applied.
> First, in the **Design Description** section below, describe the design you developed to address this challenge.  Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 2.1 Design Description
When a change is applied to the canvas, the canvas before the change is saved and the undo button is toggled on, which continues forming a chain of undo's until the limit is reached.
Redo button comes into action when a single undo action is performed. Redos can also form a chain unless they are broken with new action is performed after an undo. Redos can be done how ever many times undo is done (#Redos = # of Actions undone).

We save canvas every time a user clicks and store the canvas into a stack called undo_vector_. This operation is encapsulated in a method called update_states() which also enable redo_toggle() by setting bool enable_undo = True. When implementing UndoOperation(), we pop out previous canvas which is then assigned to current display_buffer pointer and at the same time, in order to facilitate redo later, we save the state when user clicks undo button into another stack called redo_vector_ and enable the redo_toggle() by setting bool enable_redo_= True. If user redo, pop canvas from redo_vector_ which is assigned to the current display_buffer pointer and push into undo_vector_ again.  
The timing of update_states() is after LeftMouseDown() and filter methods, such as 
UI_APPLY_BLUR, UI_APPLY_SHARP, UI_APPLY_MOTION_BLUR, UI_APPLY_EDGE, UI_APPLY_THRESHOLD, UI_APPLY_DITHER, UI_APPLY_SATURATE, UI_APPLY_CHANNEL, UI_APPLY_QUANTIZE, UI_APPLY_SPECIAL_FILTER.
Once we load another image into display_buffer, we need to be cautious that we need to resize the canvas size also when undo or redo involves different size of canvases. We create a redraw_canvas method to handle this.

  > redraw_canvas()  in FlashPhotoApp class (src/flashphoto_app.cc)
  
``` C++
void FlashPhotoApp::redraw_canvas(PixelBuffer* new_canvas) {
    display_buffer_ = new_canvas;
    this->SetWindowDimensions(display_buffer_->width(),
                              display_buffer_->height());
    this->Display();
}
```
However when we try to assign canvas that is popped out from  undo_vector_ or redo_vector_ to current display_buffer pointer, we need to remove the const declaration of width and height so that we can modify display_buffer’s width and height during the assignment.      
      
  > width_ and height_ declaration in PixelBuffer class (src/include/pixel_buffer.h)
  
``` C++
class PixelBuffer {
private:
  int width_; 
  int height_;
}
```

  > PixelBuffer operation in PixelBuffer class (src/pixel_buffer.cc)
  
``` C++
PixelBuffer& PixelBuffer::operator=(
    const PixelBuffer &rhs) {
  this->width_ = rhs.width();
  this->height_ = rhs.height();
  this->pixels_ = rhs.pixels_;
  this->background_color_ = rhs.background_color_;
  return *this;
} 
```
### 2.2 Design Justification
The first discussion was more on the concept of Undoing and Redoing. Has more to do with what to information to retain when a user decides to have his/her work undone or Redone. The first solution we come up with to tackle this problem was to save the whole canvas when any action is performed. However, it would waste too much memory if we saved the entire canvas because there is a good chance that only a small portion of the canvas will change per single action. The alternative solution was harder and more time-consuming than the first solution. Finally, we have decided that it would be more efficient to save the whole canvas than to determine which canvas has changed, how to save it, and how to write it back.

The second discussion was what structure to use to save chains of canvases. One idea we came up with was to keep a record of all past canvases in an array and have an index back move back and forth when app state is changed. The second idea was to have stack-like structures, such as a vector, for both Undo and Redo. Both ideas are similar and have very little difference memory or time consumption. Finally, we agreed that the second solution would give us more readable codes to anyone and our future selves.

Although we can resize the GLUI window size without creating a helper function called  redraw_canvas(), we can find multiple places to call this helper function in FlashPhotoApp, such as UI_LOAD_CANVAS_BUTTON, UI_UNDO, UI_REDO.

  > places to use redraw_canvas() in FlashPhotoApp class (src/flashphoto_app.cc)
  
``` C++
    case UICtrl::UI_LOAD_CANVAS_BUTTON:
      state_manager_.update_states(display_buffer_);
      redraw_canvas(io_manager_.LoadImageToCanvas());
      break;
    case UICtrl::UI_UNDO:
      state_manager_.UndoOperation(display_buffer_);
      redraw_canvas(display_buffer_);
      break;
    case UICtrl::UI_REDO:
      state_manager_.RedoOperation(display_buffer_);
      redraw_canvas(display_buffer_);
      break;
```

If we dig into the redraw_canvas() function, we can find that Display() called within redraw_canvas() shows some redundancy. If we rewrite the redraw_canvas() as following without Display(), it still runs smoothly.     

  > rewrite redraw_canvas()  in FlashPhotoApp class (src/flashphoto_app.cc)

``` C++
void FlashPhotoApp::redraw_canvas(PixelBuffer* new_canvas) {
    display_buffer_ = new_canvas;
    this->SetWindowDimensions(display_buffer_->width(),
                              display_buffer_->height());
}
```

However, you can find that it is slightly less responsive than the previous version because the previous version requires to “refresh” the canvas once we assign new canvas in  UI_UNDO or UI_LOAD_CANVAS_BUTTON. Without the Display(), we have to wait for the GlUI’s RunMainLoop() to call Display() periodically resulting in potential longer waiting time.      

## 3  Design Question Three
> A new developer on your team must add a new filter to FlashPhoto. This filter is called  _Invert._ This filter performs the following conversion to all pixels in the canvas:
> ```
> newColor's red   = 1 - oldColor's red
> newColor's green = 1 - oldColor's green
> newColor's blue  = 1 - oldColor's blue
> ```
> Describe in the form of a tutorial (including code snippets) exactly what changes would need to be made to your program in order to fully integrate this new filter.

### Programming Tutorial: Adding a New Invert Filter to FlashPhoto
Step 1: Add a new enum for Invert filter as a GLUI Interface element

    > src/include/ui_ctrl.h

``` C++
    enum Type {
    ...
    UI_APPLY_BLUR,
    UI_APPLY_SHARP,
    UI_APPLY_EDGE,
    UI_APPLY_THRESHOLD,
    UI_APPLY_DITHER,
    UI_APPLY_SATURATE,
    UI_APPLY_CHANNEL,
    UI_APPLY_QUANTIZE,
    UI_APPLY_MOTION_BLUR,
    UI_APPLY_SPECIAL_FILTER,
    UI_APPLY_INVERT, // A new enum for the Invert filter
    UI_UNDO,
    UI_REDO,
    UI_QUIT
  };
```

Step 2: Add a new panel for Invert filter on GLUI UI

  > src/filter_manager.cc

``` C++
    void FilterManager::InitGlui(const GLUI *const glui,
                             void (*s_gluicallback)(int)) {
    ...
    GLUI_Panel *specialFilterPanel = new GLUI_Panel(filter_panel, "Emboss");
    {
      new GLUI_Button(specialFilterPanel,
                      "Apply",
                      UICtrl::UI_APPLY_SPECIAL_FILTER,
                      s_gluicallback);
    }

    GLUI_Panel *specialFilterPanel = new GLUI_Panel(filter_panel, "Invert");
    {
      new GLUI_Button(specialFilterPanel,
                      "Apply",
                      UICtrl::UI_APPLY_INVERT, // use the enum for Invert
                      s_gluicallback);
    }
  } /* FilterManager::InitGlui() */
```

Step 3: Create ApplyInvert() to apply Invert effect on canvas

  > src/filter_manager.cc

``` C++
  namespace image_tools {
    ...
    void FilterManager::ApplySpecial(PixelBuffer *display_buffer) {
      std::cout << "Apply has been clicked for Special" << std::endl;
      Kernel* emboss_kernel = new KEmboss(1);
      apply_kernel(emboss_kernel, display_buffer);
    }

    void FilterManager::ApplyInvert(PixelBuffer *display_buffer) {
      std::cout << "Apply has been clicked for Invert" << std::endl;
      for (int x = 0; x < display_buffer->width(); x++) {
        for (int y = 0; y < display_buffer->height(); y++) {
          ColorData pixel_color_ = display_buffer->get_pixel(x, y);
          float red = 1 - pixel_color_.red();     // newColor's red   = 1 - oldColor's red
          float green = 1 - pixel_color_.green(); // newColor's green = 1 - oldColor's green
          float blue = 1 - pixel_color_.blue();   // newColor's blue  = 1 - oldColor's blue
          float alpha = pixel_color_.alpha();
          display_buffer->set_pixel(x, y, ColorData(red, green, blue, alpha));
        }
      }
    }
    ...
  }  /* namespace image_tools */
```

Step 4: Set up that ApplyInvert() will be executed once Invert filter is applied

  > src/flashphoto_app.cc

``` C++
  void FlashPhotoApp::GluiControl(int control_id) {
    switch (control_id) {
      ...
      case UICtrl::UI_APPLY_SPECIAL_FILTER:
        state_manager_.update_states(display_buffer_);
        filter_manager_.ApplySpecial(display_buffer_);
        break;
      case UICtrl::UI_APPLY_SPECIAL_FILTER:
        state_manager_.update_states(display_buffer_);
        filter_manager_.ApplyInvert(display_buffer_);
        break;
      case UICtrl::UI_FILE_BROWSER:
        io_manager_.set_image_file(io_manager_.file_browser()->get_file());
        break;
      ...
    }
    ...
  }
```
