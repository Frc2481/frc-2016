#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() :
		SubsystemBase("Shooter")
{
	m_shooterWheelLeft = new CANTalon(SHOOTER_MOTOR_LEFT);
	m_shooterWheelRight = new CANTalon(SHOOTER_MOTOR_RIGHT);
	/* TODO: change SHOOTER_ENCODER to uint32_t
	m_shooterEncoder = new Encoder(SHOOTER_ENCODER);
	*/
	m_angAdjust = new Servo(SHOOTER_ANGLE_ADJUST);
	m_kp = .020;
	SmartDashboard::PutNumber("Kp", m_kp);
	m_ki = .01;
	SmartDashboard::PutNumber("Ki", m_ki);
	m_kd = 0;
	SmartDashboard::PutNumber("Kd", m_kd);
}

void Shooter::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void Shooter::Periodic() {
	SmartDashboard::PutNumber("Left Shooter Motor", m_shooterWheelLeft->Get());
	SmartDashboard::PutNumber("Right Shooter Motor", m_shooterWheelRight->Get());
	SmartDashboard::PutNumber("Shooter Encoder", m_shooterEncoder->Get());
	SmartDashboard::PutNumber("Shooter Angle Servo", m_angAdjust->Get());

	SmartDashboard::PutNumber("Shooter Speed", m_shooterSpd);
	SmartDashboard::PutNumber("Shooter Angle", m_shooterAng);
	SmartDashboard::PutNumber("Shooter Distance", m_shooterDistance);
	SmartDashboard::PutNumber("Shooter Height", m_shooterHeight);
	SmartDashboard::PutBoolean("Shooter State", m_shooterState);
}

void Shooter::TurnOn() {
	m_shooterWheelLeft->Set(m_shooterSpd);
	m_shooterWheelRight->Set(-m_shooterSpd);
	m_shooterState = true;
}

void Shooter::TurnOff(){
	m_shooterWheelLeft->Set(0);
	m_shooterWheelRight->Set(0);
	m_shooterState = false;
}

void Shooter::SetShooterSpeed(double val) {
	m_shooterSpd = val;
}

void Shooter::SetShooterAngle(double val) {
	m_angAdjust->Set(val);
}

void Shooter::SetGoalDistance(double val) {
	m_shooterDistance = val;
}

void Shooter::SetGoalHeight(double val) {
	m_shooterHeight = val;
}

double Shooter::GetShooterSpeed() {
	return m_shooterWheelLeft->Get();
}

double Shooter::GetShooterAngle() {
	return m_angAdjust->GetAngle();
}

double Shooter::GetGoalDistance() {
	return m_shooterDistance;
}

double Shooter::GetGoalHeight() {
	return m_shooterHeight;
}

bool Shooter::IsOn() {
	return m_shooterState;
}

double Shooter::GetDesiredSpeed() {
	return m_shooterSpd;
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
