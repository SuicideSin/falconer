#!/bin/sh
#g++ main.cpp ../file_util.cpp ../string_util.cpp -O -Wall -o main -std=c++11
g++ main.cpp ../../osl/serial.cpp ../2d.cpp ../2d_util.cpp ../glut_input.cpp ../glut_ui.cpp ../font.cpp ../sprite.cpp ../string_util.cpp -o main -O -Wall -lGL -lGLU -lglut -lGLEW -lglui -lSOIL
#g++ example.cpp -o example -O -Wall -lGL -lGLU -lglut -lGLEW -lglui -lSOIL
#wine ~/.wine/drive_c/Program\ Files/CodeBlocks/MinGW/bin/g++.exe main.cpp ../file_util.cpp ../string_util.cpp -O -Wall -o main.exe