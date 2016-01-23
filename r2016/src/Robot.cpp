#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/ExampleCommand.h"
#include "Commands/RotateToAngleCommand.h"
#include "Commands/TurnOnShooterCommand.h"
#include "Commands/TurnOffShooterCommand.h"
#include "Commands/OneBallAutoCommandGroup.h"
#include "Commands/TwoBallAutoCommandGroup.h"
#include "CommandBase.h"

class Robot: public IterativeRobot
{
private:
	Command* autonomousCommand;
	SendableChooser *autoChooser;

	void RobotInit()
	{
		CommandBase::init();
		autoChooser = new SendableChooser();

		autoChooser->AddDefault("Nothing", (void*)0);
		autoChooser->AddObject("One Ball Auto", new OneBallAutoCommandGroup());
		autoChooser->AddObject("Two Ball Auto", new TwoBallAutoCommandGroup());
		SmartDashboard::PutData("Auto Chooser", autoChooser);
	}

	void DisabledInit()
	{
	}

	void DisabledPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void AutonomousInit()
	{
		autonomousCommand = (Command *)autoChooser->GetSelected();
		if (autonomousCommand != NULL)
			autonomousCommand->Start();
	}

	void AutonomousPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void TeleopInit()
	{
		if (autonomousCommand != NULL)
			autonomousCommand->Cancel();
	}

	void TeleopPeriodic()
	{

		CommandBase::mCameraProcessor->calculate();
		SmartDashboard::PutNumber("Area",CommandBase::mCameraProcessor->getArea());
		Scheduler::GetInstance()->Run();

		SmartDashboard::PutData("Rotate To Angle", new RotateToAngleCommand(45));
		SmartDashboard::PutData("TurnOnShooterCommand", new TurnOnShooterCommand());
		SmartDashboard::PutData("TurnOffShooterCommand", new TurnOffShooterCommand());
		SmartDashboard::PutNumber("Lift Speed",CommandBase::lift->GetLiftSpeed());
		SmartDashboard::PutNumber("Shooter Speed", CommandBase::shooter->GetShooterSpeed());
		SmartDashboard::PutNumber("Desired Shooter Speed", CommandBase::shooter->GetDesiredSpeed());

	}

	void TestPeriodic()
	{
		LiveWindow::GetInstance()->Run();
	}
};

START_ROBOT_CLASS(Robot)

