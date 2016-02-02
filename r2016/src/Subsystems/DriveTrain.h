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

class DriveTrain : public SubsystemBase{
private:
	CANTalon* m_topLeft;
	CANTalon* m_topRight;
	CANTalon* m_botLeft;
	CANTalon* m_botRight;
	uint8_t m_update_rate_hz = 50;
	SerialPort* m_serialPort;
	AHRS* m_imu;
	double m_prevYaw;

public:
	DriveTrain();
	virtual ~DriveTrain();
	AHRS* GetIMU();
	void Tank(double rightSpeed, double leftSpeed);
	void TankRaw(double rightSpeed, double leftSpeed);
	void StopMotors();
	void SetBrake(bool brake);
	double GetAngle();
	double CalcYaw();
	void InitDefaultCommand();
	void Periodic();
};

#endif /* SRC_SUBSYSTEMS_DRIVETRAIN_H_ */
