#Design Justifications for the Brush Work App 

####Group Name: 
- A03

#### Members: 
- Xinran Duan 
- Wei Chen 
- Natnael Seifu

#### Instructions 
> Respond to each of the design questions below.  Make your answers factual and compelling.  Where appropriate, reference alternative designs you considered, code snippets, and diagrams within your writing in order to be clear and back up your claims.  As we have discussed in class, when writing with reference to figures make sure to tell the reader what to look for in the diagram or what exactly you want the reader to notice in the code snippet.  Remember that the design of your project is worth 1/3 of the total project grade.  Also remember that when grading the design portion of the project, this design justification document is the only thing we will look at.  This document must stand on its own.  Rather than linking to your actual code, carefully pick the most important code snippets from your project to include here in order to provide convincing detail for your answers to the questions below.


## 1  Design Question One
> This iteration of the project is all about tools. Naturally, a key design decision is how these tools are represented. Each tool has several characteristics, including the shape of the tool, its size, and the way it blends with the canvas when the tool is applied. Some tools share characteristics with other tools, such as how the pen and calligraphy pen tools blend with the canvas in the same manner. 
> First, in the **Design Description** section below, describe the design you developed to address this challenge. We expect that you will include at least one figure showing the relationships of the classes affected by your design. Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 1.1 Design Description
Brushwork application can have from one to any number of tools, but there is only ONE active tool at a time. So we developed a generic tool class and its child tool classes. The generic tool class stores mask width, height and has two functions called paint() and fill().

> Key variables and methods within the generic tool class(include/tool.h)
	
  ``` C++
	class Tool {
	 public:
	  virtual void fill(int x, int y, int prev_x, int prev_y, PixelBuffer* canvas, ColorData curr_color);
	  virtual void paint(int x, int y, PixelBuffer* canvas, ColorData curr_color);
	 protected:
	  int mask_width_;
	  int mask_height_;
	  float** mask_;
	};
	} 
  ```

> The UML class diagram for The UML class diagram for Tool class and its child classes

![alt "UML Diagram for Tools"](https://github.umn.edu/umn-csci-3081F16/repo-group-A03/blob/master/doc/images/UML.png)

Once BrushWork starts, it initializes an array of tools and records active tool index. 

> Tool Initialization (src/BrushWorkApp.cc)
	
  ``` C++
	int cur_tool_; /*< Currently selected tool from UI  */
	void BrushWorkApp::InitializeTools(){
	    tools_ = new Tool*[6];
	    tools_[0] = new Pen();
	    tools_[1] = new Eraser();
	    tools_[2] = new SprayPaint();
	    tools_[3] = new CalligraphyPen();
	    tools_[4] = new Highlighter();
	    tools_[5] = new Chalk(); ///special tool
	}
  ```

Once user click or drag the mouse, program first call paint() using current tool index. When it is just short click, paint() is just called once to color the pixel around the mask. However, if user drag the mouse, fill() function is called which iteratively calls paint() to fill colors in the gap along the drawing path. 

![alt "Case Diagram"](https://github.umn.edu/umn-csci-3081F16/repo-group-A03/blob/master/doc/images/case_diagram.PNG)

However, we can see spray can class overwrites fill() function, Because its color should not be as tense as other tools, like pen: 

> fill() function in generic tool class (src/tool.cc)
	
  ``` C++
	  void Tool::fill(int x, int y , int prev_x_, int prev_y_, PixelBuffer* canvas, ColorData curr_color){
	    while (prev_x_<x || prev_y_< y){// remember we use converted y, new_prev_y goes top to down
	      paint(prev_x_, prev_y_, canvas, myColor);
	      prev_x=min(x,prev_x_+mask_width_);
	      prev_y=min(y,prev_y_+mask_height_);
	    }
	  }
  ```
	
> fill() function difference in Spray can class(src/spray_paint.cc)
	
  ``` C++
	void SprayPaint::fill(int x, int y , int prev_x, int prev_y,PixelBuffer* canvas, ColorData curr_color){
		float horizontal_dist = static_cast<float>(x - prev_x);
		    	float vertical_dist = static_cast<float>(y - prev_y)
		slope = vertical_dist / horizontal_dist;
		    	intercept = y - (slope * x);
			int FILL_GAP = 2;
		...
	        	new_x += (sign_x * FILL_GAP);
	        	new_y = (slope * new_x) + intercept;
		...
	}
  ```

In Eraser, we overwrites its paint() function

> paint() function in generic tool class(src/tool.cc)
	
  ``` C++
	  void Tool::paint(int x, int y, PixelBuffer* canvas, ColorData curr_color) {
	        ColorData new_color = (canvas->get_pixel(a + i, b + j) * (1 - mask_[j][i])) + (curr_color * mask_[j][i]);
	        canvas->set_pixel(a + i, b + j, new_color);
	      }
	    }
	  }
	}
  ```
	
> paint() function difference in Eraser tool class (src/eraser.cc)
	
  ``` c++
	void Eraser::paint(int x, int y, PixelBuffer* canvas, ColorData curr_color) {
	...
		  ColorData new_color = canvas->get_pixel(a+i, b+j) * (1 - mask_[i][j]);
	...
	}
  ```
  
### 1.2 Design Justification
During the design procedure, we have encountered several cases satisfying the requirements. 
First, BrushWork has exact ONE generic tool class which serve as a basic class for specific tools. 
We have two options to initialize active tool. One is initialize it once the user chooses it. 
The other one is to initialize all tools at first and store them in an array(heap) instead of stack. 
In order to responds fast, we choose the second one, so that the mask associated with tools 
can be precomputed to save computation time, especially when switching the tool.
Second, when the mask interacts with PixelBuffer, pen, calligraphy pen, highlighter, spray 
share same interaction way by assigning new color to mask around current location. 
Although eraser is different in that it does not paint at all, but erase, we leverage 
template model to accommodate both paint and erase operations by setting user-specified 
color as background color, just like “tea & coffee recipe” example in lecture. We put paint 
function in generic tool class other than individual child tool classes.

![alt "Paint Function"](https://github.umn.edu/umn-csci-3081F16/repo-group-A03/blob/master/doc/images/paint_description.PNG)

Literally, in order to feed background color into user-specified color argument, we can either 
pass a tool name to inform function paint() of tool name or directly overwrite paint() in Eraser class. 
We choose the latter one, because we hope that the generic tool class could be more independent of 
Brushwork class without setting specific tool name in order to maintain its high abstraction level. 
In addition, since there is only one tool different, overwriting paint() in individual tool level can 
help avoid affecting other tools by accidence.
###Code for compare overwrite and if-else

> Option1: if-else to assign background color to eraser in generic tool class’s paint() 
	
  ``` C++
	void Tool::paint(int x, int y, PixelBuffer* canvas, ColorData curr_color, int cur_tool_) {
		if(cur_tool_==1) {//Eraser  
			ColorData change_color=canvas->get_pixel(x,y)
		}
		Else{//other tools
			...
		}
	}
  ```
	
> Option 2: overwrite paint() in Eraser class’s paint()
	
  ``` C++
	  void Eraser::paint(int x, int y, PixelBuffer* canvas, ColorData curr_color) {
		new_color = new_color + (canvas->background_color() * mask_[i][j]);
	}
  ```

When the mouse is dragged, there are gaps between color points. In order to fill the gap, 
we also put fill() function in generic tool class, because most tools share same arguments and 
similar interaction with PixelBuffer.
 
![alt "Fill Function"](https://github.umn.edu/umn-csci-3081F16/repo-group-A03/blob/master/doc/images/fill_description.PNG)

## 2  Design Question Two
> Unlike most of the tools, the Eraser returns the canvas to its original color. One of the challenges in this iteration is giving the eraser the authority or information required to have this effect while having minimal impact on the way the rest of the tools are defined. 
> First, in the **Design Description** section below, describe the design you developed to address this challenge.  Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 2.1 Design Description
In order to draw on canvas using background color instead of currently selected color, the Eraser 
needs to have a paint function that is slightly different from the paint function inherited from the 
genetic tool class.

Similar to other tools, the Eraser needs to know the x-y coordinate, canvas, and background color 
to paint, while the paint function inherited from the genetic tool class have x-y coordinates, canvas, 
and currently selected color as parameters. The background color of canvas can be accessed by using a 
public getter function in PixelBuffer. Therefore, the existing paint function with its parameters could provide the 
Eraser with enough information to paint on canvas.

> include/tool.h
	
  ``` C++  
	class Tool {
	 public:
	 ...
	 // the paint function defined in the genetic tool class
	 // this function is inherited by all tools and can be overridden as needed 
	  virtual void paint(int x, int y, PixelBuffer* canvas, ColorData curr_color);
	 ...
	};
  ```
Also, all tools including Eraser paint in the same way: applying its mask around the x-y coordinate 
based on new color, existing colors on canvas and opacities provided by mask. The only difference 
between Eraser and other tools is Eraser will use background color to calculate new colors canvas 
pixels, rather than use currently selected color.

> src/tool.cc
	
  ``` C++  
	...
	  
	  /// The paint function inherited to all tools
	  /// This function is used by tools that apply currently selected color to paint
	  void Tool::paint(int x, int y, PixelBuffer* canvas, ColorData curr_color) {
	    int a = x - floor(mask_width_/2);
	    int b = y - floor(mask_height_/2);
	
	    for (int i = 0; i < mask_width_; i ++) {
	      for (int j = 0; j < mask_height_; j++) {
	        if ((a + i >= 0) && (a + i < canvas->width()) &&
	            (b + j >= 0) && (b + j < canvas->height())) {
	              // currently selected color is used to calculate new color for a pixel
	              ColorData new_color = (canvas->get_pixel(a + i, b + j)
	                * (1 - mask_[j][i])) + (curr_color * mask_[j][i]);
	              canvas->set_pixel(a + i, b + j, new_color);
	          }
	        }
	      }
	    }
	    
	   ...
  ```

> Genetic new color calculation formula for all tools:

> new_canvas_color = tool_color * intensity + canvas_color * (1.0- intensity)

> New color calculation formula used in paint function inherited from genetic tool class:

> new_canvas_color = currenly_selected_color * intensity + canvas_color * (1.0- intensity)

> New color calculation formula used by Eraser:

> new_canvas_color = background_color * intensity + canvas_color * (1.0- intensity)

Based on above analysis, our design is to let the Eraser class to have an overridden paint function that 
will apply background color on canvas.

### 2.2 Design Justification
The paint function overridden in Eraser will have the same parameters as the paint function inherited from 
the genetic paint function. The background color that Eraser uses is accessed in the overridden paint function 
by calling background_color(), which is a public getter for the background color of a PixelBuffer, and the 
background color is used to calculate new canvas colors. The pros of this design is when mouse is clicked or 
dragged, the right paint function and color will be used to paint according to which tool is selected, without 
any extra checking (e.g. If-else, or switch), because the inheritance relationship between tools and the genetic 
tool class will decide which function to call. Because the paint function is defined in the genetic tool class, 
if new tools are added, there will be a default paint function for them. Also, since it is allowed to override 
the paint function is defined in the genetic tool class, new tools can override it based on its functionalities 
and will not affect other tools.

> src/eraser.cc
	
  ``` C++  
	void Eraser::paint(int x, int y, PixelBuffer* canvas, ColorData curr_color) {
	    // top-left coordinates relative to (x,y) on canvas
	    int a = x - floor(mask_width_ / 2);
	    int b = y - floor(mask_height_ / 2);
	
	    for (int i = 0; i < mask_width_; i ++) {
	      for (int j = 0; j < mask_height_; j++) {
	        if ((a + i >= 0) && (a + i < canvas->width()) &&
	                (b + j >= 0) && (b + j < canvas->height())) {
	          ColorData new_color = canvas->get_pixel(a+i, b+j) * (1 - mask_[i][j]);
	          new_color = new_color + (canvas->background_color() * mask_[i][j]);
	          canvas->set_pixel(a + i, b + j, new_color);
	        }
	      }
	    }
	  }
  ```

## 3  Design Question Three
> A new developer on your team must add a new tool to BrushWork. This tool is called  _Pencil._ This tool is a single, non-transparent pixel that completely replaces the existing colors on the canvas in the same way as the pen or calligraphy pen blend.  
> Describe in the form of a tutorial (including code snippets) exactly what changes would need to be made to your program in order to fully integrate this new tool.

### Programming Tutorial: Adding a New Pencil Tool to BrushWork

1. Write your Pencil class’s .h file and place it in the “include” directory. 
Pencil class should extend from Tool class. 
Pencil class should be place in “image_tools” namespace
All destruction of classes are handled in Tool class.

	> include/pencil.h

  ``` C++
	namespace image_tools {
		Class Pencil : public Tool {
			...
		};
	}  // namespace image_tools
  ```
2. In Tool class, parent class which Pencil is inheriting from, has a field called “mask”. 
This field is initialized in each tool. It is what is going to be drawn on to the canvas by 
the paint method. Mask is a two dimensional array of floats. In the constructor of pencil:
Allocate memory for “mask_” (is a field that exists in Tool class) from the heap. 
Initialize each element of “mask_” with floating numbers to the pattern of a pencil. I.e the 
smaller the value the less opaque the current color that is to be drawn.
Place implementation for pencil.h in the “src” directory.
           
	> src/pencil.cc

  ``` C++
	...
	
	/// Allocate memory for mask
	mask_ = ...	
	
	/// This can be used to Initialize. OPTIONAL
	mask_ = {{0.5, 1.0, 0.5},    
		    {1.0, 1.0, 1.0},
		    {0.5, 1.0, 0.5}};
	...
  ```
	> if mask was used to paint over canvas, it will have an effect that will look like the
	  following: 
	
	![alt "Effect of mask"](https://github.umn.edu/umn-csci-3081F16/repo-group-A03/blob/master/doc/images/mask_effect.PNG)

3. Pencil class needs to be instantiated and added to the tools_** field of main
Brushwork app. This is done through InitializeTools() method in brushwork app.
Go to InitializeTools() in the brushwork_app.cc
Increment num_tools_ by number of tools added. 
Initialize Pencil to the correct index of tools_.
CAUTION: index corresponds to UI. be careful on index position of your tool on tool_ array
	    
	> src/brushwork_app.cc

  ``` C++
	...
	 
	/// Add new Tool at the appropriate index
	void BrushWorkApp::InitializeTools() {
		/// Increment num_tools_ by number of tools added
		/// Needed for creating and destroying tools. IMPORTANT
		num_tools_ = 6;  
		tools_ = new Tool*[num_tools_];
		tools_[0] = new Pen();
		tools_[1] = new Eraser();
		tools_[2] = new SprayPaint();
		tools_[3] = new CalligraphyPen();
		tools_[4] = new Highlighter();
		tools_[5] = new Chalk();
		Tools_[appropriate index] =  /// Initialize your tool here
	}

	...
  ```
	> End of Tutorial

		


           
