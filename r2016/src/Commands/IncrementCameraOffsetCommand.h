#ifndef IncrementCameraOffsetCommand_H
#define IncrementCameraOffsetCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class IncrementCameraOffsetCommand: public CommandBase
{
public:
	IncrementCameraOffsetCommand() : CommandBase("IncrementCameraOffsetCommand"){
		SetRunWhenDisabled(true);
	}
	void Initialize(){
		mCameraProcessor->incOffsetAngle();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
