#ifndef RaiseIntakeCommand_H
#define RaiseIntakeCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class RaiseIntakeCommand: public CommandBase
{
private:
	bool m_impeded;
public:
	RaiseIntakeCommand() : CommandBase("RaiseIntakeCommand"){
		Requires(intake.get());
		m_impeded = false;
	}
	void Initialize(){
		m_impeded = true;
		if(!kicker->IsExtended()){
			intake->Raise();
			m_impeded = false;
		}
	}
	void Execute(){}
	bool IsFinished(){
		return !intake->IsLowered() || m_impeded;
	}
	void End(){}
	void Interrupted(){}
};

#endif
