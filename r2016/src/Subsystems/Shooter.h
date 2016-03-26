#ifndef Shooter_H
#define Shooter_H

#include "WPILib.h"
#include <SubsystemBase.h>
#include "../MotionProfiles/TESTMotionProfile.h"

class Shooter: public SubsystemBase
{
private:
	CANTalon* m_shooterWheel;
	Solenoid* m_shooterAdjuster;
	Notifier m_notifier;
	bool m_highPosition;
	double m_shooterDistance;
	double m_shooterSpeed;
	int m_onTargetCounter;

public:
	Shooter();
	void InitDefaultCommand();
	void Periodic();

	void TurnOff();
	void SetShooterSpeed(bool forward = true);
	void SetGoalDistance(double val);

	double GetShooterSpeed();
	double GetDesiredSpeed();
	double GetGoalDistance();
	void incShooterSpeed();
	void decShooterSpeed();

	bool IsOn();
	bool IsOnTarget();

	void SetHighPosition();
	void SetLowPosition();
	bool GetPosition();

	//TODO: move to DriveTrain once working
	void PeriodicTask();
	void ResetMotionControl();
	void StartMotionProfile();
	void StopMotionProfile();
	void StartFilling();
	void StartFilling(const double profile[][3],int totalCnt);
};

#endif
