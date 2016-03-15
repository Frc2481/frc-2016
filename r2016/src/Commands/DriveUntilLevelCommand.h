#ifndef DriveUntilLevelCommand_H
#define DriveUntilLevelCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveUntilLevelCommand: public CommandBase
{
private:
	int m_onTargetCounter;
public:
	DriveUntilLevelCommand() : CommandBase("DriveUntilLevelCommand"){
		m_onTargetCounter = 0;
	}
	void Initialize(){
		m_onTargetCounter = 0;
	}
	void Execute(){
		if (fabs(driveTrain->GetPitch()) <= 2) {
			m_onTargetCounter++;
		}
		else{
			m_onTargetCounter = 0;
		}
	}
	bool IsFinished(){
		return m_onTargetCounter >= 3;
	}
	void End(){}
	void Interrupted(){}
};

#endif
