MSL=src/msl/2d.cpp src/msl/2d_util.cpp src/msl/glut_input.cpp src/msl/socket.cpp src/msl/socket_util.cpp src/msl/sprite.cpp src/msl/string_util.cpp src/msl/time_util.cpp
SRC=src/example.cpp falconer.cpp $(MSL)
OPTS=-O -Wall -I/usr/include/freetype2
LIB=-lGL -lGLU -lGLEW -lglut -lSOIL -lavcodec -lswscale -lavutil -lftgl
COMPILER=g++
OUT=bin
DIRS=-Isrc -I.

all: falconer

falconer: $(SRC)
	$(COMPILER) $(CFLAGS) $(DIRS) $(SRC) $(LIB) $(OPTS) -o $(OUT)/$@

clean:
	rm -rf $(OUT)/falconer
