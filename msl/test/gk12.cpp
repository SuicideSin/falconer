//GK12 Graphics Source
//	Created By:		Mike Moss
//	Modified On:	02/26/2013

//This requires GLEW and GLUT to work!

//Definitions for "gk12.hpp"
#include "gk12.hpp"

//Exception Header
#include <stdexcept>

//IO Stream Header
#include <iostream>

//Default Main
int main()
{
	//Try Code
	try
	{
		//Newline for Portable Compiler
		std::cout<<std::endl;

		//Create 2D Engine
		start_2d(window_title,1024,768,true,background_color);
	}

	//Catch Errors
	catch(std::exception& e)
	{
		//Print Error
		std::cout<<"Error!\t"<<e.what()<<std::endl;
	}

	//All Done
	return 0;
}
