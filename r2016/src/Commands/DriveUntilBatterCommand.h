#ifndef DriveUntilBatterCommand_H
#define DriveUntilBatterCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveUntilBatterCommand: public CommandBase
{
private:
	int m_onTargetCounter;
public:
	DriveUntilBatterCommand() : CommandBase("DriveUntilBatterCommand"){
		m_onTargetCounter = 0;
	}
	void Initialize(){
		m_onTargetCounter = 0;
	}
	void Execute(){
		if (fabs(driveTrain->GetPitch()) > 3){
			m_onTargetCounter++;
		}
		else{
			m_onTargetCounter = 0;
		}
	}
	bool IsFinished(){
		return m_onTargetCounter >= 3;
	}
	void End(){
		driveTrain->StopMotors();
	}
	void Interrupted(){}
};

#endif
