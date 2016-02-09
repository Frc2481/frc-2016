#ifndef FireBallCommand_H
#define FireBallCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class FireBallCommand: public CommandBase
{
public:
	FireBallCommand(): CommandBase("FireBallCommand"){
		SetTimeout(1);
	}
	void Initialize(){
		if (!intake->IsExtended()) {
			kicker->Extend();
		}
	}
	void Execute(){}
	bool IsFinished(){
		return IsTimedOut();
	}
	void End(){
		kicker->Retract();
	}
	void Interrupted(){
		End();
	}
};

#endif
