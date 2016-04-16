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

DriveTrain::DriveTrain() : SubsystemBase("DriveTrain"), m_notifier(&DriveTrain::PeriodicTask, this)
{
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
	m_rightMaster->SetF(3.0838);
	m_rightMaster->SelectProfileSlot(kSpeedPID);
	m_rightMaster->SetPID(sp, si, sd);
	m_rightMaster->ConfigEncoderCodesPerRev(128);
	m_rightMaster->SetFeedbackDevice(CANTalon::QuadEncoder);
	m_rightMaster->ChangeMotionControlFramePeriod(5);

	m_leftMaster->SelectProfileSlot(kDistancePID);
	m_leftMaster->SetPID(dp, di, dd);
	m_leftMaster->SetF(3.0838);
	m_leftMaster->SelectProfileSlot(kSpeedPID);
	m_leftMaster->SetPID(sp, si, sd);
	m_leftMaster->ConfigEncoderCodesPerRev(128);
	m_leftMaster->SetFeedbackDevice(CANTalon::QuadEncoder);

	m_shifter = new Solenoid(DRIVETRAIN_SHIFTER);

	m_serialPort = new SerialPort(57600,SerialPort::kMXP);
	m_imu = new AHRS(SerialPort::kMXP, AHRS::kProcessedData, 50);
	m_prevYaw = m_imu->GetYaw();

	m_gyroOffset = 0;

	SmartDashboard::PutBoolean("DriveTrain Tuning", false);

	m_rightMaster->Enable();
	m_leftMaster->Enable();

	m_rotateGenerator = new RotateProfileGenerator();

	m_notifier.StartPeriodic(0.0025);
	m_loopTimeoutMP = -1;
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

	//TODO: switch to RightMaster for Competition Robot
	return m_leftMaster->GetEncPosition();
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
	if (SmartDashboard::GetBoolean("DriveTrain Tuning", false)){
		SmartDashboard::PutNumber("Yaw Rate", CalcYaw());
		SmartDashboard::PutNumber("Fused Heading", m_imu->GetFusedHeading());
		SmartDashboard::PutBoolean("Is Gyro Rotating", m_imu->IsRotating());
		SmartDashboard::PutNumber("Gyro Angle", m_imu->GetAngle());
		SmartDashboard::PutNumber("Gyro Yaw", m_imu->GetYaw());
		SmartDashboard::PutNumber("Gyro Roll", m_imu->GetRoll());
		SmartDashboard::PutNumber("Gyro Pitch", m_imu->GetPitch());
		SmartDashboard::PutNumber("RM Talon Current", m_rightMaster->GetOutputCurrent());
		SmartDashboard::PutNumber("LM Talon Current", m_leftMaster->GetOutputCurrent());

		CommandBase::logTable->PutNumber("FR Talon Speed", m_leftMaster->Get());
		CommandBase::logTable->PutNumber("FL Talon Speed", m_rightMaster->Get());
		CommandBase::logTable->PutNumber("BR Talon Speed", m_rightSlave->Get());
		CommandBase::logTable->PutNumber("BL Talon Speed", m_leftSlave->Get());

		CommandBase::logTable->PutNumber("Right Master Enc Vel", m_rightMaster->GetEncVel());
		CommandBase::logTable->PutNumber("Right Master Speed", m_rightMaster->GetSpeed());

		CommandBase::logTable->PutNumber("Left Master Enc Vel", m_leftMaster->GetEncVel());
		CommandBase::logTable->PutNumber("Left Master Speed", m_leftMaster->GetSpeed());

		SmartDashboard::PutNumber("BR Talon Speed", m_rightSlave->Get());
		SmartDashboard::PutNumber("BL Talon Speed", m_leftSlave->Get());

		SmartDashboard::PutNumber("FR Talon Speed", m_leftMaster->Get());
		SmartDashboard::PutNumber("FL Talon Speed", m_rightMaster->Get());
	}
	SmartDashboard::PutBoolean("DriveTrain Level", fabs(m_imu->GetPitch()) < 2 && fabs(m_imu->GetRoll()) < 2);

	SmartDashboard::PutNumber("FR Talon Current", m_leftMaster->GetOutputCurrent());
	SmartDashboard::PutNumber("FL Talon Current", m_rightMaster->GetOutputCurrent());
	SmartDashboard::PutNumber("BR Talon Current", m_rightSlave->GetOutputCurrent());
	SmartDashboard::PutNumber("BL Talon Current", m_leftSlave->GetOutputCurrent());

	SmartDashboard::PutNumber("Right Master Enc Pos", m_rightMaster->GetEncPosition());

	SmartDashboard::PutNumber("Left Master Enc Pos", m_leftMaster->GetEncPosition());

	SmartDashboard::PutBoolean("IMU is Moving", m_imu->IsMoving());

	m_prevEncPositionLeft = m_leftMaster->GetEncPosition();
	m_prevEncPositionRight = m_rightMaster->GetEncPosition();

	PeriodicMotionProfile();
}

void DriveTrain::Tank(double rightSpeed, double leftSpeed) {
//	if (leftSpeed > .2 || leftSpeed < -.2){
		m_rightMaster->Set(rightSpeed);
//	}
//	else {
//		m_leftMaster->Set(0);
//	}
//	if (rightSpeed > .2 || rightSpeed < -.2){
		m_leftMaster->Set(-leftSpeed);
//	}
//	else {
//		m_rightMaster->Set(0);
//	}
}

void DriveTrain::TankRaw(double rightSpeed, double leftSpeed) {
	m_rightMaster->Set(rightSpeed);
	m_leftMaster->Set(-(leftSpeed));
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

double DriveTrain::GetOutputCurrent() {
	double avgCurrent = fabs(m_rightMaster->GetOutputCurrent()) + fabs(m_leftMaster->GetOutputCurrent());
	avgCurrent /= 2;
	return avgCurrent;
}

void DriveTrain::PeriodicTask(){
	m_rightMaster->ProcessMotionProfileBuffer();
}

void DriveTrain::ResetMotionControl() {
	m_rightMaster->ClearMotionProfileTrajectories();
}

void DriveTrain::StartFilling(){
	StartFilling(m_rotateGenerator->GetRightProfile(),m_rotateGenerator->GetProfileLength());
}

void DriveTrain::StartMotionProfile() {
	m_rightMaster->Enable();
	m_rightMaster->SetControlMode(CANTalon::kMotionProfile);
	m_startMP = true;
}

void DriveTrain::StopMotionProfile() {
	m_rightMaster->Set(CANTalon::SetValueMotionProfileDisable);
//	m_shooterWheel->SetControlMode(CANTalon::kSpeed);
}

void DriveTrain::PeriodicMotionProfile(){
	m_rightMaster->GetMotionProfileStatus(m_motionProfileStatus);

	if(m_loopTimeoutMP >= 0){
		if(m_loopTimeoutMP == 0){
			instrumentation::OnNoProgress();
			//TODO: we might want to do somthing here so we can react to the talon not being there
		} else {
			m_loopTimeoutMP--;
		}
	}

	if(m_rightMaster->GetControlMode() != CANSpeedController::kMotionProfile){
		m_stateMP = 0;
	} else {
		switch (m_stateMP){
	case 0:
			if (m_startMP){
				m_startMP = false;

//				m_setValueMP = CANTalon::SetValueMotionProfileDisable;
				m_rightMaster->Set(CANTalon::SetValueMotionProfileDisable);
				StartFilling();

				m_stateMP = 1;
				m_loopTimeoutMP = kNumLoopsTimeoutMP;
			}
			break;
		case 1:
			if(m_motionProfileStatus.btmBufferCnt > kMinPointsInTalonMP){
//				m_setValueMP = CANTalon::SetValueMotionProfileEnable;
				m_rightMaster->Set(CANTalon::SetValueMotionProfileEnable);
				m_stateMP = 2;
				m_loopTimeoutMP = kNumLoopsTimeoutMP;
			}
			break;
		case 2:
			if(m_motionProfileStatus.isUnderrun == false){
				m_loopTimeoutMP = kNumLoopsTimeoutMP;
			}

			if(m_motionProfileStatus.activePointValid && m_motionProfileStatus.activePoint.isLastPoint){
//				m_setValueMP = CANTalon::SetValueMotionProfileHold;
				m_rightMaster->Set(CANTalon::SetValueMotionProfileHold);
				m_stateMP = 0;
				m_loopTimeoutMP = -1;
			}
			break;
		}
	}
//	m_shooterWheel->Set(m_setValueMP);
	instrumentation::Process(m_motionProfileStatus);
}

bool DriveTrain::IsMPFinished(){
	return m_motionProfileStatus.activePointValid && m_motionProfileStatus.activePoint.isLastPoint;
}

void DriveTrain::StartFilling(double **profile,int totalCnt){
	CANTalon::TrajectoryPoint point;
	//TODO: Handle Underrun

	m_rightMaster->ClearMotionProfileTrajectories();

	for (int i=0; i < totalCnt; i++){
		point.position = profile[i][0];
		point.velocity = profile[i][1];
		point.timeDurMs = profile[i][2];

		point.profileSlotSelect = 0;
		point.velocityOnly = false;

		point.zeroPos = false;
		if(i == 0){
			point.zeroPos = true;
		}

		point.isLastPoint = false;
		if (i + 1 == totalCnt){
			point.isLastPoint = true;
		}

		m_rightMaster->PushMotionProfileTrajectory(point);
	}
}

RotateProfileGenerator* DriveTrain::GetProfileGenerator() {
	return m_rotateGenerator;
}
