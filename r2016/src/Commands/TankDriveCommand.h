#ifndef TankDriveCommand_H
#define TankDriveCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class TankDriveCommand: public CommandBase
{
public:
	TankDriveCommand(): CommandBase("TankDrive"){
		Requires(driveTrain.get());
	}
	void Initialize(){}
	void Execute(){
		double left = oi->GetDriveStick()->GetRawAxis(XboxController::xbLeftYAxis, true) +
				(oi->GetOperatorStick()->GetRawAxis(XboxController::xbLeftYAxis, true) / 3);
		double right = oi->GetDriveStick()->GetRawAxis(XboxController::xbRightYAxis, true) +
				(oi->GetOperatorStick()->GetRawAxis(XboxController::xbRightYAxis, true) / 3);
		driveTrain->Tank(right, left);
	}
	bool IsFinished(){
		return false;
	}
	void End(){
		driveTrain->StopMotors();
	}
	void Interrupted(){
		End();
	}
};

#endif
