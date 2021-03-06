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
	const int kDistancePID = 0;
	const int kSpeedPID = 1;
	CANTalon* m_rightMaster;
	CANTalon* m_leftMaster;
	CANTalon* m_rightSlave;
	CANTalon* m_leftSlave;
	Solenoid* m_shifter;
	uint8_t m_update_rate_hz = 50;
	SerialPort* m_serialPort;
	AHRS* m_imu;
	double m_prevYaw;
	double m_setPoint;
	double m_gyroOffset;
	double m_prevEncPositionLeft;
	double m_prevEncPositionRight;
public:
	DriveTrain();
	virtual ~DriveTrain();
	AHRS* GetIMU();
	void Tank(double rightSpeed, double leftSpeed);
	void TankRaw(double rightSpeed, double leftSpeed);
	void StopMotors();
	void SetBrake(bool brake);
	void SetShifter(bool state);
	void SetSetpoint(double setpoint);
	void SetToVoltageMode();
	void SetToDistanceMode();
	void SetToSpeedMode();
	void ZeroEncoders();
	double GetEncoderPos();
	double GetAngle();
	double GetRoll();
	double CalcYaw();
	double GetPitch();
	bool IsAtSetpoint();
	void ZeroGyro();
	void InitDefaultCommand();
	void FPSDrive(double spd, double rotate);
	double GetOutputCurrent();
	void Periodic();
};

#endif /* SRC_SUBSYSTEMS_DRIVETRAIN_H_ */
