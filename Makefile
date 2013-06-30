MSL=src/msl/2d.cpp src/msl/2d_util.cpp src/msl/font.cpp src/msl/glut_input.cpp src/msl/socket.cpp src/msl/socket_util.cpp src/msl/sprite.cpp src/msl/string_util.cpp src/msl/time_util.cpp
SRC=src/example.cpp src/falconer.cpp $(MSL)
OPTS=-O -Wall
LIB=-lGL -lGLU -lGLEW -lglui -lglut -lSOIL -lavcodec -lswscale -lavutil
COMPILER=g++
OUT=bin

all: falconer

falconer: $(SRC)
	$(COMPILER) $(CFLAGS) $(SRC) $(LIB) $(OPTS) -o $(OUT)/$@

clean:
	rm -rf $(OUT)/falconer