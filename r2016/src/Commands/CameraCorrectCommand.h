#ifndef CameraCorrectCommand_H
#define CameraCorrectCommand_H

#include "../CommandBase.h"
#include "RobotMap.h"
#include "WPILib.h"

class CameraCorrectCommand: public CommandBase
{
public:
	CameraCorrectCommand(){

	}
	void Initialize(){

	}
	void Execute(){
		if(CommandBase::mCameraProcessor->getAngle() < -CAMERA_TOLERANCE){
			CommandBase::driveTrain->TankRaw(-.1,.1);
		}
		else if(CommandBase::mCameraProcessor->getAngle() < CAMERA_TOLERANCE){
			CommandBase::driveTrain->TankRaw(.1,-.1);
		}
	}
	bool IsFinished(){
		return CommandBase::mCameraProcessor->isOnTarget();
	}
	void End(){
		CommandBase::driveTrain->TankRaw(0,0);
	}
	void Interrupted(){

	}
};

#endif
