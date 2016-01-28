#ifndef FPSDriveCommand_H
#define FPSDriveCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class FPSDriveCommand: public CommandBase
{
public:
	FPSDriveCommand(){
		Requires(driveTrain.get());
	}
	void Initialize(){
		double driveSpeed = oi->GetDriveStick()->GetRawAxis(XboxController::xbLeftYAxis);
		double turnSpeed = oi->GetDriveStick()->GetRawAxis(XboxController::xbRightXAxis);
		driveTrain->FPSDrive(driveSpeed, turnSpeed);
	}
	void Execute(){}
	bool IsFinished(){
		return false;
	}
	void End(){}
	void Interrupted(){}
};

#endif
