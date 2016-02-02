#ifndef RotateToAngleCommand_H
#define RotateToAngleCommand_H

#include "../CommandBase.h"
#include "RoboUtils.h"
#include "WPILib.h"

class RotateToAngleCommand: public PIDCommand
{
private:
	double m_angle;
	int m_onTarget;
public:
	RotateToAngleCommand(double angle, bool useCamera = false)
			: PIDCommand("RotateToAngle", .020, .002, 0){

		Requires(CommandBase::driveTrain.get());

		if (useCamera == false) {
			m_angle = angle;
		}
		else {
			CommandBase::mCameraProcessor->calculate();
			m_angle = CommandBase::mCameraProcessor->getAngle();
		}
		m_onTarget = 0;
		SetSetpoint(CommandBase::driveTrain->GetIMU()->GetAngle() + m_angle);
		SmartDashboard::PutNumber("Rotation I Zone", 10);
		SmartDashboard::PutNumber("DriveTrain Rotate I", .002);
		SmartDashboard::PutNumber("DriveTrain Rotate P", .020);
	}

	double ReturnPIDInput(){
		return RoboUtils::constrainDegNeg180To180(CommandBase::driveTrain->GetAngle());
	}

	void UsePIDOutput(double output){
		output = std::min(1.0, std::max(-1.0, output));
		CommandBase::driveTrain->TankRaw(-output, output);
	}


	void Initialize(){
		GetPIDController()->Reset();
		GetPIDController()->Enable();
		m_onTarget = 0;
	}

	void Execute(){
			double curError = fabs(GetSetpoint()-GetPosition());
			double P = SmartDashboard::GetNumber("DriveTrain Rotate P", 0);

			std::shared_ptr<PIDController> pid = GetPIDController();
			if (curError < SmartDashboard::GetNumber("Rotation I Zone", 10)) {
				double I = SmartDashboard::GetNumber("DriveTrain Rotate I", 0);
				pid->SetPID(P, I, pid->GetD());
			}
			else {
				pid->SetPID(P, 0, pid->GetD());
			}

			if (curError < .5) {
				m_onTarget++;
			}
			else {
				m_onTarget = 0;
			}
	}

	bool IsFinished(){
		return m_onTarget >= 5;
	}
	void End(){
		SmartDashboard::PutNumber("Rotate Time", TimeSinceInitialized());
	}
	void Interrupted(){}
};

#endif
