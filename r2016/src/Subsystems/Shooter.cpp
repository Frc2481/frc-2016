#include "Shooter.h"
#include "../RobotMap.h"
#include "../RoboPreferences.h"

Shooter::Shooter() :
		SubsystemBase("Shooter")
{
	m_shooterWheel = new CANTalon(SHOOTER_MOTOR);
	SmartDashboard::PutBoolean("Shooter Tuning", false);
	double kp = RoboPreferences::GetInstance()->GetDouble("Shooter kP", .7);
	double ki = RoboPreferences::GetInstance()->GetDouble("Shooter kI", .00008);
	double kd = RoboPreferences::GetInstance()->GetDouble("Shooter kD", 0);
	m_shooterWheel->SetControlMode(CANTalon::kSpeed);
	m_shooterWheel->SetPID(kp, ki, kd);
	m_shooterWheel->ConfigEncoderCodesPerRev(1024);
	m_shooterWheel->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	m_shooterWheel->SetSensorDirection(true);
}

void Shooter::InitDefaultCommand()
{
}

void Shooter::Periodic() {
	bool tuning = SmartDashboard::GetBoolean("Shooter Tuning", false);
	if (tuning){
		double kp = RoboPreferences::GetInstance()->GetDouble("Shooter kP", .7);
		double ki = RoboPreferences::GetInstance()->GetDouble("Shooter kI", .00008);
		double kd = RoboPreferences::GetInstance()->GetDouble("Shooter kD", 0);

		m_shooterWheel->SetPID(kp, ki, kd);
	}

	SmartDashboard::PutNumber("Shooter Motor", m_shooterWheel->GetSpeed());
	SmartDashboard::PutNumber("Shooter Enc Vel", m_shooterWheel->GetEncVel());
	SmartDashboard::PutNumber("Shooter Error", m_shooterWheel->GetClosedLoopError());
	SmartDashboard::PutNumber("Shooter Setpoint", m_shooterWheel->GetSetpoint());
	SmartDashboard::PutNumber("Shooter Distance", m_shooterDistance);
}

void Shooter::TurnOff(){
	m_shooterWheel->Disable();
}

void Shooter::SetShooterSpeed(double val) {
	m_shooterWheel->Enable();
	m_shooterWheel->Set(val);
}

void Shooter::SetGoalDistance(double val) {
	m_shooterDistance = val;
}

double Shooter::GetShooterSpeed() {
	return m_shooterWheel->Get();
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
