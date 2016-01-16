/*
 * DriveTrain.h
 *
 *  Created on: Jan 16, 2016
 *      Author: Team2481
 */

#ifndef SRC_SUBSYSTEMS_DRIVETRAIN_H_
#define SRC_SUBSYSTEMS_DRIVETRAIN_H_
#include "WPILib.h"

class DriveTrain : public Subsystem{
private:
	CANTalon* m_topLeft;
	CANTalon* m_topRight;
	CANTalon* m_botLeft;
	CANTalon* m_botRight;
	AnalogGyro* m_gyro;
	double m_kp, m_ki, m_kd;
	double m_errorAccum;
	//PIDController* m_PIDGyro;

public:
	DriveTrain();
	virtual ~DriveTrain();
	void Tank(double rightSpeed, double leftSpeed);
	void StopMotors();
	void RotateToAngle(double angle);
	void InitDefaultCommand();
};

#endif /* SRC_SUBSYSTEMS_DRIVETRAIN_H_ */
