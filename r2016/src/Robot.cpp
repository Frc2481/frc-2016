#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/ExampleCommand.h"
#include "Commands/RotateToAngleCommand.h"
#include "Commands/TurnOnShooterCommand.h"
#include "Commands/TurnOffShooterCommand.h"
#include "Commands/TurnLightRingOnCommand.h"
#include "Commands/TraverseChevalFrieseCommandGroup.h"
#include "Commands/TraverseDrawbridgeCommand.h"
#include "Commands/TraverseMoatCommandGroup.h"
#include "Commands/TraverseRampartsCommandGroup.h"
#include "Commands/TraversePortCommand.h"
#include "Commands/TraversePortcullisCommand.h"
#include "Commands/TraverseTerrainCommandGroup.h"
#include "Commands/TraverseWallCommandGroup.h"
#include "Commands/OneBallAutoCommandGroup.h"
#include "Commands/TwoBallAutoCommandGroup.h"
#include "Commands/GeneratedAutoCommandGroup.h"
#include "Commands/FireBallCommandGroup.h"
#include "Commands/ExtendKickerCommand.h"
#include "Commands/RetractKickerCommand.h"
#include "CommandBase.h"

class Robot: public IterativeRobot
{
private:
	std::unique_ptr<Command> autonomousCommand;
	SendableChooser* m_defenseChooser;
	SendableChooser* m_posChooser;

	void RobotInit()
	{
		CommandBase::init();

		m_defenseChooser = new SendableChooser();
		//Group A
		m_defenseChooser->AddObject("Portcullis", new TraversePortcullisCommand());
		m_defenseChooser->AddObject("Cheval de Friese", new TraverseChevalFrieseCommandGroup());

		//Group B
		m_defenseChooser->AddObject("Moat", new TraverseMoatCommandGroup());
		m_defenseChooser->AddObject("Ramparts", new TraverseRampartsCommandGroup());

		//Group C
		m_defenseChooser->AddObject("Drawbridge", new TraverseDrawbridgeCommand());
		m_defenseChooser->AddObject("Sally Port", new TraversePortCommand());

		//Group D
		m_defenseChooser->AddObject("Rock Wall", new TraverseWallCommandGroup());
		m_defenseChooser->AddObject("Rough Terrain", new TraverseTerrainCommandGroup());

		m_posChooser = new SendableChooser();
		m_posChooser->AddObject("Pos 1", (void*)1);
		m_posChooser->AddObject("Pos 2", (void*)2);
		m_posChooser->AddObject("Pos 3", (void*)3);
		m_posChooser->AddObject("Pos 4", (void*)4);
		m_posChooser->AddObject("Pos 5", (void*)5);

		SmartDashboard::PutData("Rotate To Angle", (PIDCommand*)(new RotateToAngleCommand(0)));
		SmartDashboard::PutData("Rotate To Angle With Camera", new RotateToAngleFromCameraCommand());
		SmartDashboard::PutData("TurnOnShooterCommand Run", new TurnOnShooterCommand());
		SmartDashboard::PutData("TurnOnShooterCommand 5000", new TurnOnShooterCommand(5000));
		SmartDashboard::PutData("TurnOffShooterCommand", new TurnOffShooterCommand());
		SmartDashboard::PutData("Turn Light Ring On", new TurnLightRingOnCommand());
		SmartDashboard::PutData("FireBallCommand", new FireBallCommandGroup());
		SmartDashboard::PutData("ExtendKickerCommand", new ExtendKickerCommand());
		SmartDashboard::PutData("RetractKickerCommand", new RetractKickerCommand());
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
		autonomousCommand.reset(new GeneratedAutoCommandGroup((Command*)m_defenseChooser->GetSelected(), (int)m_posChooser->GetSelected()));
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

