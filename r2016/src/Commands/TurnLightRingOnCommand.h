#ifndef TurnLightRingOnCommand_H
#define TurnLightRingOnCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class TurnLightRingOnCommand: public CommandBase
{
public:
	TurnLightRingOnCommand(){}
	void Initialize(){
		mCameraProcessor->SetLight(true);
	}
	void Execute(){}
	bool IsFinished(){
		return false;
	}
	void End(){
		mCameraProcessor->SetLight(false);
	}
	void Interrupted(){
		End();
	}
};

#endif
