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
	OneBallAutoCommandGroup(){
		AddParallel(new AutoDriveCommand(.4, .4, .5));
		AddSequential(new LiftUpCommand());
		AddSequential(new AutoTraverseCommand());
		AddParallel(new TurnOnShooterCommand());
		AddSequential(new RotateToAngleCommand(0, true));
		AddSequential(new FireBallCommand(.75));
		AddSequential(new TurnOffShooterCommand());
	}
};

#endif
