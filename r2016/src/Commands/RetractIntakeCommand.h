#ifndef RetractIntakeCommand_H
#define RetractIntakeCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class RetractIntakeCommand: public CommandBase
{
public:
	RetractIntakeCommand() : CommandBase("RetractIntakeCommand"){
		Requires(intake.get());
	}
	void Initialize(){
		intake->TurnOff();
		intake->Retract();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
