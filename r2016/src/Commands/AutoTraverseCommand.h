#ifndef AutoTraverseCommand_H
#define AutoTraverseCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class AutoTraverseCommand: public CommandBase
{
private:
	bool m_done;
public:
	AutoTraverseCommand(): CommandBase("AutoTraverseCommand"){
		Requires(driveTrain.get());
	}
	void Initialize(){
		m_done = false;
		driveTrain->SetBrake(true);
		driveTrain->Tank(.5,.5);
	}
	void Execute(){
		if (fabs(driveTrain->GetIMU()->GetRoll()) < .5 && !m_done) {
			driveTrain->Tank(0,0);
			SetTimeout(TimeSinceInitialized() + .5);
			m_done = true;
		}
	}
	bool IsFinished(){
		return IsTimedOut();
	}
	void End(){
		driveTrain->Tank(0,0);
		driveTrain->SetBrake(false);
	}
	void Interrupted(){
		End();
	}
};

#endif
