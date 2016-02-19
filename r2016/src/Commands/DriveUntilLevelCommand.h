#ifndef DriveUntilLevelCommand_H
#define DriveUntilLevelCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveUntilLevelCommand: public CommandBase
{
private:
	int m_onTargetCounter;
public:
	DriveUntilLevelCommand() : CommandBase("DriveUntilLevelCommand"){}
	void Initialize(){
		m_onTargetCounter = 0;
	}
	void Execute(){
		if (fabs(driveTrain->GetRoll()) <= 2) {
			m_onTargetCounter++;
		}
	}
	bool IsFinished(){
		return m_onTargetCounter >= 10;
	}
	void End(){}
	void Interrupted(){}
};

#endif
