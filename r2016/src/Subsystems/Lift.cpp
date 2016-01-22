#include "Lift.h"
#include "../RobotMap.h"

Lift::Lift() :
		Subsystem("Lift")
{
	m_liftMotor = new CANTalon(LIFT_MOTOR);
	m_ballSensor = new DigitalInput(LIFT_LIMIT_SWITCH);
}

void Lift::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
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
// Put methods for controlling this subsystem
// here. Call these from Commands.
