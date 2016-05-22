#ifndef RetractKickerCommand_H
#define RetractKickerCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class RetractKickerCommand: public CommandBase
{
public:
	RetractKickerCommand() : CommandBase("RetractKickerCommand"){
		Requires(kicker.get());
		Requires(intake.get());
		SetInterruptible(false);
	}
	void Initialize(){
		SetTimeout(1);
		kicker->Retract();
	}
	void Execute(){}
	bool IsFinished(){
		return kicker->GetCurrentDraw() >= 10 || IsTimedOut();
	}
	void End(){
		kicker->Stop();
	}
	void Interrupted(){
		End();
	}
};

#endif
