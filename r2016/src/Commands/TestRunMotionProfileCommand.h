#ifndef TestRunMotionProfileCommand_H
#define TestRunMotionProfileCommand_H

#include "../CommandBase.h"
#include "../MotionProfiles/Instrumentation.h"
#include "WPILib.h"

class TestRunMotionProfileCommand: public CommandBase
{
public:
	TestRunMotionProfileCommand(){
		SetRunWhenDisabled(true);
		Requires(driveTrain.get());
	}
	void Initialize(){
		driveTrain->GetProfileGenerator()->GenerateMotionProfile(15);
		driveTrain->StartMotionProfile();

	}
	void Execute(){
//		driveTrain->GetProfileGenerator()->GenerateMotionProfile(15);
	}
	bool IsFinished(){
		return driveTrain->IsMPFinished();
	}
	void End(){
//		driveTrain->StopMotionProfile();
	}
	void Interrupted(){
		End();
	}
};

#endif
