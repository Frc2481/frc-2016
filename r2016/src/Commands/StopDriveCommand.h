#ifndef StopDriveCommand_H
#define StopDriveCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class StopDriveCommand: public CommandBase
{
public:
	StopDriveCommand() : CommandBase("StopDriveCommand"){
		Requires(driveTrain.get());
	}
	void Initialize(){}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
