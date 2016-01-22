#ifndef LiftUpCommand_H
#define LiftUpCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class LiftUpCommand: public CommandBase
{
public:
	LiftUpCommand() : CommandBase("Lift Up Command"){
		Requires(lift.get());
	}

	void Initialize(){
		if (!lift->HasBall()){
			lift->SetLiftSpeed(LIFT_UP_SPEED);
		}
	}

	void Execute(){

	}

	bool IsFinished(){
		return lift->HasBall();
	}

	void End(){
		lift->SetLiftSpeed(0);
	}

	void Interrupted(){
		End();
	}
};

#endif
