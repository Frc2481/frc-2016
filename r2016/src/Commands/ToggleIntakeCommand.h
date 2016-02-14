#ifndef ToggleIntakeCommand_H
#define ToggleIntakeCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ToggleIntakeCommand: public CommandBase
{

public:
	ToggleIntakeCommand() : CommandBase("ToggleIntakeCommand"){
		Requires(intake.get());
	}
	void Initialize(){
		if(intake->IsLowered()){
			intake->Raise();
		}else{
			intake->Lower();
		}
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){
		End();
	}
};

#endif
