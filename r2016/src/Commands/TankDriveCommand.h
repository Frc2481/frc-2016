#ifndef TankDriveCommand_H
#define TankDriveCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class TankDriveCommand: public CommandBase
{
public:
	TankDriveCommand(){
		Requires(driveTrain.get());
	}
	void Initialize(){}
	void Execute(){
		double left = oi->driveStick->GetRawAxis(XboxController::xbLeftXAxis);
		double right = oi->driveStick->GetRawAxis(XboxController::xbRightXAxis);
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
