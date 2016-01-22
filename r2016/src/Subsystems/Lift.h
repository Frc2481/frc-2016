#ifndef Lift_H
#define Lift_H

#include "WPILib.h"

class Lift: public Subsystem
{
private:
	CANTalon* m_liftMotor;
	DigitalInput* m_ballSensor;

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Lift();
	void InitDefaultCommand();
	void SetLiftSpeed(double spd);

	double GetLiftSpeed();

	bool HasBall();
};

#endif
