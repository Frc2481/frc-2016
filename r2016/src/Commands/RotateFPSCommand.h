#ifndef RotateFPSCommand_H
#define RotateFPSCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class RotateFPSCommand: public CommandBase
{
private:
	double m_initAngle;
	double m_secondAngle;
	bool m_firstFinish;
	bool m_secondFinish;
	double m_tolerance;
public:
	RotateFPSCommand(int pos) : CommandBase("RotateFPSCommand"){
		m_firstFinish = false;
		m_secondFinish = false;
		if (pos == 2) {
			m_initAngle = -45;
			m_secondAngle = 45;
			m_tolerance = 5;
		}
		else if (pos == 3) {
			m_initAngle = 0;
			m_secondAngle = 0;
		}
		else if (pos == 4) {
			m_initAngle = 0;
			m_secondAngle = 0;
		}
		else if (pos == 5) {
			m_initAngle = 45;
			m_secondAngle = -45;
			m_tolerance = -5;
		}
	}
	void Initialize(){
		m_firstFinish = false;
		m_secondFinish = false;
	}
	void Execute(){
		if (!m_firstFinish) {
			if (RoboUtils::constrainDegNeg180To180(driveTrain->GetAngle()) >= m_initAngle + m_tolerance) {
				driveTrain->FPSDrive(.5, .25);
			}
			else if (RoboUtils::constrainDegNeg180To180(driveTrain->GetAngle() <= m_initAngle - m_tolerance)) {
				driveTrain->FPSDrive(.5, -.25);
			}
			else {
				m_firstFinish = true;
				driveTrain->FPSDrive(.5,0);
			}
		}
		else if (!m_secondFinish && m_firstFinish) {
			if (RoboUtils::constrainDegNeg180To180(driveTrain->GetAngle()) >= m_secondAngle - m_tolerance) {
				driveTrain->FPSDrive(.5, -.25);
			}
			else if (RoboUtils::constrainDegNeg180To180(driveTrain->GetAngle()) <= m_secondAngle + m_tolerance) {
				driveTrain->FPSDrive(.5, .25);
			}
			else {
				m_secondFinish = true;
			}
		}
	}
	bool IsFinished(){
		return m_secondFinish;
	}
	void End(){
		driveTrain->TankRaw(0,0);
	}
	void Interrupted(){
		End();
	}
};

#endif
