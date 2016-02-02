#ifndef TurnOnShooterCommand_H
#define TurnOnShooterCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class TurnOnShooterCommand: public CommandBase
{
private:
	double m_shooterSpd;
public:
	TurnOnShooterCommand(double spd = -1) : CommandBase("TurnOnShooterCommand"){
		Requires(CommandBase::shooter.get());
		if (spd == -1){
			m_shooterSpd = SmartDashboard::GetNumber("Shooter Speed", 3300);
		}
		else {
			m_shooterSpd = spd;
		}
	}
	void Initialize(){
		shooter->SetShooterSpeed(m_shooterSpd);
	}
	void Execute(){}
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
