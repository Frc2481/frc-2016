#ifndef TurnOnShooterCommand_H
#define TurnOnShooterCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class TurnOnShooterCommand: public CommandBase
{
private:
	double m_shooterSpd;
	double m_spd;
public:
	TurnOnShooterCommand(double spd = -1) : CommandBase("TurnOnShooterCommand"){
		Requires(CommandBase::shooter.get());
		m_spd = spd;
		m_shooterSpd = 0;
	}
	void Initialize(){
		if (m_spd == -1){
			m_shooterSpd = SmartDashboard::GetNumber("Shooter Speed", 3300);
		}
		else {
			m_shooterSpd = m_spd;
		}
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
