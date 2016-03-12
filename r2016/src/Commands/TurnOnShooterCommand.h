#ifndef TurnOnShooterCommand_H
#define TurnOnShooterCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class TurnOnShooterCommand: public CommandBase
{
private:
	double m_spd;
public:
	TurnOnShooterCommand(double spd = -1) : CommandBase("TurnOnShooterCommand"){
		Requires(shooter.get());
		SmartDashboard::PutNumber("Shooter Speed", 3200);
		m_spd = spd;
	}
	void Initialize(){
		double shooterSpd;
		if (m_spd == -1){
			shooterSpd = SmartDashboard::GetNumber("Shooter Speed", 3200);
		}
		else {
			shooterSpd = m_spd;
		}
		shooter->SetShooterSpeed(shooterSpd);
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
