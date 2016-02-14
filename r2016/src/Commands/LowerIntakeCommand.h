#ifndef LowerIntakeCommand_H
#define LowerIntakeCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class LowerIntakeCommand: public CommandBase
{
private:
	bool m_impeded;
public:
	LowerIntakeCommand() : CommandBase("LowerIntakeCommand"){
		Requires(intake.get());
		m_impeded = false;
	}
	void Initialize(){
		m_impeded = true;
		if(!kicker->IsExtended()){
			intake->Lower();
			m_impeded = false;
		}
	}
	void Execute(){}
	bool IsFinished(){
		return intake->IsLowered() || m_impeded;
	}
	void End(){}
	void Interrupted(){}
};

#endif
