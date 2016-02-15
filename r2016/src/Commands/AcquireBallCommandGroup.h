#ifndef AcquireBallCommandGroup_H
#define AcquireBallCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/IntakeBallCommandGroup.h"
#include "Commands/WaitCommand.h"
#include "Commands/WaitForBallCommand.h"
#include "Commands/BringIntakeUpCommandGroup.h"
#include "Commands/AutoDriveCommand.h"
#include "WPILib.h"

class AcquireBallCommandGroup: public CommandGroup
{
public:
	AcquireBallCommandGroup() : CommandGroup("AcquireBallCommandGroup"){
		AddParallel(new IntakeBallCommandGroup());
		AddParallel(new WaitCommand(.75));
		AddSequential(new AutoDriveCommand(.5, .5));
		AddSequential(new WaitForBallCommand());
		AddSequential(new AutoDriveCommand(0, 0, .11));
		AddSequential(new BringIntakeUpCommandGroup());
	}
};

#endif
