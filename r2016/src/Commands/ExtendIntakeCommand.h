#ifndef ExtendIntakeCommand_H
#define ExtendIntakeCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ExtendIntakeCommand: public CommandBase
{
public:
	ExtendIntakeCommand() : CommandBase("ExtendIntakeCommand"){
		Requires(intake.get());
	}
	void Initialize(){
		intake->Extend();
		intake->TurnOnFwd();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){
	}
	void Interrupted(){}
};

#endif
