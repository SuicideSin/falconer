//GK12 Graphics Header
//	Created By:		Mike Moss
//	Modified On:	02/22/2013

//This requires GLEW and GLUT to work!

//Begin Define Guards
#ifndef GK12_H
#define GK12_H

//2D Graphics Header
#include "../2d.hpp"

//Math Header
#include <math.h>

//String Header
#include <string>

//Namespaces (Yea I know...namespace pollution...)
using namespace msl;
using namespace std;

//Function Declarations
void setup();
void loop(const double dt);
void draw();

//External Variables
extern std::string window_title;
extern msl::color background_color;

//End Define Guards
#endif