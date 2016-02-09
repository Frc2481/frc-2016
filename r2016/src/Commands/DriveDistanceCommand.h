#ifndef DriveDistanceCommand_H
#define DriveDistanceCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveDistanceCommand: public CommandBase
{
private:
	double m_distance;
public:
	DriveDistanceCommand(double distance) : CommandBase("DriveDistanceCommand"){
		m_distance = distance;
	}
	void Initialize(){
		driveTrain->SetToDistanceMode();
		driveTrain->SetSetpoint(m_distance);
	}
	void Execute(){}
	bool IsFinished(){
		return driveTrain->IsAtSetpoint();
	}
	void End(){
		driveTrain->SetToVoltageMode();
	}
	void Interrupted(){
		End();
	}
};

#endif
