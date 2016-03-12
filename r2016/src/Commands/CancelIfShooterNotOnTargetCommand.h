#ifndef CancelIfShooterNotOnTargetCommand_H
#define CancelIfShooterNotOnTargetCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class CancelIfShooterNotOnTargetCommand: public CommandBase
{
public:
	CancelIfShooterNotOnTargetCommand(){}
	void Initialize(){
		if(!shooter->IsOnTarget() && Command::GetGroup()){
			Command::GetGroup()->Cancel();
		}
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
