#ifndef FPSDriveCommand_H
#define FPSDriveCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class FPSDriveCommand: public CommandBase
{
public:
	FPSDriveCommand() : CommandBase("FPSDriveCommand"){
		Requires(driveTrain.get());
	}
	void Initialize(){}
	void Execute(){
		double turnSpeed = oi->GetDriveStick()->GetRawAxis(XboxController::xbRightXAxis);
		double driveSpeed = oi->GetDriveStick()->GetRawAxis(XboxController::xbLeftYAxis);
		driveTrain->FPSDrive(turnSpeed * .5, driveSpeed * .75);
	}
	bool IsFinished(){
		return false;
	}
	void End(){}
	void Interrupted(){}
};

#endif
