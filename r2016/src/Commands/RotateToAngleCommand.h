#ifndef RotateToAngleCommand_H
#define RotateToAngleCommand_H

#include "../CommandBase.h"
#include "RoboUtils.h"
#include "WPILib.h"

class RotateToAngleCommand: public PIDCommand
{
protected:
	double m_angle;
	int m_onTarget;
public:
	RotateToAngleCommand(double angle)
			: PIDCommand("RotateToAngle", .050, .004, 0){
		Requires(CommandBase::driveTrain.get());
		m_angle = angle;
		m_onTarget = 0;
		SmartDashboard::PutNumber("Rotation I Zone", 10);
		SmartDashboard::PutNumber("DriveTrain Rotate I", .004);
		SmartDashboard::PutNumber("DriveTrain Rotate P", .050);
		SmartDashboard::PutNumber("Rotation Ontarget Time", 5);
	}

	double ReturnPIDInput(){
		return RoboUtils::constrainDegNeg180To180(CommandBase::driveTrain->GetAngle());
	}

	void UsePIDOutput(double output){
		output = std::min(1.0, std::max(-1.0, output));
		CommandBase::driveTrain->TankRaw(-output, output);
	}


	virtual void Initialize(){
		GetPIDController()->Reset();
		GetPIDController()->Enable();
		m_onTarget = 0;

		double setpoint = m_angle;
		setpoint = RoboUtils::constrainDegNeg180To180(setpoint);
		SetSetpoint(setpoint);
	}

	void Execute(){
		double curError = fabs(GetSetpoint ()-GetPosition());
		SmartDashboard::PutNumber("Rotate Angle", curError);
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
		return m_onTarget >= SmartDashboard::GetNumber("Rotation Ontarget Time", 5);
	}
	void End(){
		SmartDashboard::PutNumber("Rotate Time", TimeSinceInitialized());
	}
	void Interrupted(){}
};

class RotateToAngleFromCameraCommand : public RotateToAngleCommand {
public:
	RotateToAngleFromCameraCommand() : RotateToAngleCommand(0) {
		SmartDashboard::PutNumber("Camera Offset", -7);
	}

	void Initialize(){
		double scale = 19.9 / 15.45; //TODO: Figure out why the camera or gyro angle is wrong.
		m_angle = CommandBase::mCameraProcessor->getAngle() * scale;
		m_angle += CommandBase::driveTrain->GetIMU()->GetAngle() - SmartDashboard::GetNumber("Camera Offset", -7);
		RotateToAngleCommand::Initialize();
	}
};


#endif
