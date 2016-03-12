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
		Requires(kicker.get());
		m_skip = false;
		m_onTargetCounter = 0;
	}
	void Initialize(){
		m_skip = true;
		m_onTargetCounter = 0;
	}
	void Execute(){
		if (!intake->IsLowered()) {
			kicker->Extend();
			m_skip = false;
			if (kicker->GetCurrentDraw() >= 10) {
				m_onTargetCounter++;
			}
			else {
				m_onTargetCounter = 0;
			}
		}
		else {
			m_skip = true;
		}
	}
	bool IsFinished(){
		return m_onTargetCounter >= 50 || m_skip;
	}
	void End(){
		kicker->Stop();
	}
	void Interrupted(){
		End();
	}
};

#endif
