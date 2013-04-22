//Gk12 Header
#include <gk12.hpp>

//Globals
short joystick_value=0;
bool found_start_bytes=false;

//Setup Function
void setup()
{
	Serial.Open("COM9");
	Serial.Set_baud(57600);
}

//Loop Function
void loop(const double dt)
{
	//If We Haven't Gotten Our Start Bytes
	if(!found_start_byte)
	{
		//Temporary Byte Variable
		char byte;

		//Read a Byte, If Start Bytes are Found, Set Start Bytes Variable
		if(Serial.Read(&bytes,2)==2&&bytes==0x1234)
			found_start_bytes=true;
	}

	//If We've Gotten Our Start Bytes
	else
	{
		//Try to Read the Next Two Bytes, If Successful Reset Start Bytes Variable
		if(Serial.Read(&joystick_value,2)==2)
			found_start_bytes=false;
	}
}

//Draw Function
void draw()
{
}