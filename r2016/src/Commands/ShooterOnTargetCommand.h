#ifndef ShooterOnTargetCommand_H
#define ShooterOnTargetCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShooterOnTargetCommand: public CommandBase
{
private:
public:
	ShooterOnTargetCommand(){}
	void Initialize(){
		SetTimeout(2);
	}
	void Execute(){}
	bool IsFinished(){
		return shooter->IsOnTarget() || IsTimedOut();
	}
	void End(){}
	void Interrupted(){}
};

#endif
