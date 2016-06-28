#ifndef IncShooterSpeedCommand_H
#define IncShooterSpeedCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class IncShooterSpeedCommand: public CommandBase
{
public:
	IncShooterSpeedCommand() : CommandBase("IncShooterSpeedCommand"){
		SetRunWhenDisabled(true);
	}
	void Initialize(){
		shooter->incShooterSpeed();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
