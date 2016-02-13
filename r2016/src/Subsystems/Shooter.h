#ifndef Shooter_H
#define Shooter_H

#include "WPILib.h"
#include <SubsystemBase.h>

class Shooter: public SubsystemBase
{
private:
	CANTalon* m_shooterWheel;
	Solenoid* m_shooterAdjuster;
	bool m_highPosition;
	double m_shooterDistance;

public:
	Shooter();
	void InitDefaultCommand();
	void Periodic();

	void TurnOff();
	void SetShooterSpeed(double val);
	void SetGoalDistance(double val);

	double GetShooterSpeed();
	double GetDesiredSpeed();
	double GetGoalDistance();

	bool IsOn();

	void SetHighPosition();
	void SetLowPosition();
	bool GetPosition();
};

#endif
