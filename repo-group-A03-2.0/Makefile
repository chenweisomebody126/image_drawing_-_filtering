# MAKEFILE FOR FLASHPHOTO APP - CSCI3081W - FALL 2016

#COMPILER_FLAGS_1 = -pedantic -Werror -Wswitch-default
COMPILER_FLAGS_2 = -Wfloat-equal -Wold-style-cast -W -Wall -Wextra -Weffc++ -std=c++11
ALL_COMPILER_FLAGS = $(COMPILER_FLAGS_1) $(COMPILER_FLAGS_2)

SRCDIR = ./src
OBJDIR = ./obj
BINDIR = ./bin
INCDIR = $(SRCDIR)/include
EXE = $(BINDIR)/FlashPhoto
GOOGLE_STYLE_EXE = ./ext/cpplint/cpplint.py --linelength=81

FLASHPHOTO_INC_CXX = $(wildcard $(INCDIR)/*.h)
FLASHPHOTO_SRC_CXX = $(wildcard $(SRCDIR)/*.cc)
FLASHPHOTO_OBJECT_CXX = $(patsubst $(SRCDIR)/%.cc, $(OBJDIR)/%.o, $(FLASHPHOTO_SRC_CXX))

CLEAN_EXT_FOLDER_PATH = ./ext/lib ./ext/share ./ext/include bin obj

# MAKEFILE PATH FOR LIB ARCHIVES NEEDED TO COMPILE
GLUI_MAKE_PATH = ext/glui/
JPEG_MAKE_PATH = ext/jpeg-9a/
PNG_MAKE_PATH = ext/libpng-1.6.16/

#ALL PATHS OF HEADER FILES NEEDED TO COMPILE
OBJECTS_INCLUDE_PATH = -I./src/
GLUI_INCLUDE_PATH = -I./ext/glui/include/
JPEG_INCLUDE_PATH = -I./ext/
PNG_INCLUDE_PATH = -I./ext/
ALL_INCLUDE_PATHS = $(OBJECTS_INCLUDE_PATH) $(GLUI_INCLUDE_PATH)
ALL_INCLUDE_PATHS += $(JPEG_INCLUDE_PATH) $(PNG_INCLUDE_PATH)

LIB_PATH = -L./ext/glui/lib/ -L./ext/lib/
LIBS_LINKED_WITH = -lglut -lGL -lGLU -lglui -ljpeg -lpng -lz

# DEPENDACIES ARE ARCHIVES SO MAKE CAN RECOGNIZE IF THEY EXIST OR NOT
LIB = ext/glui/lib/libglui.a ext/lib/libjpeg.a ext/lib/libpng.a
CLEAN_DEPENDANCIES = make_glui_clean make_jpeg_clean make_png_clean


all: $(LIB) $(EXE)

clean: $(CLEAN_DEPENDANCIES)
	rm -rf $(CLEAN_EXT_FOLDER_PATH)

# Google style checker
# This target will fail since it doesn't need to out put anything
style:
	$(GOOGLE_STYLE_EXE) $(FLASHPHOTO_INC_CXX) $(FLASHPHOTO_SRC_CXX)


$(EXE): $(FLASHPHOTO_OBJECT_CXX) | $(BINDIR) $(OBJDIR)
	g++ -I. -o $@ $^ $(LIB_PATH) $(LIBS_LINKED_WITH)

$(OBJDIR)/%.o: $(SRCDIR)/%.cc $(INCDIR)/%.h | $(OBJDIR)
	g++ $(ALL_COMPILER_FLAGS) $(ALL_INCLUDE_PATHS) -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cc | $(OBJDIR)
	g++ $(ALL_COMPILER_FLAGS) $(ALL_INCLUDE_PATHS) -c -o $@ $<

# MAKE LIBS
ext/glui/lib/libglui.a:
	make -C $(GLUI_MAKE_PATH) all

ext/lib/libjpeg.a:
	make -C $(JPEG_MAKE_PATH) all install

ext/lib/libpng.a:
	make -C $(PNG_MAKE_PATH) all install

bin obj:
	mkdir -p $@


# CLEAN LIBS
make_glui_clean:
	make -C $(GLUI_MAKE_PATH) clean

make_jpeg_clean:
	make -C $(JPEG_MAKE_PATH) clean

make_png_clean:
	make -C $(PNG_MAKE_PATH) clean
