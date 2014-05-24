#!/bin/bash

#Compiler
COMPILER="g++"

#Sources
#Falconer
FALCONER_DIR="."
FALCONER="src/example.cpp $(FALCONER_DIR)/falconer.cpp"

#MSL
MSL_DIR="src/msl"
MSL="$(MSL_DIR)/2d.cpp $(MSL_DIR)/2d_util.cpp \
$(MSL_DIR)/glut_input.cpp $(MSL_DIR)/glut_ui.cpp \
$(MSL_DIR)/socket.cpp $(MSL_DIR)/socket_util.cpp \
$(MSL_DIR)/sprite.cpp $(MSL_DIR)/string_util.cpp \
$(MSL_DIR)/time_util.cpp"

#SOIL
SOIL_DIR="src/SOIL"
SOIL="$(SOIL_DIR)/stb_image_aug.c $(SOIL_DIR)/SOIL.c"

#Full Source
SRC="$(FALCONER) $(HAGGARD) $(MSL) $(SOIL)"

#Libraries
#GL
ifeq ($(shell uname),Darwin)
	OS_GL=-framework OpenGL -framework Glew -framework GLUT
else
	OS_GL=-lGL -lGLU -lglut -lGLEW
endif

#PThread
PTHREAD="-lpthread"

#Full Libraries
LIB="-lftgl $(OS_GL) $(PTHREAD)"

#Binary Name
BIN="-o bin/falconer"

#Compiler Flags
CFLAGS="-O -Wall"

#Search Directories
DIRS="-I. -I./src -I/usr/local/include -L/usr/local/lib -I/usr/include/freetype2"

all: falconer

falconer:
	$(COMPILER) $(SRC) $(LIB) $(BIN) $(CFLAGS) $(DIRS)

clean:
	rm -rf $(OUT)/falconer
