#ifndef TurnLightRingOnCommand_H
#define TurnLightRingOnCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class TurnLightRingOnCommand: public CommandBase
{
public:
	TurnLightRingOnCommand() : CommandBase("TurnLightRingOnCommand"){}
	void Initialize(){
		mCameraProcessor->SetLight(true);
	}
	void Execute(){}
	bool IsFinished(){
		return true; //return false;
	}
	void End(){}
	void Interrupted(){}
};

#endif
