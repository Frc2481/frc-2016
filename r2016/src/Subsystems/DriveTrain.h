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
#include <SubsystemBase.h>

class DriveTrain : public Subsystem{
private:
	CANTalon* m_topLeft;
	CANTalon* m_topRight;
	CANTalon* m_botLeft;
	CANTalon* m_botRight;
	SerialPort* m_serialPort;
	AHRS* m_imu;
	double m_kp, m_ki, m_kd;
	double m_errorAccum;
	double m_acceleration;
	double m_accelBase;
	double m_accelScale;
//	enum Ports {
//		m_Port
//	};
	//PIDController* m_PIDGyro;

public:
	DriveTrain();
	virtual ~DriveTrain();
	AHRS* GetIMU();
	void Tank(double rightSpeed, double leftSpeed);
	void TankRaw(double rightSpeed, double leftSpeed);
	void FPSDrive(double driveSpeed, double turnSpeed);
	void StopMotors();
	void SetBrake(bool brake);
	double RotateToAngleClock(double angle);
	double RotateToAngleCClock(double angle);
	double GetAngle();
	void InitDefaultCommand();
	void Periodic();
};

#endif /* SRC_SUBSYSTEMS_DRIVETRAIN_H_ */
