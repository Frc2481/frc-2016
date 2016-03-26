#ifndef LockOnTargetCommand_H
#define LockOnTargetCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class LockOnTargetCommand: public CommandBase
{
private:
	CameraProcessor::target_type_t m_target;

public:
	LockOnTargetCommand(CameraProcessor::target_type_t target)
		: CommandBase("LockOnTargetCommand"), m_target(target) {
	}
	void Initialize(){
		CommandBase::mCameraProcessor->lockOnTarget(m_target);
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){
		End();
	}
};

#endif
