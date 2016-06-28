#ifndef RotateToAngleCommand_H
#define RotateToAngleCommand_H

#include "../CommandBase.h"
#include "RoboUtils.h"
#include "WPILib.h"

class RotateToAngleCommand: public PIDCommand
{
protected:
	double m_angle;
	double m_onTargetTolerance;
	bool m_skip;
	int m_onTarget;
public:
	RotateToAngleCommand(double angle)
			: PIDCommand("RotateToAngle", .04, .025, 0){
		Requires(CommandBase::driveTrain.get());
		m_angle = angle;
		m_onTarget = 0;
		m_onTargetTolerance = 3;
		SmartDashboard::PutNumber("Rotation I Zone", 4);
		SmartDashboard::PutNumber("DriveTrain Rotate D", 0);
		SmartDashboard::PutNumber("DriveTrain Rotate I", .025);
		SmartDashboard::PutNumber("DriveTrain Rotate P", .04);
		SmartDashboard::PutNumber("Rotation Ontarget Time", 5);
	}

	double ReturnPIDInput(){
		return constrain(CommandBase::driveTrain->GetAngle());
	}

	virtual void UsePIDOutput(double output){
		output = std::min(1.0, std::max(-1.0, output));
		CommandBase::driveTrain->TankRaw(output, -output);
	}

	virtual double constrain(double angle) {
		return RoboUtils::constrainDegNeg180To180(angle);
	}

	virtual void Initialize(){
		GetPIDController()->Reset();
		GetPIDController()->Enable();
		m_onTarget = 0;
		m_skip = false;
		m_angle = constrain(m_angle);
		SmartDashboard::PutNumber("Commanded absolute angle", m_angle);
		SetSetpoint(m_angle);
	}

	void Execute(){
		double curError = fabs(GetSetpoint()-GetPosition());
		SmartDashboard::PutNumber("Rotation Error", curError);
		double P = SmartDashboard::GetNumber("DriveTrain Rotate P", 0);
		double D = SmartDashboard::GetNumber("DriveTrain Rotate D", 0);

		std::shared_ptr<PIDController> pid = GetPIDController();
		if (curError < SmartDashboard::GetNumber("Rotation I Zone", 10)) {
			double I = SmartDashboard::GetNumber("DriveTrain Rotate I", 0);
			pid->SetPID(P, I, D);
		}
		else {
			pid->SetPID(P, 0, D);
		}
		if (curError < m_onTargetTolerance) {
			m_onTarget++;
		}
		else {
			m_onTarget = 0;
		}
	}

	bool IsFinished(){

		if (fabs(CommandBase::oi->GetDriveStick()->GetRawAxis(XboxController::xbLeftYAxis)) > .25 ||
				fabs(CommandBase::oi->GetDriveStick()->GetRawAxis(XboxController::xbRightYAxis)) > .25 ||
				fabs(CommandBase::oi->GetOperatorStick()->GetRawAxis(XboxController::xbLeftYAxis)) > .25 ||
				fabs(CommandBase::oi->GetOperatorStick()->GetRawAxis(XboxController::xbRightYAxis)) > .25) {
			return true;
		}


		return m_onTarget >= SmartDashboard::GetNumber("Rotation Ontarget Time", 5) || m_skip;
	}
	void End(){
		SmartDashboard::PutNumber("Rotate Time", TimeSinceInitialized());
	}
	void Interrupted(){}
};

class RotateToAngleFromCameraCommand : public RotateToAngleCommand {
public:
	RotateToAngleFromCameraCommand() : RotateToAngleCommand(0) {
		m_skip = false;
	}

	void Initialize(){
		m_skip = false;
		m_onTargetTolerance = .5; //.25;
		if(CommandBase::mCameraProcessor->isTargetAvailable()){
			double scale = SmartDashboard::GetNumber("Camera Scale", 1.35275); //30.37 / 14.19; //TODO: Figure out why the camera or gyro angle is wrong.

//			printf("raw relative angle = %f\n", CommandBase::mCameraProcessor->getAngle());
			m_angle = CommandBase::mCameraProcessor->getAngle();
			m_angle *= scale;

//			printf("scaled relative angle = %f\n", m_angle);
			m_angle += CommandBase::driveTrain->GetAngle();

//			printf("current driveTrain angle = %f\n", CommandBase::driveTrain->GetAngle());
//			printf("absolute angle with offset = %f\n", m_angle);
			RotateToAngleCommand::Initialize();
		} else {
			m_skip = true;
		}
	}
};

class Rotate180Command : public RotateToAngleCommand {
private:
	double m_radiusScale;

public:
	Rotate180Command(double radiusScale=1) : RotateToAngleCommand(180), m_radiusScale(radiusScale){
	}

	double constrain(double angle) {
		return RoboUtils::constrainDeg0To360(angle);
	}

	void UsePIDOutput(double output){
		output = std::min(1.0, std::max(-1.0, output));
		CommandBase::driveTrain->TankRaw(output, -output * m_radiusScale);
	}
};


#endif
