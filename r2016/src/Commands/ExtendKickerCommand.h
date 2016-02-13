#ifndef ExtendKickerCommand_H
#define ExtendKickerCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ExtendKickerCommand: public CommandBase
{
private:
	bool m_skip;
public:
	ExtendKickerCommand(): CommandBase("ExtendKickerCommand"){
		Requires(kicker.get());
		m_skip = false;
	}
	void Initialize(){
		m_skip = true;
		if (!intake->IsLowered()) {
			kicker->Extend();
			m_skip = false;
		}
	}
	void Execute(){}
	bool IsFinished(){
		return kicker->GetCurrentDraw() >= 10 || m_skip;
	}
	void End(){
		kicker->Stop();
	}
	void Interrupted(){
		End();
	}
};

#endif
