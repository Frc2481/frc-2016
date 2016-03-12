#ifndef ShooterOnTargetCommand_H
#define ShooterOnTargetCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShooterOnTargetCommand: public CommandBase
{
public:
	ShooterOnTargetCommand(){}
	void Initialize(){}
	void Execute(){}
	bool IsFinished(){
		return shooter->IsOnTarget();
	}
	void End(){}
	void Interrupted(){}
};

#endif
