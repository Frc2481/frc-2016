#include "Shooter.h"
#include "../RobotMap.h"
#include "../RoboPreferences.h"

Shooter::Shooter() :
		SubsystemBase("Shooter")
{
	m_shooterDistance = 0;
	m_shooterSpeed = 3300;
	m_onTargetCounter = 0;
	m_highPosition = true;
	m_shooterWheel = new CANTalon(SHOOTER_MOTOR);
	m_shooterWheel->SetClosedLoopOutputDirection(true);
	m_shooterAdjuster = new Solenoid(SHOOTER_ANGLE_ADJUST);
	SmartDashboard::PutBoolean("Shooter Tuning", false);
	m_shooterWheel->SelectProfileSlot(0);
	m_shooterWheel->SetControlMode(CANTalon::kSpeed);
	m_shooterWheel->SetPID(.5, 0.0, 0.0, .033);
	m_shooterWheel->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	m_shooterWheel->SetSensorDirection(true);
}

void Shooter::InitDefaultCommand()
{
}

void Shooter::Periodic() {
	SmartDashboard::PutNumber("Shooter Motor", m_shooterWheel->GetSpeed());
	SmartDashboard::PutNumber("Shooter Enc Vel", m_shooterWheel->GetEncVel());
	SmartDashboard::PutNumber("Shooter Error", m_shooterWheel->GetClosedLoopError());
	SmartDashboard::PutNumber("Shooter Setpoint", m_shooterSpeed);
	SmartDashboard::PutBoolean("Shooter High Position", m_highPosition);
	SmartDashboard::PutBoolean("Shooter on Target", IsOnTarget());
	SmartDashboard::PutNumber("Shooter Current", m_shooterWheel->GetOutputCurrent());
}

void Shooter::TurnOff(){
	m_shooterWheel->Disable();
}

void Shooter::SetShooterSpeed(bool forward) {
	if (forward){
		m_shooterWheel->Enable();
		m_shooterWheel->Set(m_shooterSpeed);
	}
	else {
		m_shooterWheel->Enable();
		m_shooterWheel->Set(-m_shooterSpeed);
	}
}

void Shooter::SetGoalDistance(double val) {
	m_shooterDistance = val;
}

double Shooter::GetShooterSpeed() {
	return m_shooterSpeed;
}

double Shooter::GetGoalDistance() {
	return m_shooterDistance;
}

bool Shooter::IsOn() {
	return m_shooterWheel->IsEnabled();
}

double Shooter::GetDesiredSpeed() {
	return m_shooterWheel->GetSetpoint();
}

void Shooter::SetHighPosition() {
	m_shooterAdjuster->Set(false);
	m_highPosition = true;
}

void Shooter::SetLowPosition() {
	m_shooterAdjuster->Set(true);
	m_highPosition = false;
}

bool Shooter::IsOnTarget() {
	if (m_shooterWheel->GetSpeed() > 1000 && fabs(m_shooterWheel->GetSpeed() - m_shooterWheel->GetSetpoint()) < 20) {
		m_onTargetCounter++;
	}
	else {
		m_onTargetCounter = 0;
	}

	return m_onTargetCounter > 5;
}

bool Shooter::GetPosition() {
	return m_highPosition;
}

void Shooter::incShooterSpeed() {
	m_shooterSpeed += 100;
}

void Shooter::decShooterSpeed() {
	m_shooterSpeed -= 100;
}

