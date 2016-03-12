/*
 * Intake.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: FIRSTMentor
 */

#include <Subsystems/Intake.h>
#include "RobotMap.h"
#include <SubsystemBase.h>
#include "CommandBase.h"

Intake::Intake() : SubsystemBase("Intake") {
	m_intakeMotor = new CANTalon(INTAKE_MOTOR);
	m_extender = new Solenoid(INTAKE_EXTENDER);
	m_stalledCounter = 0;
}

Intake::~Intake() {
	// TODO Auto-generated destructor stub
}

bool Intake::IsLowered() {
	return m_extender->Get();
}

double Intake::GetIntakeCurrent() {
	return m_intakeMotor->GetOutputCurrent();
}

void Intake::Periodic(){
	SmartDashboard::PutNumber("Intake Motor", m_intakeMotor->Get());
	SmartDashboard::PutNumber("Intake Output Current", m_intakeMotor->GetOutputCurrent());
	SmartDashboard::PutNumber("Intake Extender", m_extender->Get());
	if (m_intakeMotor->GetOutputCurrent() > 10) {
		m_stalledCounter++;
		if (m_stalledCounter > 100) {
			TurnOff();
			m_stalledCounter = 0;
		}
	}
	else {
		m_stalledCounter = 0;
	}

}
void Intake::Lower() {
	m_extender->Set(true);
}

void Intake::Raise() {
	m_extender->Set(false);
}

void Intake::SetSpeed(double spd) {
	m_intakeMotor->Set(spd);
}

void Intake::TurnOff() {
	m_intakeMotor->Set(0);
}
