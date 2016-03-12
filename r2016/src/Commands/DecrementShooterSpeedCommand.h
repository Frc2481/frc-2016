#ifndef DecrementShooterSpeedCommand_H
#define DecrementShooterSpeedCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DecrementShooterSpeedCommand: public CommandBase
{
public:
	DecrementShooterSpeedCommand() : CommandBase("DecrementShooterSpeedCommand"){}
	void Initialize(){
		shooter->decShooterSpeed();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
