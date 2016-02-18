#ifndef DriveDistanceCommand_H
#define DriveDistanceCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveDistanceCommand: public CommandBase
{
private:
	double m_distance;
	double m_offset;
public:
	DriveDistanceCommand(double distance) : CommandBase("DriveDistanceCommand"){
		Requires(driveTrain.get());
		m_distance = -distance;
//		driveTrain->ZeroEncoders();
	}
	void Initialize(){
		m_offset = driveTrain->GetEncoderPos();
		driveTrain->Tank(-.5,-.5);

//		driveTrain->SetToDistanceMode();
//		driveTrain->SetSetpoint(m_distance);
	}
	void Execute(){}
	bool IsFinished(){
		return driveTrain->GetEncoderPos() < m_distance + m_offset;
	}
	void End(){
		driveTrain->SetToVoltageMode();
		driveTrain->StopMotors();
//		driveTrain->ZeroEncoders();
	}
	void Interrupted(){
		End();
	}
};

#endif
