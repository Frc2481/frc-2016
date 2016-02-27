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
#include <RoboPreferences.h>

DriveTrain::DriveTrain() : SubsystemBase("DriveTrain"){
	// TODO Auto-generated constructor stub
	m_rightMaster = new CANTalon(RM_MOTOR);
	m_rightMaster->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);

	m_leftMaster = new CANTalon(LM_MOTOR);
	m_leftMaster->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);

	m_leftSlave = new CANTalon(LS_MOTOR);
	m_leftSlave->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
	m_leftSlave->SetControlMode(CANTalon::kFollower);
	m_leftSlave->Set(LM_MOTOR);

	m_rightSlave = new CANTalon(RS_MOTOR);
	m_rightSlave->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
	m_rightSlave->SetControlMode(CANTalon::kFollower);
	m_rightSlave->Set(RM_MOTOR);

	double dp = RoboPreferences::GetInstance()->GetDouble("DriveTrain_Distance_P", 0);
	double di = RoboPreferences::GetInstance()->GetDouble("DriveTrain_Distance_I", 0);
	double dd = RoboPreferences::GetInstance()->GetDouble("DriveTrain_Distance_D", 0);

	double sp = RoboPreferences::GetInstance()->GetDouble("DriveTrain_Speed_P", 0);
	double si = RoboPreferences::GetInstance()->GetDouble("DriveTrain_Speed_I", 0);
	double sd = RoboPreferences::GetInstance()->GetDouble("DriveTrain_Speed_D", 0);

	m_rightMaster->SelectProfileSlot(kDistancePID);
	m_rightMaster->SetPID(dp, di, dd);
	m_rightMaster->SelectProfileSlot(kSpeedPID);
	m_rightMaster->SetPID(sp, si, sd);
	m_rightMaster->ConfigEncoderCodesPerRev(64);
	m_rightMaster->SetFeedbackDevice(CANTalon::QuadEncoder);

	m_leftMaster->SelectProfileSlot(kDistancePID);
	m_leftMaster->SetPID(dp, di, dd);
	m_leftMaster->SelectProfileSlot(kSpeedPID);
	m_leftMaster->SetPID(sp, si, sd);
	m_leftMaster->ConfigEncoderCodesPerRev(64);
	m_leftMaster->SetFeedbackDevice(CANTalon::QuadEncoder);

	m_shifter = new Solenoid(DRIVETRAIN_SHIFTER);

	m_serialPort = new SerialPort(57600,SerialPort::kMXP);
	m_imu = new AHRS(SerialPort::kMXP, AHRS::kProcessedData, 50);
	m_prevYaw = m_imu->GetYaw();

	m_gyroOffset = 0;
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

void DriveTrain::SetSetpoint(double setpoint) {
	m_leftMaster->SetEncPosition(0);
	m_rightMaster->SetEncPosition(0);
	m_rightMaster->SetSetpoint(setpoint);
	m_leftMaster->SetSetpoint(setpoint);
}

void DriveTrain::SetToVoltageMode() {
	m_rightMaster->SetControlMode(CANTalon::kPercentVbus);
	m_leftMaster->SetControlMode(CANTalon::kPercentVbus);
}

void DriveTrain::SetToDistanceMode() {
	double dp = RoboPreferences::GetInstance()->GetDouble("DriveTrain_Distance_P", 0);
	double di = RoboPreferences::GetInstance()->GetDouble("DriveTrain_Distance_I", 0);
	double dd = RoboPreferences::GetInstance()->GetDouble("DriveTrain_Distance_D", 0);

	//m_leftMaster->SetControlMode(CANTalon::kPosition);
	m_leftMaster->SetControlMode(CANTalon::kPosition);
	m_rightMaster->SetControlMode(CANTalon::kPosition);

	//m_leftMaster->SelectProfileSlot(kDistancePID);
	//m_leftMaster->SetPID(dp, di, dd);

	m_leftMaster->SelectProfileSlot(kDistancePID);
	m_leftMaster->SetPID(dp, di, dd);
	m_rightMaster->SelectProfileSlot(kDistancePID);
	m_rightMaster->SetPID(dp, di, dd);

}

void DriveTrain::SetToSpeedMode() {
	double sp = RoboPreferences::GetInstance()->GetDouble("DriveTrain_Speed_P", 0);
	double si = RoboPreferences::GetInstance()->GetDouble("DriveTrain_Speed_I", 0);
	double sd = RoboPreferences::GetInstance()->GetDouble("DriveTrain_Speed_D", 0);

	m_rightMaster->SetControlMode(CANTalon::kSpeed);
	m_leftMaster->SetControlMode(CANTalon::kSpeed);

	m_rightMaster->SelectProfileSlot(kSpeedPID);
	m_rightMaster->SetPID(sp, si, sd);

	m_leftMaster->SelectProfileSlot(kSpeedPID);
	m_leftMaster->SetPID(sp, si, sd);
}

void DriveTrain::ZeroEncoders(){
	m_leftMaster->SetEncPosition(0);
	m_rightMaster->SetEncPosition(0);
}

bool DriveTrain::IsAtSetpoint() {
	return /*fabs(m_leftMaster->GetClosedLoopError()) < .5 &&*/ fabs(m_leftMaster->GetClosedLoopError()) < .5;
}

void DriveTrain::FPSDrive(double spd, double rotate) {
	if (spd > .2 || rotate > .2) {
		m_rightMaster->Set(spd - rotate);
		m_leftMaster->Set(spd + rotate);
	}
	else {
		m_rightMaster->Set(0);
		m_leftMaster->Set(0);
	}
}

double DriveTrain::GetEncoderPos() {
	return m_rightMaster->GetEncPosition();
//	if(m_leftMaster->GetEncPosition() != m_prevEncPositionLeft){
//		return m_leftMaster->GetEncPosition();
//	}
//	else if (m_rightMaster->GetEncPosition() != m_prevEncPositionRight){
//		return m_rightMaster->GetEncPosition();
//	}
//	else {
//		return m_leftMaster->GetEncPosition();
//	}
}

double DriveTrain::GetRoll() {
	return m_imu->GetRoll();
}

void DriveTrain::ZeroGyro() {
	m_gyroOffset = m_imu->GetAngle();
}

double DriveTrain::GetPitch() {
	return m_imu->GetPitch();
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
	SmartDashboard::PutNumber("RM Talon Current", m_rightMaster->GetOutputCurrent());
	SmartDashboard::PutNumber("LM Talon Current", m_leftMaster->GetOutputCurrent());
	CommandBase::logTable->PutNumber("FR Talon Current", m_leftMaster->GetOutputCurrent());
	CommandBase::logTable->PutNumber("FL Talon Current", m_rightMaster->GetOutputCurrent());
	CommandBase::logTable->PutNumber("BR Talon Current", m_rightSlave->GetOutputCurrent());
	CommandBase::logTable->PutNumber("BL Talon Current", m_leftSlave->GetOutputCurrent());
	CommandBase::logTable->PutNumber("FR Talon Speed", m_leftMaster->Get());
	CommandBase::logTable->PutNumber("FL Talon Speed", m_rightMaster->Get());
	CommandBase::logTable->PutNumber("BR Talon Speed", m_rightSlave->Get());
	CommandBase::logTable->PutNumber("BL Talon Speed", m_leftSlave->Get());

	CommandBase::logTable->PutNumber("Right Master Enc Vel", m_rightMaster->GetEncVel());
	SmartDashboard::PutNumber("Right Master Enc Pos", m_rightMaster->GetEncPosition());
	CommandBase::logTable->PutNumber("Right Master Speed", m_rightMaster->GetSpeed());

	CommandBase::logTable->PutNumber("Left Master Enc Vel", m_leftMaster->GetEncVel());
	SmartDashboard::PutNumber("Left Master Enc Pos", m_leftMaster->GetEncPosition());
	CommandBase::logTable->PutNumber("Left Master Speed", m_leftMaster->GetSpeed());

	m_prevEncPositionLeft = m_leftMaster->GetEncPosition();
	m_prevEncPositionRight = m_rightMaster->GetEncPosition();
}

void DriveTrain::Tank(double rightSpeed, double leftSpeed) {
//	if (leftSpeed > .2 || leftSpeed < -.2){
		m_rightMaster->Set(leftSpeed);
//	}
//	else {
//		m_leftMaster->Set(0);
//	}
//	if (rightSpeed > .2 || rightSpeed < -.2){
		m_leftMaster->Set(-(rightSpeed));
//	}
//	else {
//		m_rightMaster->Set(0);
//	}
}

void DriveTrain::TankRaw(double rightSpeed, double leftSpeed) {
	m_rightMaster->Set(leftSpeed);
	m_leftMaster->Set(-(rightSpeed));
}

void DriveTrain::StopMotors(){
	m_rightMaster->Set(0);
	m_leftMaster->Set(0);
}

double DriveTrain::GetAngle() {
	return m_imu->GetAngle() - m_gyroOffset;
}

AHRS* DriveTrain::GetIMU(){
	return m_imu;
}

void DriveTrain::SetBrake(bool brake) {
	m_rightMaster->ConfigNeutralMode(brake ? CANTalon::kNeutralMode_Brake : CANTalon::kNeutralMode_Coast);
	m_leftMaster->ConfigNeutralMode(brake ? CANTalon::kNeutralMode_Brake : CANTalon::kNeutralMode_Coast);
	m_leftSlave->ConfigNeutralMode(brake ? CANTalon::kNeutralMode_Brake : CANTalon::kNeutralMode_Coast);
	m_rightSlave->ConfigNeutralMode(brake ? CANTalon::kNeutralMode_Brake : CANTalon::kNeutralMode_Coast);
}

void DriveTrain::InitDefaultCommand() {
	Subsystem::SetDefaultCommand(new TankDriveCommand());
}

void DriveTrain::SetShifter(bool state) {
	m_shifter->Set(state);
}
