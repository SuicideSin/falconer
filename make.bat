@ECHO OFF

set MSL=src/msl/2d.cpp src/msl/2d_util.cpp src/msl/font.cpp src/msl/glut_input.cpp src/msl/socket.cpp src/msl/socket_util.cpp src/msl/sprite.cpp src/msl/string_util.cpp src/msl/time_util.cpp
set SOIL=windows\mingw\include\SOIL\SOIL.c windows\mingw\include\SOIL\stb_image_aug.c
set SRC=src/example.cpp src/falconer.cpp %MSL% %SOIL%
set OPTS=-O -Wall -Wno-unknown-pragmas -static-libgcc -static-libstdc++
set LIB=-lopengl32 -lglu32 -lfreeglut -lfreeglut_static -lglew32 -lwsock32 -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lx264 -ltheoraenc -logg -ltheoradec -lswscale
set COMPILER=windows\mingw\bin\g++.exe
set OUT=bin

REM BUILD VARIABLES
	SET BUILD_FALCONER=0
	SET BUILD_CLEAN=0

REM CHECK COMMAND LINE OPTIONS
	SET ARGC=0
	FOR %%i IN (%*) do (
		SET /a ARGC+=1
		IF %%i==all SET BUILD_FALCONER=1
		IF %%i==falconer SET BUILD_FALCONER=1
		IF %%i==clean SET BUILD_CLEAN=1
	)

	IF %BUILD_CLEAN%==1 SET BUILD_FALCONER=0
	IF %ARGC%==0 SET BUILD_FALCONER=1

REM BUILD WHAT IS NEEDED
	IF %BUILD_FALCONER%==1 %COMPILER% %SRC% %LIB% %OPTS% -o %OUT%/falconer.exe
	IF %BUILD_CLEAN%==1 DEL /Q %OUT%\falconer.exe