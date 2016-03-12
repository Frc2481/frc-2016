#ifndef SpyBotTwoBallAutoCommandGroup_H
#define SpyBotTwoBallAutoCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/RotateToAngleCommand.h"
#include "Commands/WaitForBallTestCommandGroup.h"
#include "Commands/ZeroGyroCommand.h"
#include "Commands/AutoDriveCommand.h"
#include "Commands/DriveUntilBatterCommand.h"
#include "Commands/TurnOnShooterCommand.h"
#include "Commands/FireBallCommandGroup.h"
#include "Commands/TurnOffShooterCommand.h"
#include "Commands/ShiftDriveTrainCommand.h"
#include "WPILib.h"

class SpyBotTwoBallAutoCommandGroup: public CommandGroup
{
public:
	SpyBotTwoBallAutoCommandGroup(Command* traverseCommand) : CommandGroup("SpyBotTwoBallAutoCommandGroup"){
		AddSequential(new ZeroGyroCommand());
		AddSequential(new TurnOnShooterCommand());
		AddSequential(new ShooterOnTargetCommand());
		AddSequential(new FireBallCommandGroup());

		AddSequential(new ShiftDriveTrainCommand(true));
		AddSequential(new DriveDistanceCommand(.5,1,13000));
		AddSequential(new AutoDriveCommand(1,1,1));
		AddSequential(new ShiftDriveTrainCommand(false));
		AddParallel(new AutoDriveCommand(1,1));
		AddSequential(new DriveUntilBatterCommand());
		AddSequential(traverseCommand);

		AddSequential(new RotateToAngleCommand(0));		//Change to 180 for comp
		AddSequential(new WaitForBallTestCommandGroup());
		AddSequential(new Rotate180Command(1));
		AddSequential(new AutoDriveCommand(.7,.7,.5));
		AddParallel(new AutoDriveCommand(.7,.7));
		AddSequential(new DriveUntilBatterCommand());

		AddSequential(new TurnOnShooterCommand());
		AddSequential(traverseCommand);
		AddSequential(new AutoDriveCommand(.5,.5,.5));
		AddSequential(new WaitCommand(1));
		AddSequential(new ZeroGyroCommand());
		AddSequential(new RotateToAngleCommand(30));	//Position 2 rotation to tower
		AddSequential(new WaitCommand(.5));
		AddSequential(new RotateToAngleFromCameraCommand());
		AddSequential(new ShooterOnTargetCommand());
		AddSequential(new FireBallCommandGroup());
		AddSequential(new TurnOffShooterCommand());
	}
};

#endif
