#ifndef AutoTraverseCommand_H
#define AutoTraverseCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class AutoTraverseCommand: public CommandBase
{
public:
	AutoTraverseCommand(): CommandBase("AutoTraverseCommand"){
		Requires(driveTrain.get());
	}
	void Initialize(){
		driveTrain->Tank(.5,.5);
	}
	void Execute(){}
	bool IsFinished(){
		return fabs(driveTrain->GetIMU()->GetRoll()) < .5;
	}
	void End(){
		driveTrain->Tank(0,0);
	}
	void Interrupted(){
		End();
	}
};

#endif
