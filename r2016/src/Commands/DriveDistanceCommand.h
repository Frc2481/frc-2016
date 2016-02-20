#ifndef DriveDistanceCommand_H
#define DriveDistanceCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveDistanceCommand: public CommandBase
{
private:
	double m_distance;
	double m_offset;
	double m_rightSpeed;
	double m_leftSpeed;
public:
	DriveDistanceCommand(double rightSpeed, double leftSpeed, double distance) : CommandBase("DriveDistanceCommand"){
		Requires(driveTrain.get());
		m_rightSpeed = rightSpeed;
		m_leftSpeed = leftSpeed;
		m_distance = -distance;
	}
	void Initialize(){
		m_offset = driveTrain->GetEncoderPos();
		driveTrain->Tank(-m_rightSpeed,-m_leftSpeed);
	}
	void Execute(){}
	bool IsFinished(){
		return driveTrain->GetEncoderPos() < m_distance + m_offset;
	}
	void End(){
		driveTrain->SetToVoltageMode();
		driveTrain->StopMotors();
	}
	void Interrupted(){
		End();
	}
};

#endif
