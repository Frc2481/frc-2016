/*
 * DriveTrain.cpp
 *
 *  Created on: Jan 16, 2016
 *      Author: Team2481
 */

#include <Subsystems/DriveTrain.h>
#include <Commands/TankDriveCommand.h>
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
	m_imu = new AHRS(SerialPort::kMXP, AHRS::kProcessedData, 50);
	m_prevYaw = m_imu->GetYaw();
}

DriveTrain::~DriveTrain() {
	// TODO Auto-generated destructor stub
}

double DriveTrain::CalcYaw() {
	double curYaw = m_imu->GetYaw();
	double yawRate = curYaw - m_prevYaw;
	m_prevYaw = curYaw;
	return yawRate;
}

void DriveTrain::Periodic(){
	SmartDashboard::PutNumber("Yaw Rate", CalcYaw());
	SmartDashboard::PutNumber("Fused Heading", m_imu->GetFusedHeading());
	SmartDashboard::PutBoolean("Is Gyro Rotating", m_imu->IsRotating());
	SmartDashboard::PutNumber("Raw Gyro X", m_imu->GetRawGyroX());
	SmartDashboard::PutNumber("Raw Gyro Y", m_imu->GetRawGyroY());
	SmartDashboard::PutNumber("Raw Gyro Z", m_imu->GetRawGyroZ());
	SmartDashboard::PutNumber("Gyro Angle", m_imu->GetAngle());
	SmartDashboard::PutNumber("Gyro Yaw", m_imu->GetYaw());
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
	Subsystem::SetDefaultCommand(new TankDriveCommand());
}
