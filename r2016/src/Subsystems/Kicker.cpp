#include "Kicker.h"
#include "../RobotMap.h"
#include "../CommandBase.h"

Kicker::Kicker() : SubsystemBase("Kicker")
{
	m_kicker = new CANTalon(KICKER);
	m_isExtended = false;
	m_kickerSpeed = -1;
	SmartDashboard::PutNumber("Kicker Speed", m_kickerSpeed);
}

void Kicker::InitDefaultCommand()
{
}

void Kicker::Extend() {
	m_kicker->Set(m_kickerSpeed);
	m_isExtended = true;
}

void Kicker::Retract() {
	m_kicker->Set(.2);
	m_isExtended = false;
}

void Kicker::Stop(){
	m_kicker->Set(0);
}

bool Kicker::IsExtended() {
	return m_isExtended;
}

void Kicker::Periodic() {

	m_kickerSpeed = SmartDashboard::GetNumber("Kicker Speed", -1);
	SmartDashboard::PutNumber("Kicker Output Current", m_kicker->GetOutputCurrent());
	SmartDashboard::PutNumber("Kicker Output Current", m_kicker->GetOutputCurrent());
	SmartDashboard::PutNumber("Kicker Actual Speed", m_kicker->GetSpeed());
}

double Kicker::GetCurrentDraw() {
	return m_kicker->GetOutputCurrent();
}
