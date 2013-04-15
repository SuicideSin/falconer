#include <iostream>
#include "msl/socket.hpp"
#include "msl/string_util.hpp"
#include "msl/2d.hpp"
#include <string>
#include "falconer.hpp"

ardrone a;
msl::socket video("192.168.1.1:5555");

int main()
{
	msl::start_2d("ardrone",640,480);
	return 0;
}

void setup()
{
	if(a.connect())
	{
		std::cout<<":)"<<std::endl;
	}
	else
	{
		std::cout<<":("<<std::endl;
		exit(0);
	}

	video.connect_tcp();
}

void loop(const double dt)
{
	a.navdata_update();
	video<<0;

	if(video.check()>0)
	{
		uint8_t byte;

		if(video.read(&byte,1))
			std::cout<<std::hex<<(unsigned int)byte<<std::endl;
	}

	float speed=0.8;
	float pitch=0;
	float roll=0;
	float altitude=0;
	float yaw=0;

	if(msl::input_check(kb_escape))
		exit(0);

	if(msl::input_check_pressed(kb_r))
		a.emergency_mode_toggle();

	if(msl::input_check(kb_w))
		pitch=-speed;

	if(msl::input_check(kb_s))
		pitch=speed;

	if(msl::input_check(kb_a))
		roll=-speed;

	if(msl::input_check(kb_d))
		roll=speed;

	if(msl::input_check(kb_q))
		yaw=-speed;

	if(msl::input_check(kb_e))
		yaw=speed;

	if(msl::input_check(kb_up))
		altitude=speed;

	if(msl::input_check(kb_down))
		altitude=-speed;

	if(msl::input_check_pressed(kb_space))
	{
		if(a.flying())
			a.land();
		else
			a.takeoff();
	}

	a.manuever(altitude,pitch,roll,yaw);

	a.video_update();
}

void draw()
{
	std::string data;
	data+="Battery:\t"+msl::to_string(a.battery_percent())+"%\n";
	data+="Pitch:\t\t"+msl::to_string(a.pitch())+"\n";
	data+="Roll:\t\t"+msl::to_string(a.roll())+"\n";
	data+="Yaw:\t\t"+msl::to_string(a.yaw())+"\n";
	data+="Altitude:\t"+msl::to_string(a.altitude())+"\n";

	if(a.emergency_mode())
		data+="Emergency Mode\n";

	if(a.low_battery())
		data+="Low Battery\n";

	if(!a.motors_good())
		data+="Bad Motor\n";

	if(a.flying())
		data+="Flying\n";
	else
		data+="Landed\n";

	msl::draw_text(-msl::window_width/2.0,msl::window_height/2.0,data);
}