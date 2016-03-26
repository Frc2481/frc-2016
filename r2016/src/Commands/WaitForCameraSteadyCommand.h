#ifndef WaitForCameraSteadyCommand_H
#define WaitForCameraSteadyCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class WaitForCameraSteadyCommand: public CommandBase
{
public:
	WaitForCameraSteadyCommand() : CommandBase("WaitForCameraSteadyCommand"){
	}
	void Initialize(){}
	void Execute(){}
	bool IsFinished(){
		if (fabs(CommandBase::oi->GetDriveStick()->GetRawAxis(XboxController::xbLeftYAxis)) > .25 ||
			fabs(CommandBase::oi->GetDriveStick()->GetRawAxis(XboxController::xbRightYAxis)) > .25 ||
			fabs(CommandBase::oi->GetOperatorStick()->GetRawAxis(XboxController::xbLeftYAxis)) > .25 ||
			fabs(CommandBase::oi->GetOperatorStick()->GetRawAxis(XboxController::xbRightYAxis)) > .25) {
			return true;
		}
		return mCameraProcessor->isCameraSteady();
	}
	void End(){}
	void Interrupted(){}
};

#endif
