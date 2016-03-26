#ifndef TestRunMotionProfileCommand_H
#define TestRunMotionProfileCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class TestRunMotionProfileCommand: public CommandBase
{
public:
	TestRunMotionProfileCommand(){
		Requires(shooter.get());
	}
	void Initialize(){
		shooter->StartFilling();
		shooter->StartMotionProfile();
	}
	void Execute(){
	}
	bool IsFinished(){
		return false;
	}
	void End(){
		shooter->StopMotionProfile();
	}
	void Interrupted(){
		End();
	}
};

#endif
