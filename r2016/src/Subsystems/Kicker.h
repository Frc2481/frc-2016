#ifndef Kicker_H
#define Kicker_H

#include <SubsystemBase.h>
#include "WPILib.h"

class Kicker: public SubsystemBase
{
private:
	CANTalon* m_kicker;
	bool m_isExtended;
	double m_kickerSpeed;
public:
	Kicker();
	void InitDefaultCommand();
	void Extend();
	void Retract();
	void Stop();
	bool IsExtended();
	void Periodic();
	double GetCurrentDraw();
};

#endif
