#ifndef TestRunMotionProfileCommand_H
#define TestRunMotionProfileCommand_H

#include "../CommandBase.h"
#include "../MotionProfiles/Instrumentation.h"
#include "WPILib.h"

class TestRunMotionProfileCommand: public CommandBase
{
public:
	TestRunMotionProfileCommand(){
		Requires(shooter.get());
	}
	void Initialize(){
		shooter->StartMotionProfile();

	}
	void Execute(){
//		shooter->PeriodicMotionProfile();
	}
	bool IsFinished(){
		return shooter->IsMPFinished();
	}
	void End(){
		shooter->StopMotionProfile();
	}
	void Interrupted(){
		End();
	}
};

#endif
