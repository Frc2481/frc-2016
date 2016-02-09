/*
 * Intake.h
 *
 *  Created on: Jan 18, 2016
 *      Author: FIRSTMentor
 */

#ifndef SRC_SUBSYSTEMS_INTAKE_H_
#define SRC_SUBSYSTEMS_INTAKE_H_

#include "WPILib.h"
#include <SubsystemBase.h>

class Intake : public SubsystemBase{
private:
	CANTalon* m_intakeMotor;
	Solenoid* m_extender;
public:
	Intake();
	virtual ~Intake();
	void Extend();
	void Retract();
	void TurnOnFwd();
	void TurnOnRev();
	void TurnOff();
	bool IsExtended();
	void Periodic();
};

#endif /* SRC_SUBSYSTEMS_INTAKE_H_ */
