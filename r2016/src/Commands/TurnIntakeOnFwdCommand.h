#ifndef TurnIntakeOnFwdCommand_H
#define TurnIntakeOnFwdCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class TurnIntakeOnFwdCommand: public CommandBase
{
public:
	TurnIntakeOnFwdCommand() : CommandBase("TurnIntakeOnFwdCommand"){
		Requires(intake.get());
	}
	void Initialize(){
		intake->SetSpeed(INTAKE_FWD_SPD);
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
