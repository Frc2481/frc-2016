#include "Kicker.h"
#include "../RobotMap.h"

Kicker::Kicker() : SubsystemBase("Kicker")
{
	m_kicker = new Solenoid(KICKER);
}

void Kicker::InitDefaultCommand()
{
}

void Kicker::Extend() {
	m_kicker->Set(true);
}

void Kicker::Retract() {
	m_kicker->Set(false);
}

bool Kicker::IsExtended() {
	return m_kicker->Get();
}

void Kicker::Periodic() {}
