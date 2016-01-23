#include "Lift.h"
#include "../RobotMap.h"

Lift::Lift() :
		SubsystemBase("Lift")
{
	m_liftMotor = new CANTalon(LIFT_MOTOR);
	m_ballSensor = new DigitalInput(LIFT_LIMIT_SWITCH);
}

void Lift::InitDefaultCommand(){
}

void Lift::SetLiftSpeed(double spd) {
	m_liftMotor->Set(spd);
}

double Lift::GetLiftSpeed() {
	return m_liftMotor->Get();
}

bool Lift::HasBall() {
	return m_ballSensor->Get();
}

void Lift::Periodic() {
	SmartDashboard::PutNumber("Lift Speed", m_liftMotor->Get());
	SmartDashboard::PutBoolean("Lift Ball Sensor", m_ballSensor->Get());
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
