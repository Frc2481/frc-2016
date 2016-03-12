#ifndef ShooterUpCommand_H
#define ShooterUpCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShooterUpCommand: public CommandBase
{
public:
	ShooterUpCommand() : CommandBase("ShooterUpCommand"){}
	void Initialize(){
		shooter->SetHighPosition();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
