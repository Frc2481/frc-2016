#ifndef TurnLightRingOffCommand_H
#define TurnLightRingOffCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class TurnLightRingOffCommand: public CommandBase
{
public:
	TurnLightRingOffCommand(){}
	void Initialize(){
		mCameraProcessor->SetLight(false);
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
