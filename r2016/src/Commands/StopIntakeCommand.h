#ifndef StopIntakeCommand_H
#define StopIntakeCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class StopIntakeCommand: public CommandBase
{
public:
	StopIntakeCommand() : CommandBase("StopIntakeCommand"){
		Requires(intake.get());
	}
	void Initialize(){
		intake->SetSpeed(0);
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
