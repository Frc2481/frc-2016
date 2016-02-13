#ifndef RetractKickerCommand_H
#define RetractKickerCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class RetractKickerCommand: public CommandBase
{
public:
	RetractKickerCommand() : CommandBase("RetractKickerCommand"){
		Requires(kicker.get());
	}
	void Initialize(){
		kicker->Retract();
	}
	void Execute(){}
	bool IsFinished(){
		return kicker->GetCurrentDraw() >= 10;
	}
	void End(){
		kicker->Stop();
	}
	void Interrupted(){}
};

#endif
