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
		shooter->SetShooterSpeed(false);
	}
	void Execute(){}
	bool IsFinished(){
		return false;
	}
	void End(){
		shooter->TurnOff();
	}
	void Interrupted(){
		End();
	}
};

#endif
