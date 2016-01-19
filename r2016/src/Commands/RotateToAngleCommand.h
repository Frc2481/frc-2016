#ifndef RotateToAngleCommand_H
#define RotateToAngleCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class RotateToAngleCommand: public CommandBase
{
private:
	double m_angle;
	double m_curError;
	double m_curAngle;
	bool m_clockwise;
	int m_onTargetCounter;
public:
	RotateToAngleCommand(double angle){
		Requires(driveTrain);
		m_angle = angle;
		m_curError = 0;
		m_clockwise = false;
		m_onTargetCounter = 0;
	}
	void Initialize(){

	}

	void Execute(){
			m_curError = driveTrain->RotateToAngleClock(m_angle);
			if (m_curError < 5) {
				m_onTargetCounter++;
			}
			else {
				m_onTargetCounter = 0;
			}
	}

	bool IsFinished(){
		return m_onTargetCounter >= 100;
	}
	void End(){
		driveTrain->StopMotors();
	}
	void Interrupted(){
		End();
	}
};

#endif
