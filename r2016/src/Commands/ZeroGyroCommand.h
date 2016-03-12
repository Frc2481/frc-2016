#ifndef ZeroGyroCommand_H
#define ZeroGyroCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ZeroGyroCommand: public CommandBase
{
public:
	ZeroGyroCommand(){}
	void Initialize(){
		driveTrain->ZeroGyro();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
