#ifndef RoughRotationCommand_H
#define RoughRotationCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class RoughRotationCommand: public CommandBase
{
private:
	double m_angle;
	bool m_onTarget;
public:
	RoughRotationCommand(double angle) : CommandBase("RoughRotationCommand"){
		m_angle = angle;
		m_onTarget = false;
	}
	void Initialize(){
		if (driveTrain->GetAngle() > m_angle){
			driveTrain->TankRaw(.7,-.7);
		}
		else if (driveTrain->GetAngle() < m_angle) {
			driveTrain->TankRaw(-.7,.7);
		}
	}
	void Execute(){
		if (driveTrain->GetAngle() <= m_angle + .5 && driveTrain->GetAngle() >= m_angle - .5) {
			m_onTarget = true;
		}
		else {
			m_onTarget = false;
		}
	}
	bool IsFinished(){
		return m_onTarget;
	}
	void End(){
		driveTrain->TankRaw(0,0);
	}
	void Interrupted(){
		End();
	}
};

#endif
