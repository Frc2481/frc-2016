#ifndef GameOverCommand_H
#define GameOverCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class GameOverCommand: public CommandBase
{
public:
	GameOverCommand() : CommandBase("GameOverCommand"){}
	void Initialize(){
		SmartDashboard::PutBoolean("GAME_OVER", true);
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
