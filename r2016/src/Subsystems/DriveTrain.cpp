/*
 * DriveTrain.cpp
 *
 *  Created on: Jan 16, 2016
 *      Author: Team2481
 */

#include <Subsystems/DriveTrain.h>
#include <Commands/TankDriveCommand.h>
#include <Commands/FPSDriveCommand.h>
#include <RoboUtils.h>
#include <SubsystemBase.h>

DriveTrain::DriveTrain() : SubsystemBase("DriveTrain"){
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
	m_accelBase = 0;
	m_accelScale = 0;
	SmartDashboard::PutNumber("Base Acceleration", m_accelBase);
	SmartDashboard::PutNumber("Acceleration Scale", m_accelScale);
}

DriveTrain::~DriveTrain() {
	// TODO Auto-generated destructor stub
}

void DriveTrain::Periodic(){
	SmartDashboard::PutNumber("Gyro Angle", m_imu->GetAngle());
	SmartDashboard::PutNumber("Gyro Roll", m_imu->GetRoll());
	SmartDashboard::PutNumber("Gyro Pitch", m_imu->GetPitch());
	SmartDashboard::PutNumber("FR Talon Current", m_topRight->GetOutputCurrent());
	SmartDashboard::PutNumber("FL Talon Current", m_topLeft->GetOutputCurrent());
	SmartDashboard::PutNumber("BR Talon Current", m_botRight->GetOutputCurrent());
	SmartDashboard::PutNumber("BL Talon Current", m_botLeft->GetOutputCurrent());
	SmartDashboard::PutNumber("FR Talon Speed", m_topRight->Get());
	SmartDashboard::PutNumber("FL Talon Speed", m_topLeft->Get());
	SmartDashboard::PutNumber("BR Talon Speed", m_botRight->Get());
	SmartDashboard::PutNumber("BL Talon Speed", m_botLeft->Get());
}

void DriveTrain::Tank(double rightSpeed, double leftSpeed) {
	SmartDashboard::GetNumber("Base Acceleration", 0);
	SmartDashboard::GetNumber("Acceleration Scale", 0);
	m_acceleration = m_accelScale * fabs(rightSpeed - leftSpeed) + m_accelBase;
	m_topLeft->SetVoltageRampRate(m_acceleration);
	m_botLeft->SetVoltageRampRate(m_acceleration);
	m_topRight->SetVoltageRampRate(m_acceleration);
	m_botRight->SetVoltageRampRate(m_acceleration);
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

AHRS* DriveTrain::GetIMU(){
	return m_imu;
}

void DriveTrain::SetBrake(bool brake) {
	m_topLeft->ConfigNeutralMode(brake ? CANTalon::kNeutralMode_Brake : CANTalon::kNeutralMode_Coast);
	m_topRight->ConfigNeutralMode(brake ? CANTalon::kNeutralMode_Brake : CANTalon::kNeutralMode_Coast);
	m_botLeft->ConfigNeutralMode(brake ? CANTalon::kNeutralMode_Brake : CANTalon::kNeutralMode_Coast);
	m_botRight->ConfigNeutralMode(brake ? CANTalon::kNeutralMode_Brake : CANTalon::kNeutralMode_Coast);
}

void DriveTrain::InitDefaultCommand() {
	//SetDefaultCommand(new TankDriveCommand());
	SetDefaultCommand(new FPSDriveCommand());
}

void DriveTrain::FPSDrive(double driveSpeed, double turnSpeed) {
	if (fabs(driveSpeed) < .2){
		driveSpeed = 0;
	}
	if (fabs(turnSpeed) < .2){
		turnSpeed = 0;
	}
	m_topLeft->Set(driveSpeed + turnSpeed);
	m_topRight->Set(driveSpeed - turnSpeed);
	m_botLeft->Set(driveSpeed + turnSpeed);
	m_botRight->Set(driveSpeed - turnSpeed);
}
