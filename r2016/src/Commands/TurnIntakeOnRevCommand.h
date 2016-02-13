#ifndef TurnIntakeOnRevCommand_H
#define TurnIntakeOnRevCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class TurnIntakeOnRevCommand: public CommandBase
{
public:
	TurnIntakeOnRevCommand() : CommandBase("TurnIntakeOnRevCommand"){
		Requires(intake.get());
	}
	void Initialize(){
		intake->SetSpeed(INTAKE_REV_SPD);
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
