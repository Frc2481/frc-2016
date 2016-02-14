#ifndef AcquireBallCommandGroup_H
#define AcquireBallCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/IntakeBallCommandGroup.h"
#include "Commands/WaitCommand.h"
#include "Commands/WaitForBallCommand.h"
#include "Commands/BringIntakeUpCommandGroup.h"
#include "WPILib.h"

class AcquireBallCommandGroup: public CommandGroup
{
public:
	AcquireBallCommandGroup() : CommandGroup("AcquireBallCommandGroup"){
		AddParallel(new IntakeBallCommandGroup());
		AddSequential(new WaitCommand(.75));
		AddSequential(new WaitForBallCommand());
		AddSequential(new BringIntakeUpCommandGroup());
	}
};

#endif
