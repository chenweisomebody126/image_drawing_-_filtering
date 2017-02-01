#Not Needed for now
#BRUSH_SRC_CXX += src/base_gfx_app.cc
#BRUSH_SRC_CXX += src/brushwork_app.cc
#BRUSH_SRC_CXX += src/color_data.cc
#BRUSH_SRC_CXX += src/main.cc
#BRUSH_SRC_CXX += src/pixel_buffer.cc

C++_VERSION = -std=c++11

BRUSH_OBJECT_CXX += obj/base_gfx_app.o
BRUSH_OBJECT_CXX += obj/brushwork_app.o
BRUSH_OBJECT_CXX += obj/tool.o
BRUSH_OBJECT_CXX += obj/pen.o
BRUSH_OBJECT_CXX += obj/calligraphy_pen.o
BRUSH_OBJECT_CXX += obj/highlighter.o
BRUSH_OBJECT_CXX += obj/chalk.o
BRUSH_OBJECT_CXX += obj/eraser.o
BRUSH_OBJECT_CXX += obj/spray_paint.o
BRUSH_OBJECT_CXX += obj/color_data.o
BRUSH_OBJECT_CXX += obj/pixel_buffer.o
BRUSH_OBJECT_CXX += obj/main.o

GLUI_MAKE = ext/glui/
GLUI_INCLUDE_PATH = -I./ext/glui/include/
GLUI_LIB_PATH = -L./ext/glui/lib/

all: bin/brushwork

bin/brushwork: $(BRUSH_OBJECT_CXX) | make_glui bin
	g++ -I. -o $@ $^ $(GLUI_LIB_PATH) -lglut -lGL -lGLU -lglui
obj/%.o: src/%.cc include/%.h | obj
	g++ $(C++_VERSION) -I. $(GLUI_INCLUDE_PATH) -c -o $@ $<
obj/%.o: src/%.cc | obj
	g++ $(C++_VERSION) -I. $(GLUI_INCLUDE_PATH) -c -o $@ $<
make_glui:
	make -C $(GLUI_MAKE)
bin obj:
	mkdir -p $@

clean: lib_clean
	rm -rf bin obj brushwork
lib_clean:
	make -C $(GLUI_MAKE) clean
