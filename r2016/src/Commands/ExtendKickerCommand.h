#ifndef ExtendKickerCommand_H
#define ExtendKickerCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ExtendKickerCommand: public CommandBase
{
private:
	bool m_skip;
	int m_onTargetCounter;
public:
	ExtendKickerCommand(): CommandBase("ExtendKickerCommand"){
		SetInterruptible(false);
		Requires(kicker.get());
		Requires(intake.get());
		m_skip = false;
		m_onTargetCounter = 0;
	}
	void Initialize(){
		SetTimeout(1);
		m_onTargetCounter = 0;
		if (!intake->IsLowered() && shooter->IsOnTarget()) {
			kicker->Extend();
			m_skip = false;
		}
		else {
			m_skip = true;
		}
	}
	void Execute(){
		if (kicker->GetCurrentDraw() >= 20) {
			m_onTargetCounter++;
		}
		else {
			m_onTargetCounter = 0;
		}
	}
	bool IsFinished(){
		return m_onTargetCounter >= 5 || m_skip || IsTimedOut();
	}
	void End(){
		kicker->Stop();
	}
	void Interrupted(){
		End();
	}
};

#endif
