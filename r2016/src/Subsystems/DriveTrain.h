/*
 * DriveTrain.h
 *
 *  Created on: Jan 16, 2016
 *      Author: Team2481
 */

#ifndef SRC_SUBSYSTEMS_DRIVETRAIN_H_
#define SRC_SUBSYSTEMS_DRIVETRAIN_H_
#include "WPILib.h"
#include "../IMU/AHRS.h"
#include "RobotMap.h"

class DriveTrain : public Subsystem{
private:
	CANTalon* m_topLeft;
	CANTalon* m_topRight;
	CANTalon* m_botLeft;
	CANTalon* m_botRight;
	uint8_t m_update_rate_hz = 50;
	SerialPort* m_serialPort;
	AHRS* m_imu;
	double m_kp, m_ki, m_kd;
	double m_errorAccum;
//	enum Ports {
//		m_Port
//	};
	//PIDController* m_PIDGyro;

public:
	DriveTrain();
	virtual ~DriveTrain();
	void Tank(double rightSpeed, double leftSpeed);
	void TankRaw(double rightSpeed, double leftSpeed);
	void StopMotors();
	double RotateToAngleClock(double angle);
	double RotateToAngleCClock(double angle);
	double GetAngle();
	void InitDefaultCommand();
};

#endif /* SRC_SUBSYSTEMS_DRIVETRAIN_H_ */
