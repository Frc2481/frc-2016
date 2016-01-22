#ifndef LiftDownCommand_H
#define LiftDownCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class LiftDownCommand: public CommandBase
{
public:
	LiftDownCommand() : Subsystem("Lift Down Command"){
		Requires (lift.get());
	}

	void Initialize(){
			lift->SetLiftSpeed(LIFT_DOWN_SPEED);
	}

	void Execute(){

	}

	bool IsFinished(){
		return false;
	}

	void End(){
		lift->SetLiftSpeed(0);
	}

	void Interrupted(){

	}
};

#endif
