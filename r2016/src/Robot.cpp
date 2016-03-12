#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/ExampleCommand.h"
#include "Commands/RotateToAngleCommand.h"
#include "Commands/TurnOnShooterCommand.h"
#include "Commands/TurnOffShooterCommand.h"
#include "Commands/TurnLightRingOnCommand.h"
#include "Commands/TraverseChevalFrieseCommandGroup.h"
#include "Commands/TraverseDrawbridgeCommandGroup.h"
#include "Commands/TraverseMoatCommandGroup.h"
#include "Commands/TraverseRampartsCommandGroup.h"
#include "Commands/TraversePortCommandGroup.h"
#include "Commands/TraversePortcullisCommandGroup.h"
#include "Commands/TraverseTerrainCommandGroup.h"
#include "Commands/TraverseWallCommandGroup.h"
#include "Commands/GeneratedAutoCommandGroup.h"
#include "Commands/FireBallCommandGroup.h"
#include "Commands/ExtendKickerCommand.h"
#include "Commands/RetractKickerCommand.h"
#include "Commands/WaitForBallTestCommandGroup.h"
#include "Commands/DriveDistanceCommand.h"
#include "Commands/ZeroGyroCommand.h"
#include "Commands/AutoBlockOneCommandGroup.h"
#include "Commands/AutoBlockTwoCommandGroup.h"
#include "Commands/TraversePortcullisCommandGroup.h"
#include "Commands/ToggleGameOverCommand.h"
#include "Commands/GeneratedAutoBatterShotsCommandGroup.h"
#include "Commands/SpyBotTwoBallAutoCommandGroup.h"
#include "CommandBase.h"

class Robot: public IterativeRobot
{
private:
	std::unique_ptr<Command> autonomousCommand;
	SendableChooser* m_defenseChooser;
	SendableChooser* m_posChooser;
	SendableChooser* m_backChooser;
	SendableChooser* m_autoChooser;
	Compressor* m_compressor;

	bool m_GAMEOVER;

	void RobotInit()
	{
		CommandBase::init();

		SmartDashboard::PutBoolean("GAMEOVER", false);

		m_compressor = new Compressor();
		m_compressor->SetClosedLoopControl(true);

		m_defenseChooser = new SendableChooser();
		//Group A
		m_defenseChooser->AddObject("Portcullis", new TraversePortcullisCommandGroup());
		m_defenseChooser->AddObject("Cheval de Friese", new TraverseChevalFrieseCommandGroup());

		//Group B
		m_defenseChooser->AddObject("Moat", new TraverseMoatCommandGroup());
		m_defenseChooser->AddObject("Ramparts", new TraverseRampartsCommandGroup());

		//Group C
		m_defenseChooser->AddObject("Drawbridge", new TraverseDrawbridgeCommandGroup());
		m_defenseChooser->AddObject("Sally Port", new TraversePortCommandGroup());

		//Group D
		m_defenseChooser->AddObject("Rock Wall", new TraverseWallCommandGroup());
		m_defenseChooser->AddObject("Rough Terrain", new TraverseTerrainCommandGroup());

		m_defenseChooser->AddDefault("Nothing", (void*)0);

		SmartDashboard::PutData("Defense Chooser",m_defenseChooser);

		m_posChooser = new SendableChooser();
		m_posChooser->AddDefault("Nothing", NULL);
		m_posChooser->AddObject("Pos 1", (void*)1);
		m_posChooser->AddObject("Pos 2", (void*)2);
		m_posChooser->AddObject("Pos 3", (void*)3);
		m_posChooser->AddObject("Pos 4", (void*)4);
		m_posChooser->AddObject("Pos 5", (void*)5);

		SmartDashboard::PutData("Position Chooser", m_posChooser);

		m_backChooser = new SendableChooser();
		m_backChooser->AddDefault("Nothing", NULL);
		m_backChooser->AddObject("Drive Back", (void*)1);
		SmartDashboard::PutData("Back Chooser", m_backChooser);

		m_autoChooser = new SendableChooser();
		m_autoChooser->AddDefault("Nothing", NULL);
		m_autoChooser->AddObject("Normal Auto", (void*)1);
		m_autoChooser->AddObject("Batter Shot", (void*)2);
		m_autoChooser->AddObject("Spy Bot Two Ball. KOBE!", (void*)3);
		SmartDashboard::PutData("AutoChooser", m_autoChooser);

		SmartDashboard::PutData("Rotate To Angle", (PIDCommand*)(new RotateToAngleCommand(0)));
		SmartDashboard::PutData("Turn Light Ring On", new TurnLightRingOnCommand());
		SmartDashboard::PutData("ExtendKickerCommand", new ExtendKickerCommand());
		SmartDashboard::PutData("RetractKickerCommand", new RetractKickerCommand());
		SmartDashboard::PutData("WaitForBallCommandGroup", new WaitForBallTestCommandGroup());
		SmartDashboard::PutData("Zero Gyro Command", new ZeroGyroCommand());
		SmartDashboard::PutData("AutoBlockOneCommand", new AutoBlockOneCommandGroup());
		SmartDashboard::PutData("AutoBlockTwoCommand", new AutoBlockTwoCommandGroup());
		SmartDashboard::PutData("Rotate180Command", new Rotate180Command());

		SmartDashboard::PutData("TraverseChevalFrieseCommandGroup", new TraverseChevalFrieseCommandGroup());
		SmartDashboard::PutData("TraverseTerrainCommandGroup", new TraverseTerrainCommandGroup());
		SmartDashboard::PutData("TraverseRampartsCommandGroup", new TraverseRampartsCommandGroup());
		SmartDashboard::PutData("TraversePortcullisCommandGroup", new TraversePortcullisCommandGroup());
		SmartDashboard::PutData("TraverseRockWallCommandGroup", new TraverseWallCommandGroup());
		SmartDashboard::PutData("TraverseMoatCommandGroup", new TraverseMoatCommandGroup());

		SmartDashboard::PutData("Toggle GameOver", new ToggleGameOverCommand());

		SmartDashboard::PutBoolean("Gyro on Target", false);

		SmartDashboard::PutBoolean("Shooter on Target", false);
		SmartDashboard::PutNumber("Camera Scale", 1.35275);
		SmartDashboard::PutNumber("Desired Shooter Speed", CommandBase::shooter->GetDesiredSpeed());
	}

	void DisabledInit()
	{
	}

	void DisabledPeriodic()
	{
		Scheduler::GetInstance()->Run();
		if(DriverStation::GetInstance().IsFMSAttached() && DriverStation::GetInstance().GetMatchTime() >= 150){
			SmartDashboard::PutBoolean("GAMEOVER", true);
		}
	}

	void AutonomousInit()
	{
		if ((int)m_autoChooser->GetSelected() == 1){
			autonomousCommand.reset(new GeneratedAutoCommandGroup((Command*)m_defenseChooser->GetSelected(),
				(int)m_posChooser->GetSelected(),
				(int)m_backChooser->GetSelected()));
		}
		else if((int)m_autoChooser->GetSelected() == 2){
			autonomousCommand.reset(new GeneratedAutoBatterShotsCommandGroup((Command*)m_defenseChooser->GetSelected(), (int)m_posChooser->GetSelected()));
		}
		else if((int)m_autoChooser->GetSelected() == 3){
			autonomousCommand.reset(new SpyBotTwoBallAutoCommandGroup((Command*)m_defenseChooser->GetSelected()));
		}
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
		Scheduler::GetInstance()->Run();
	}

	void TestPeriodic()
	{
		LiveWindow::GetInstance()->Run();
	}
};

START_ROBOT_CLASS(Robot)

