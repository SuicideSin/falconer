#include "falconer.hpp"

#include "msl/string_util.hpp"
#include <time.h>

ardrone::ardrone(const std::string ip):_count(1),_control_socket(ip+":5556"),_navdata_socket(ip+":5554"),_video_socket(ip+":5555"),
	_battery_percent(0),_landed(true),_emergency_mode(false),_low_battery(false),_ultrasonic_enabled(false),_video_enabled(false),
	_motors_good(false),_pitch(0),_roll(0),_yaw(0),_altitude(0)
{}

ardrone::operator bool() const
{
	return (_control_socket&&_navdata_socket);
}

bool ardrone::connect(unsigned int time_out)
{
	bool connected=false;

	if(!*this)
	{
		_control_socket.connect_udp();
		_navdata_socket.connect_udp();
		_video_socket.connect_tcp();

		unsigned int time_start=time(0);
		char redirect_navdata_command[14]={1,0,0,0,0,0,0,0,0,0,0,0,0,0};
		char video_wakeup_command[1]={1};

		do
		{
			_navdata_socket.write(redirect_navdata_command,14);
			_video_socket.write(video_wakeup_command,1);
		}
		while(time(0)-time_start<time_out&&(_navdata_socket.check()<=0||_video_socket.check()<=0));

		if(_navdata_socket.check()>0&&_video_socket.check()>0)
			connected=true;
	}

	if(*this)
	{
		_count=1;

		std::string initialize_command="AT*FTRIM="+msl::to_string(_count)+"\r";
		++_count;
		_control_socket<<initialize_command;

		std::string outdoor_hull_command="AT*CONFIG="+msl::to_string(_count)+",\"control:outdoor\",\"FALSE\"\r";
		++_count;
		_control_socket<<outdoor_hull_command;

		std::string shell_is_on_command="AT*CONFIG="+msl::to_string(_count)+",\"control:flight_without_shell\",\"TRUE\"\r";
		++_count;
		_control_socket<<shell_is_on_command;

		std::string motor_type_command="AT*CONFIG="+msl::to_string(_count)+",\"control:brushless\",\"TRUE\"\r";
		++_count;
		_control_socket<<motor_type_command;

		std::string navdata_enable_command="AT*CONFIG="+msl::to_string(_count)+",\"general:navdata_demo\",\"FALSE\"\r";
		++_count;
		_control_socket<<navdata_enable_command;

		std::string navdata_send_all_command="AT*CONFIG="+msl::to_string(_count)+",\"general:navdata_options\",\"65537\"\r";
		++_count;
		_control_socket<<navdata_send_all_command;

		std::string watchdog_command="AT*COMWDG="+msl::to_string(_count)+"\r";
		++_count;
		_control_socket<<watchdog_command;

		std::string altitude_min_command="AT*CONFIG="+msl::to_string(_count)+",\"control:altitude_min\",\"10\"\r";
		++_count;
		_control_socket<<altitude_min_command;

		std::string altitude_max_command="AT*CONFIG="+msl::to_string(_count)+",\"control:altitude_max\",\"4000\"\r";
		++_count;
		_control_socket<<altitude_max_command;
	}

	return (connected&&*this);
}

void ardrone::navdata_update()
{
	if(*this)
	{
		const int packet_size=548;			//nav-data-full packet size=548, nav-data-demo packet size=24
		uint8_t byte[packet_size];

		if(_navdata_socket.check()>0&&_navdata_socket.read(byte,packet_size))
		{
			if(byte[0]==0x88&&byte[1]==0x77&&byte[2]==0x66&&byte[3]==0x55)
			{
				unsigned int states=byte[7]<<24|byte[6]<<16|byte[5]<<8|byte[4]<<0;
				_landed=!static_cast<bool>(states&(1<<0));
				_emergency_mode=static_cast<bool>(states&(1<<31));
				_low_battery=static_cast<bool>(states&(1<<15));
				_ultrasonic_enabled=!static_cast<bool>(states&(1<<21));
				_video_enabled=static_cast<bool>(states&(1<<1));
				_motors_good=!static_cast<bool>(states&(1<<12));

				int header=byte[17]<<8|byte[16]<<0;

				if(header==0)
				{
					for(unsigned char ii=0;ii<4;++ii)
					{
						reinterpret_cast<uint8_t*>(&_battery_percent)[ii]=byte[24+ii];
						reinterpret_cast<uint8_t*>(&_pitch)[ii]=byte[28+ii];
						reinterpret_cast<uint8_t*>(&_roll)[ii]=byte[32+ii];
						reinterpret_cast<uint8_t*>(&_yaw)[ii]=byte[36+ii];
						reinterpret_cast<uint8_t*>(&_altitude)[ii]=byte[40+ii];
					}
				}
			}
		}
	}
}

void ardrone::video_update()
{
	if(*this)
	{
	}
}

void ardrone::land()
{
	if(*this)
	{
		int land_flags=1<<18|1<<20|1<<22|1<<24|1<<28;
		std::string command="AT*REF="+msl::to_string(_count)+","+msl::to_string(land_flags)+"\r";
		++_count;
		_control_socket<<command;
	}
}

void ardrone::emergency_mode_toggle()
{
	if(*this)
	{
		int emergency_flags=1<<8|1<<18|1<<20|1<<22|1<<24|1<<28;
		std::string command="AT*REF="+msl::to_string(_count)+","+msl::to_string(emergency_flags)+"\r";
		++_count;
		_control_socket<<command;
	}
}

void ardrone::takeoff()
{
	if(*this)
	{
		int takeoff_flags=1<<9|1<<18|1<<20|1<<22|1<<24|1<<28;
		std::string command="AT*REF="+msl::to_string(_count)+","+msl::to_string(takeoff_flags)+"\r";
		++_count;
		_control_socket<<command;
	}
}

void ardrone::manuever(const float altitude,const float pitch,const float roll,const float yaw)
{
	if(*this)
	{
		float inverted_roll=roll*-1.0;
		float inverted_pitch=pitch*-1.0;
		float inverted_yaw=yaw*-1.0;

		bool hover=false;
		std::string command="AT*PCMD="+msl::to_string(_count)+",1,"+msl::to_string(*(int*)(&inverted_roll))+","+msl::to_string(*(int*)(&inverted_pitch))
			+","+msl::to_string(*(int*)(&altitude))+","+msl::to_string(*(int*)(&inverted_yaw))+"\r";
		++_count;
		_control_socket<<command;
	}
}

void ardrone::hover()
{
	if(*this)
	{
		std::string command="AT*PCMD="+msl::to_string(_count)+",0,0,0,0,0\r";
		++_count;
		_control_socket<<command;
	}
}

unsigned int ardrone::battery_percent() const
{
	return _battery_percent;
}

bool ardrone::flying() const
{
	return !_landed;
}

bool ardrone::emergency_mode() const
{
	return _emergency_mode;
}

bool ardrone::low_battery() const
{
	return _low_battery;
}

bool ardrone::ultrasonic_enabled() const
{
	return _ultrasonic_enabled;
}

bool ardrone::motors_good() const
{
	return _motors_good;
}

int ardrone::altitude() const
{
	return _altitude;
}

float ardrone::pitch() const
{
	return _pitch;
}

float ardrone::roll() const
{
	return _roll;
}

float ardrone::yaw() const
{
	return _yaw;
}