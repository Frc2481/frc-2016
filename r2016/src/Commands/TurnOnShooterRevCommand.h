#ifndef TurnOnShooterRevCommand_H
#define TurnOnShooterRevCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class TurnOnShooterRevCommand: public CommandBase
{
public:
	TurnOnShooterRevCommand() : CommandBase("TurnOnShooterRevCommand"){
		Requires(shooter.get());
	}
	void Initialize(){
		shooter->SetShooterSpeed(-3000);
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
