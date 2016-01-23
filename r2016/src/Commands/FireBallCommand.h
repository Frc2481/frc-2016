#ifndef FireBallCommand_H
#define FireBallCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class FireBallCommand: public CommandBase
{
public:
	FireBallCommand(double timeout): CommandBase("FireBallCommand"){
		SetTimeout(timeout);
	}
	void Initialize(){}
	void Execute(){
		lift->SetLiftSpeed(LIFT_UP_SPEED);
	}
	bool IsFinished(){
		return IsTimedOut();
	}
	void End(){
		lift->SetLiftSpeed(0);
	}
	void Interrupted(){
		End();
	}
};

#endif
