#include "../2d.hpp"
#include "../sprite.hpp"
#include <math.h>
#include "../glut_ui.hpp"
#include "font.hpp"
#include "../../osl/serial.h"
#include <iostream>

int main()
{
	msl::start_2d("test",320,240);
	return 0;
}
using namespace msl;


































//GK12 Animate a Sprite Example
//      Created By:     Mike Moss
//      Modified On:    02/25/2013

//This example animates and moves a sprite with the keyboard arrow keys.

//GK12 Header
#include <gk12.hpp>
#include <iostream>
using namespace std;

//Window Settings
std::string window_title="Move!";
color background_color(0.5,0.5,0.5);

//Create stuff here

//Animation Variables
bool idle=true;                 //Boolean value to show idle or run sprite.
double frame=0;                 //Current frame variable.
double animation_speed=10;      //Animation speed variable.
double boostTime = 0;
double boostTimeLength = .3;
bool boosting = false;
bool boostKeyDown = false;
double boostCoolDownLength = 7;
double boostCoolDown = boostCoolDownLength;
short valueFromBuffer = 0;
short modifiedValueFromBuffer = 0;

//Moving Variables
double x,y=0;                   //X position variable.
double running_speed=80;        //Running speed variable.
double facing_direction=1;      //Facing direction variable.

short lowerMovementBound = 200;
short upperMovementBound = 700;

//Setup Function
void setup()
{
        //Initialize stuff here
        Serial.Open("COM12");
        Serial.Set_baud(57600);
}

short readShort()
{
        int bytes = 0;
        short value = 0;
        if(Serial.Read((uint8_t*)&bytes, 1) == 1 && bytes == 0xef)
        {
                Serial.Read((uint8_t*)&value, 2);
                Serial.Input_discard();
        }

        return value;
}

//Loop Function
void loop(const double dt)
{
        //Move stuff here
        valueFromBuffer = readShort();
        cout<<"Value: "<< valueFromBuffer<<endl;
        if(valueFromBuffer != 0)
        {
                //cout<<"Value: "<< valueFromBuffer<<endl;
                modifiedValueFromBuffer = valueFromBuffer;
        }

        //Escape key closes program.
        if(input_check(kb_escape))
                exit(0);

        //Right arrow key sets our direction to the right (1) and adds speed.
        if(modifiedValueFromBuffer > upperMovementBound)
        {
                facing_direction=1;
                x+=running_speed*dt;
        }

        //Left arrow key sets our direction to the left (-1) and subtracts speed.
        else if(modifiedValueFromBuffer < lowerMovementBound)
        {
                facing_direction=-1;
                x-=running_speed*dt;
        }

        if(input_check(kb_up))
        {
                y+=running_speed*dt;
        }

        if(input_check(kb_down))
        {
                y-=running_speed*dt;
        }
        if(input_check(kb_a) && !boostKeyDown && boostCoolDown >= boostCoolDownLength)
        {
                boostKeyDown = true;
                boosting = true;
        }
        else if(!input_check(kb_a))
        {
                boostKeyDown = false;
        }

        //When the right or left arrow key is down switch to run sprite
(idle=false) and animate sprite.
        //if(((input_check(kb_right)||input_check(kb_left))&&!(input_check(kb_right)&&input_check(kb_left)))
|| ((input_check(kb_up)||input_check(kb_down))&&!(input_check(kb_up)&&input_check(kb_down))))
        if(valueFromBuffer < lowerMovementBound && valueFromBuffer >
upperMovementBound)
        {
                idle=false;
                frame+=animation_speed*dt;
        }

        //Else reset animation to idle sprite.
        else
        {
                idle=true;
                frame=0;
        }

        //Limit our frames to 4 frames (the animation only has 4 frames).
        if(frame>4)
                frame=0;

        if(boostCoolDown < boostCoolDownLength) boostCoolDown += dt;
        if(boostTime > boostTimeLength)
        {
                boostTime = 0;
                boosting = false;
                animation_speed = 10;
        }
        if(boosting)
        {
                x += facing_direction * running_speed * dt + (facing_direction *
boostTime * 1.5);
                boostTime += dt;
                boostCoolDown = 0;
                animation_speed = 50;
        }
}

//Draw Function
void draw()
{
        //Draw stuff here

        //Load sprites (static means do something once and then never again)
        static sprite mm_idle("mm_idle.png");
        static sprite mm_run("mm_run.png",4);

        draw_circle(-250,200,20,color(0,0,0));
        draw_circle(-250,200,boostCoolDown/(boostCoolDownLength / 20.0),color(1,0,0));

        //If idling show idle sprite.
        if(idle)
        {
                mm_idle.draw(x,y,0,0,facing_direction);
        }

        //Else if running show running sprite.
        else
        {
                mm_run.draw(x,y,0,0,facing_direction);
        }
}