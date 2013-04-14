#include "msl/socket.hpp"
#include <string>

class ardrone
{
	public:
		ardrone(const std::string ip="192.168.1.1");
		operator bool() const;
		bool connect(unsigned int time_out=1);
		void navdata_update();
		void land();
		void emergency_mode_toggle();
		void takeoff();
		void manuever(const float altitude,const float pitch,const float roll,const float yaw);
		void hover();
		unsigned int battery_percent() const;
		bool flying() const;
		bool emergency_mode() const;
		bool low_battery() const;
		bool ultrasonic_enabled() const;
		bool motors_good() const;
		float pitch() const;
		float roll() const;
		float yaw() const;
		int altitude() const;

	private:
		unsigned int _count;
		msl::socket _control_socket;
		msl::socket _navdata_socket;
		std::string _navdata_buffer;
		unsigned int _battery_percent;
		bool _landed;
		bool _emergency_mode;
		bool _low_battery;
		bool _ultrasonic_enabled;
		bool _video_enabled;
		bool _motors_good;
		int _altitude;
		float _pitch;
		float _roll;
		float _yaw;
};