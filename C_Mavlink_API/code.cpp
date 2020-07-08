#include "code.h"
#include <bits/stdc++.h>
using namespace std;
void
set_position(float x, float y, float z, mavlink_set_position_target_local_ned_t &sp)
{
	sp.type_mask =
		MAVLINK_MSG_SET_POSITION_TARGET_LOCAL_NED_POSITION;

	sp.coordinate_frame = MAV_FRAME_LOCAL_NED;

	sp.x   = x;
	sp.y   = y;
	sp.z   = z;

	printf("POSITION SETPOINT XYZ = [ %.4f , %.4f , %.4f ] \n", sp.x, sp.y, sp.z);

}

/*
 * Set target local ned velocity
 *
 * Modifies a mavlink_set_position_target_local_ned_t struct with target VX VY VZ
 * velocities in the Local NED frame, in meters per second.
 */
void
set_velocity(float vx, float vy, float vz, mavlink_set_position_target_local_ned_t &sp)
{
	sp.type_mask =
		MAVLINK_MSG_SET_POSITION_TARGET_LOCAL_NED_VELOCITY     ;

	sp.coordinate_frame = MAV_FRAME_LOCAL_NED;

	sp.vx  = vx;
	sp.vy  = vy;
	sp.vz  = vz;

	printf("VELOCITY SETPOINT UVW = [ %.4f , %.4f , %.4f ] \n", sp.vx, sp.vy, sp.vz);

}

/*
 * Set target local ned acceleration
 *
 * Modifies a mavlink_set_position_target_local_ned_t struct with target AX AY AZ
 * accelerations in the Local NED frame, in meters per second squared.
 */
void
set_acceleration(float ax, float ay, float az, mavlink_set_position_target_local_ned_t &sp)
{

	// NOT IMPLEMENTED
	fprintf(stderr,"set_acceleration doesn't work yet \n");
	throw 1;


	sp.type_mask =
		MAVLINK_MSG_SET_POSITION_TARGET_LOCAL_NED_ACCELERATION &
		MAVLINK_MSG_SET_POSITION_TARGET_LOCAL_NED_VELOCITY     ;

	sp.coordinate_frame = MAV_FRAME_LOCAL_NED;

	sp.afx  = ax;
	sp.afy  = ay;
	sp.afz  = az;
}

void
Autopilot_Interface::
change_mode(int mode_num)
{

	mavlink_message_t message;
	mavlink_msg_set_mode_pack(255, 1, &message,3, 1, mode_num);
	//mavlink_msg_set_mode_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               //uint8_t target_system, uint8_t base_mode, uint32_t custom_mode)
	// Send the message
	port->write_message(message);

}

void
Autopilot_Interface::
change_param(int autopilotid, const char paramid , float paramval, int type )
{

	mavlink_message_t message;
	mavlink_msg_param_set_pack(255, 1, &message,3,autopilotid, paramid, paramval, type );
	//static inline uint16_t 
	//mavlink_msg_param_set_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                              // uint8_t target_system, uint8_t target_component, const char *param_id, float param_value, uint8_t param_type)
	// Send the message
	port->write_message(message);

}


int
Autopilot_Interface::
arm_disarm( bool flag )
{
	if(flag)
	{
		printf("ARM ROTORS\n");
	}
	else
	{
		printf("DISARM ROTORS\n");
	}

	// Prepare command for off-board mode
	mavlink_command_long_t com = { 0 };
	com.target_system    = system_id;
	com.target_component = autopilot_id;
	com.command          = MAV_CMD_COMPONENT_ARM_DISARM;
	com.confirmation     = true;
	com.param1           = (float) flag;
	com.param2           = 21196;

	// Encode
	mavlink_message_t message;
	mavlink_msg_command_long_encode(system_id, companion_id, &message, &com);

	// Send the message
	int len = port->write_message(message);

	// Done!
	return len;
}
int
Autopilot_Interface::
servo_pwm( int servo_number, int pwm )
{

	// Prepare command for off-board mode
	mavlink_command_long_t com = { 0 };
	com.target_system    = system_id;
	com.target_component = autopilot_id;
	com.command          = MAV_CMD_DO_SET_SERVO;
	com.confirmation     = true;
	com.param1           = servo_number;
	com.param2           = pwm;

	// Encode
	mavlink_message_t message;
	mavlink_msg_command_long_encode(system_id, companion_id, &message, &com);

	// Send the message
	int len = port->write_message(message);

	// Done!
	return len;
}
void
Autopilot_Interface::
takeoff(float alt)
{

	// Prepare command for off-board mode
	mavlink_command_long_t com = { 0 };
	com.target_system    = system_id;
	com.target_component = autopilot_id;
	com.command          = MAV_CMD_NAV_TAKEOFF;
	com.confirmation     = true;
	com.param7           = alt;
	cout<<"TakeOff Started reaching "<<alt<<" meters\n";
	// Encode
	mavlink_message_t message;
	mavlink_msg_command_long_encode(system_id, companion_id, &message, &com);

	// Send the message
	int len = port->write_message(message);

	// Done!
	return len;
}
int
Autopilot_Interface::
read_servo(int servo_number)
{
	mavlink_servo_output_raw_t servo = messages.servo;
	if(servo_number == 1)
		pwm = servo.servo1_raw;
	else if(servo_number == 2)
		pwm = servo.servo2_raw;
	else if(servo_number == 3)
		pwm = servo.servo3_raw;
	else if(servo_number == 4)
		pwm = servo.servo4_raw;
	else if(servo_number == 5)
		pwm = servo.servo5_raw;
	else if(servo_number == 6)
		pwm = servo.servo6_raw;
	else if(servo_number == 7)
		pwm = servo.servo7_raw;
	else if(servo_number == 8)
		pwm = servo.servo8_raw;
	else if(servo_number == 9)
		pwm = servo.servo9_raw;
	else if(servo_number == 10)
		pwm = servo.servo10_raw;
	else if(servo_number == 11)
		pwm = servo.servo11_raw;
	else if(servo_number == 12)
		pwm = servo.servo12_raw;
	else if(servo_number == 13)
		pwm = servo.servo13_raw;
	else if(servo_number == 14)
		pwm = servo.servo14_raw;
	else if(servo_number == 15)
		pwm = servo.servo15_raw;
	else if(servo_number == 16)
		pwm = servo.servo16_raw;
	
	cout<<"Servo "<<servo_number<< " PWM = "<<pwm<<endl;
}




