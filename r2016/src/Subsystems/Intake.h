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
	int m_stalledCounter;
	double m_intakeSpeed;
public:
	Intake();
	virtual ~Intake();
	void Lower();
	void Raise();
	void SetSpeed(double spd);
	void TurnOff();
	double GetIntakeCurrent();
	double GetIntakeSpeed();
	bool IsLowered();
	void Periodic();
};

#endif /* SRC_SUBSYSTEMS_INTAKE_H_ */
