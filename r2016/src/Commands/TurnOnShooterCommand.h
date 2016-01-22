#ifndef TurnOnShooterCommand_H
#define TurnOnShooterCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class TurnOnShooterCommand: public CommandBase
{
public:
	TurnOnShooterCommand() : Subsystem("Turn On Shooter Command"){
		Requires(shooter.get());
	}
	void Initialize(){
		shooter->TurnOn();
	}
	void Execute(){
	}
	bool IsFinished(){
		return false;
	}
	void End(){
		shooter->TurnOff();
	}
	void Interrupted(){
		End();
	}
};

#endif
