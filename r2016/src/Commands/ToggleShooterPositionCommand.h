#ifndef ToggleShooterPositionCommand_H
#define ToggleShooterPositionCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ToggleShooterPositionCommand: public CommandBase
{
public:
	ToggleShooterPositionCommand() : CommandBase("ToggleShooterPositionCommand"){
		Requires(shooter.get());
	}
	void Initialize(){
		if (shooter->GetPosition() == false) {
			shooter->SetHighPosition();
		}
		else {
			shooter->SetLowPosition();
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
