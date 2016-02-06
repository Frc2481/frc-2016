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
	m_leftMaster = new CANTalon(FL_MOTOR);
	m_leftMaster->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);

	m_rightMaster = new CANTalon(FR_MOTOR);
	m_rightMaster->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);

	m_leftSlave = new CANTalon(BL_MOTOR);
	m_leftSlave->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
	m_leftSlave->SetControlMode(CANTalon::kFollower);
	m_leftSlave->Set(FL_MOTOR);

	m_rightSlave = new CANTalon(BR_MOTOR);
	m_rightSlave->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
	m_rightSlave->SetControlMode(CANTalon::kFollower);
	m_rightSlave->Set(FR_MOTOR);

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
	SmartDashboard::PutNumber("FR Talon Current", m_rightMaster->GetOutputCurrent());
	SmartDashboard::PutNumber("FL Talon Current", m_leftMaster->GetOutputCurrent());
	SmartDashboard::PutNumber("BR Talon Current", m_rightSlave->GetOutputCurrent());
	SmartDashboard::PutNumber("BL Talon Current", m_leftSlave->GetOutputCurrent());
	SmartDashboard::PutNumber("FR Talon Speed", m_rightMaster->Get());
	SmartDashboard::PutNumber("FL Talon Speed", m_leftMaster->Get());
	SmartDashboard::PutNumber("BR Talon Speed", m_rightSlave->Get());
	SmartDashboard::PutNumber("BL Talon Speed", m_leftSlave->Get());
}

void DriveTrain::Tank(double rightSpeed, double leftSpeed) {
	if (leftSpeed > .2 || leftSpeed < -.2){
		m_leftMaster->Set(leftSpeed);
	}
	else {
		m_leftMaster->Set(0);
	}
	if (rightSpeed > .2 || rightSpeed < -.2){
		m_rightMaster->Set(-(rightSpeed));
	}
	else {
		m_rightMaster->Set(0);
	}
}

void DriveTrain::TankRaw(double rightSpeed, double leftSpeed) {
	m_leftMaster->Set(leftSpeed);
	m_rightMaster->Set(-(rightSpeed));
}

void DriveTrain::StopMotors(){
	m_leftMaster->Set(0);
	m_rightMaster->Set(0);
}

double DriveTrain::GetAngle() {
	return m_imu->GetAngle();
}

AHRS* DriveTrain::GetIMU(){
	return m_imu;
}

void DriveTrain::SetBrake(bool brake) {
	m_leftMaster->ConfigNeutralMode(brake ? CANTalon::kNeutralMode_Brake : CANTalon::kNeutralMode_Coast);
	m_rightMaster->ConfigNeutralMode(brake ? CANTalon::kNeutralMode_Brake : CANTalon::kNeutralMode_Coast);
	m_leftSlave->ConfigNeutralMode(brake ? CANTalon::kNeutralMode_Brake : CANTalon::kNeutralMode_Coast);
	m_rightSlave->ConfigNeutralMode(brake ? CANTalon::kNeutralMode_Brake : CANTalon::kNeutralMode_Coast);
}

void DriveTrain::InitDefaultCommand() {
	Subsystem::SetDefaultCommand(new TankDriveCommand());
}
