#ifndef Shooter_H
#define Shooter_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Shooter: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	CANTalon* m_shooterWheelLeft;
	CANTalon* m_shooterWheelRight;
	Encoder* m_shooterEncoder;
	Servo* m_angAdjust;
	
	double m_angle;

	double m_kp;
	double m_ki;
	double m_kd;

	double m_shooterSpd;
	double m_shooterAng;
	double m_shooterDistance;
	double m_shooterHeight;

	bool m_shooterState;

public:
	Shooter();
	void InitDefaultCommand();

	void TurnOn();
	void TurnOff();

	void SetShooterSpeed(double val);
	void SetShooterAngle(double val);
	void SetGoalDistance(double val);
	void SetGoalHeight(double val);

	double GetShooterSpeed();
	double GetShooterAngle();
	double GetGoalDistance();
	double GetGoalHeight();

	bool IsOn();
};

#endif
