#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/ExampleCommand.h"
#include "Commands/RotateToAngleCommand.h"
#include "Commands/TurnOnShooterCommand.h"
#include "Commands/TurnOffShooterCommand.h"
#include "Commands/TurnLightRingOnCommand.h"
#include "Commands/OneBallAutoCommandGroup.h"
#include "Commands/TwoBallAutoCommandGroup.h"
#include "CommandBase.h"

class Robot: public IterativeRobot
{
private:
	std::unique_ptr<Command> autonomousCommand;
	SendableChooser *autoChooser;

	void RobotInit()
	{
		CommandBase::init();
		autoChooser = new SendableChooser();

		autoChooser->AddDefault("Nothing", (void*)0);
		autoChooser->AddObject("One Ball Auto", new OneBallAutoCommandGroup());
		autoChooser->AddObject("Two Ball Auto", new TwoBallAutoCommandGroup());
		SmartDashboard::PutData("Auto Chooser", autoChooser);

		SmartDashboard::PutData("Rotate To Angle", (PIDCommand*)(new RotateToAngleCommand(0)));
		SmartDashboard::PutData("Rotate To Angle With Camera", new RotateToAngleFromCameraCommand());
		SmartDashboard::PutData("TurnOnShooterCommand Run", new TurnOnShooterCommand());
		SmartDashboard::PutData("TurnOnShooterCommand 5000", new TurnOnShooterCommand(5000));
		SmartDashboard::PutData("TurnOffShooterCommand", new TurnOffShooterCommand());
		SmartDashboard::PutData("Turn Light Ring On", new TurnLightRingOnCommand());
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
		autonomousCommand.reset((Command*)autoChooser->GetSelected());
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

		SmartDashboard::PutData("Scheduler", Scheduler::GetInstance());
		CommandBase::mCameraProcessor->calculate();
		Scheduler::GetInstance()->Run();

		SmartDashboard::PutNumber("Lift Speed",CommandBase::lift->GetLiftSpeed());
		SmartDashboard::PutNumber("Desired Shooter Speed", CommandBase::shooter->GetDesiredSpeed());

	}

	void TestPeriodic()
	{
		LiveWindow::GetInstance()->Run();
	}
};

START_ROBOT_CLASS(Robot)

