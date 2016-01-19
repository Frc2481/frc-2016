/*
 * DriveTrain.cpp
 *
 *  Created on: Jan 16, 2016
 *      Author: Team2481
 */

#include <Subsystems/DriveTrain.h>
#include <Commands/TankDriveCommand.h>
#include <RoboUtils.h>

DriveTrain::DriveTrain() : Subsystem("DriveTrain"){
	// TODO Auto-generated constructor stub
	m_topLeft = new CANTalon(FL_MOTOR);
	m_topLeft->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
	m_topRight = new CANTalon(FR_MOTOR);
	m_topRight->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
	m_botLeft = new CANTalon(BL_MOTOR);
	m_botLeft->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
	m_botRight = new CANTalon(BR_MOTOR);
	m_botRight->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
	m_serialPort = new SerialPort(57600,SerialPort::kMXP);
	m_imu = new AHRS(SerialPort::kMXP);
	m_kp = .020;
	SmartDashboard::PutNumber("Kp", m_kp);
	m_ki = .01;
	SmartDashboard::PutNumber("Ki", m_ki);
	m_kd = 0;
	SmartDashboard::PutNumber("Kd", m_kd);
	m_errorAccum = 0;
	SmartDashboard::PutNumber("I Zone", 30);
}

DriveTrain::~DriveTrain() {
	// TODO Auto-generated destructor stub
}

void DriveTrain::Tank(double rightSpeed, double leftSpeed) {
	SmartDashboard::PutNumber("Gyro Value", m_imu->GetAngle());
	SmartDashboard::PutNumber("FR Talon", m_topRight->GetOutputCurrent());
	SmartDashboard::PutNumber("FL Talon", m_topLeft->GetOutputCurrent());
	SmartDashboard::PutNumber("BR Talon", m_botRight->GetOutputCurrent());
	SmartDashboard::PutNumber("BL Talon", m_botLeft->GetOutputCurrent());

	if (leftSpeed > .2 || leftSpeed < -.2){
		m_topLeft->Set(leftSpeed);
		m_botLeft->Set(leftSpeed);
	}
	else {
		m_topLeft->Set(0);
		m_botLeft->Set(0);
	}
	if (rightSpeed > .2 || rightSpeed < -.2){
		m_topRight->Set(-(rightSpeed));
		m_botRight->Set(-(rightSpeed));
	}
	else {
		m_topRight->Set(0);
		m_botRight->Set(0);
	}
}

void DriveTrain::TankRaw(double rightSpeed, double leftSpeed) {
	SmartDashboard::PutNumber("Gyro Value", m_imu->GetAngle());
	SmartDashboard::PutNumber("FR Talon", m_topRight->GetOutputCurrent());
	SmartDashboard::PutNumber("FL Talon", m_topLeft->GetOutputCurrent());
	SmartDashboard::PutNumber("BR Talon", m_botRight->GetOutputCurrent());
	SmartDashboard::PutNumber("BL Talon", m_botLeft->GetOutputCurrent());

	m_topLeft->Set(leftSpeed);
	m_botLeft->Set(leftSpeed);

	m_topRight->Set(-(rightSpeed));
	m_botRight->Set(-(rightSpeed));
}

void DriveTrain::StopMotors(){
	m_topLeft->Set(0);
	m_topRight->Set(0);
	m_botLeft->Set(0);
	m_botRight->Set(0);
}

double DriveTrain::RotateToAngleClock(double angle) {
	double curAngle = m_imu->GetAngle();
	double error = RoboUtils::constrainDegNeg180To180(angle - curAngle);
	SmartDashboard::PutNumber("Gyro Error", error);
	m_kp = SmartDashboard::GetNumber("Kp", 0);
	m_ki = SmartDashboard::GetNumber("Ki", 0) / 100;
	m_kd = SmartDashboard::GetNumber("Kd", 0);
	double P = m_kp * error;
	SmartDashboard::PutNumber("P", P);
	SmartDashboard::GetNumber("I Zone", 0);
	if (fabs(error) > 10) {
		m_errorAccum = 0;
	}
	else if (error > 0 && m_errorAccum < 0) {
		m_errorAccum = 0;
	}
	else if (error < 0 && m_errorAccum > 0) {
		m_errorAccum = 0;
	}
	else {
		m_errorAccum += error;
	}
	double I = m_errorAccum * m_ki;
	SmartDashboard::PutNumber("I", I);
	double twist = (P + I);
	SmartDashboard::PutNumber("Twist", twist);
	TankRaw(-twist, twist);
	return fabs(error);
}

double DriveTrain::RotateToAngleCClock(double angle) {
//	double curAngle = m_imu->GetAngle();
//	double error = angle - curAngle;
//	SmartDashboard::PutNumber("Gyro Error", error);
//	m_kp = SmartDashboard::GetNumber("Kp", 0);
//	m_ki = SmartDashboard::GetNumber("Ki", 0);
//	m_kd = SmartDashboard::GetNumber("Kd", 0);
//	double P = m_kp * error;
//	SmartDashboard::PutNumber("P", P);
//	double I = (m_errorAccum + error) * m_ki;
//	SmartDashboard::PutNumber("I", I);
//	m_errorAccum += error;
//	double twist = (P + I) * .2;
//	SmartDashboard::PutNumber("Twist", twist);
//	Tank(-twist, twist);
//	return fabs(error);
}

double DriveTrain::GetAngle() {
	return m_imu->GetAngle();
}

void DriveTrain::InitDefaultCommand() {
	SetDefaultCommand(new TankDriveCommand());
}
