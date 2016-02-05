#ifndef OneBallAutoCommandGroup_H
#define OneBallAutoCommandGroup_H

#include "Commands/CommandGroup.h"
#include "AutoDriveCommand.h"
#include "AutoTraverseCommand.h"
#include "TurnOnShooterCommand.h"
#include "TurnOffShooterCommand.h"
#include "LiftUpCommand.h"
#include "FireBallCommand.h"
#include "RotateToAngleCommand.h"
#include "WPILib.h"

class OneBallAutoCommandGroup: public CommandGroup
{
public:
	OneBallAutoCommandGroup() : CommandGroup("OneBallAuto"){
		AddParallel(new AutoDriveCommand(.4, .4, .5));
		AddSequential(new LiftUpCommand());
		AddSequential(new AutoTraverseCommand());
		AddParallel(new TurnOnShooterCommand(.5));
		AddSequential(new RotateToAngleFromCameraCommand());
		AddSequential(new FireBallCommand(.75));
		AddSequential(new TurnOffShooterCommand());
	}
};

#endif
