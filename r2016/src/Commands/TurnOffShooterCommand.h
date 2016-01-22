#ifndef TurnOffShooterCommand_H
#define TurnOffShooterCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class TurnOffShooterCommand: public CommandBase
{
public:
	TurnOffShooterCommand() : CommandBase("TurnOffShooterCommand"){
		Requires(shooter.get());
	}
	void Initialize(){
		shooter->TurnOff();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
