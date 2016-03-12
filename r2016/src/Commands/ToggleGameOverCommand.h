#ifndef ToggleGameOverCommand_H
#define ToggleGameOverCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ToggleGameOverCommand: public CommandBase
{
public:
	ToggleGameOverCommand(){
		SetRunWhenDisabled(true);
	}
	void Initialize(){
		if(SmartDashboard::GetBoolean("GAMEOVER", false)){
			SmartDashboard::PutBoolean("GAMEOVER", false);
		}else{
			SmartDashboard::PutBoolean("GAMEOVER", true);
		}
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
