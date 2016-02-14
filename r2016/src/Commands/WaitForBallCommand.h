#ifndef WaitForBallCommand_H
#define WaitForBallCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class WaitForBallCommand: public CommandBase
{
public:
	WaitForBallCommand() : CommandBase("WaitForBallCommand"){}
	void Initialize(){}
	void Execute(){}
	bool IsFinished(){
		return intake->GetIntakeCurrent() > 15;
	}
	void End(){}
	void Interrupted(){}
};

#endif
