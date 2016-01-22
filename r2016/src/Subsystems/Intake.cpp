/*
 * Intake.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: FIRSTMentor
 */

#include <Subsystems/Intake.h>
#include "RobotMap.h"

Intake::Intake() : Subsystem("Intake") {
	m_intakeMotor = new CANTalon(INTAKE_MOTOR);
	m_extender = new Solenoid(INTAKE_EXTENDER);
}

Intake::~Intake() {
	// TODO Auto-generated destructor stub
}

void Intake::Extend() {
	m_extender->Set(true);
}

void Intake::Retract() {
	m_extender->Set(false);
}

void Intake::TurnOnFwd() {
	m_intakeMotor->Set(INTAKE_FWD_SPD);
}

void Intake::TurnOnRev() {
	m_intakeMotor->Set(INTAKE_REV_SPD);
}

void Intake::TurnOff() {
	m_intakeMotor->Set(0);
}
