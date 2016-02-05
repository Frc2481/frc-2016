#ifndef TwoBallAutoCommandGroup_H
#define TwoBallAutoCommandGroup_H

#include "Commands/CommandGroup.h"
#include "AutoDriveCommand.h"
#include "AutoTraverseCommand.h"
#include "LiftUpCommand.h"
#include "FireBallCommand.h"
#include "ExtendIntakeCommand.h"
#include "RetractIntakeCommand.h"
#include "TurnOffShooterCommand.h"
#include "TurnOnShooterCommand.h"
#include "RotateToAngleCommand.h"
#include "WPILib.h"

class TwoBallAutoCommandGroup: public CommandGroup
{
public:
	TwoBallAutoCommandGroup(): CommandGroup("TwoBallAuto"){
		//First Traverse
		AddParallel(new AutoDriveCommand(.4,.4,.5));
		AddSequential(new LiftUpCommand());
		AddSequential(new AutoTraverseCommand());
		AddParallel(new RotateToAngleFromCameraCommand());
		AddSequential(new TurnOnShooterCommand(.5));
		AddSequential(new FireBallCommand(.5));

		//Second Traverse
		AddParallel(new RotateToAngleCommand(180));
		AddSequential(new TurnOffShooterCommand());
		AddSequential(new AutoTraverseCommand());
		AddParallel(new AutoDriveCommand(.4,.4,.5));
		AddSequential(new ExtendIntakeCommand());
		AddParallel(new RetractIntakeCommand());
		AddSequential(new WaitCommand(.25));
		AddSequential(new RotateToAngleCommand(0));

		//Third Traverse
		AddParallel(new AutoDriveCommand(.4,.4,.5));
		AddSequential(new LiftUpCommand());
		AddSequential(new AutoTraverseCommand());
		AddParallel(new RotateToAngleFromCameraCommand());
		AddSequential(new TurnOnShooterCommand(.5));
		AddSequential(new FireBallCommand(.5));
	}
};

#endif
