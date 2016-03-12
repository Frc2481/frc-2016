#ifndef TurnOnShooterCommand_H
#define TurnOnShooterCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class TurnOnShooterCommand: public CommandBase
{
public:
	TurnOnShooterCommand() : CommandBase("TurnOnShooterCommand"){
		Requires(shooter.get());
	}
	void Initialize(){
		shooter->SetShooterSpeed();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
