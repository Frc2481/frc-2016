#ifndef ShiftDriveTrainCommand_H
#define ShiftDriveTrainCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShiftDriveTrainCommand: public CommandBase
{
private:
	bool m_shiftState;
public:
	ShiftDriveTrainCommand(bool state) : CommandBase("ShiftDriveTrainCommand"){
		Requires(driveTrain.get());
		m_shiftState = state;
	}
	void Initialize(){
		driveTrain->SetShifter(m_shiftState);
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
