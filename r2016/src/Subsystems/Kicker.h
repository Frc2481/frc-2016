#ifndef Kicker_H
#define Kicker_H

#include <SubsystemBase.h>
#include "WPILib.h"

class Kicker: public SubsystemBase
{
private:
	Solenoid* m_kicker;
public:
	Kicker();
	void InitDefaultCommand();
	void Extend();
	void Retract();
	bool IsExtended();
	void Periodic();
};

#endif
