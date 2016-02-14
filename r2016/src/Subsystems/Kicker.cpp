#include "Kicker.h"
#include "../RobotMap.h"

Kicker::Kicker() : SubsystemBase("Kicker")
{
	m_kicker = new CANTalon(KICKER);
	m_isExtended = false;
}

void Kicker::InitDefaultCommand()
{
}

void Kicker::Extend() {
	m_kicker->Set(-1);
	m_isExtended = true;
}

void Kicker::Retract() {
	m_kicker->Set(1);
	m_isExtended = false;
}

void Kicker::Stop(){
	m_kicker->Set(0);
}

bool Kicker::IsExtended() {
	return m_isExtended;
}

void Kicker::Periodic() {
	SmartDashboard::PutNumber("Kicker Output Current", m_kicker->GetOutputCurrent());
	SmartDashboard::PutNumber("Kicker Speed", m_kicker->GetSpeed());
}

double Kicker::GetCurrentDraw() {
	return m_kicker->GetOutputCurrent();
}
