/*
 * DriveTrain.cpp
 *
 *  Created on: Jan 16, 2016
 *      Author: Team2481
 */

#include <Subsystems/DriveTrain.h>
#include <Commands/TankDriveCommand.h>

DriveTrain::DriveTrain() : Subsystem("DriveTrain"){
	// TODO Auto-generated constructor stub
	m_topLeft = new CANTalon(0);
	m_topRight = new CANTalon(1);
	m_botLeft = new CANTalon(2);
	m_botRight = new CANTalon(3);
	m_gyro = new AnalogGyro(0);
	m_kp = 0;
	SmartDashboard::PutNumber("Kp", m_kp);
	m_ki = 0;
	SmartDashboard::PutNumber("Ki", m_ki);
	m_kd = 0;
	SmartDashboard::PutNumber("Kd", m_kd);
	m_errorAccum = 0;
}

DriveTrain::~DriveTrain() {
	// TODO Auto-generated destructor stub
}

void DriveTrain::Tank(double rightSpeed, double leftSpeed) {
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

void DriveTrain::StopMotors(){
	m_topLeft->Set(0);
	m_topRight->Set(0);
	m_botLeft->Set(0);
	m_botRight->Set(0);
}

void DriveTrain::RotateToAngle(double angle) {
	double curAngle = m_gyro->GetAngle();
	double error = angle - curAngle;
	m_kp = SmartDashboard::GetNumber("Kp", 0);
	m_ki = SmartDashboard::GetNumber("Ki", 0);
	m_kd = SmartDashboard::GetNumber("Kd", 0);
	double P = m_kp * error;
	double I = m_errorAccum + error;
}

void DriveTrain::InitDefaultCommand() {
	SetDefaultCommand(new TankDriveCommand());
}
