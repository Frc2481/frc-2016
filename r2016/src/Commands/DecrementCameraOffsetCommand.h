#ifndef DecrementCameraOffsetCommand_H
#define DecrementCameraOffsetCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DecrementCameraOffsetCommand: public CommandBase
{
public:
	DecrementCameraOffsetCommand() : CommandBase("DecrementCameraOffsetCommand"){
		SetRunWhenDisabled(true);
	}
	void Initialize(){
		mCameraProcessor->decOffSetAngle();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
