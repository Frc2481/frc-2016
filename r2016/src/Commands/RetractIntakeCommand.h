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
		if (!kicker->IsExtended()) {
			intake->Retract();
			intake->TurnOff();
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
