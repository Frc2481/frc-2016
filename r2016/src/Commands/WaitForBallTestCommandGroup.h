#ifndef WaitForBallTestCommandGroup_H
#define WaitForBallTestCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/AutoDriveCommand.h"
#include "Commands/WaitForBallCommand.h"
#include "Commands/IntakeBallCommandGroup.h"
#include "Commands/BringIntakeUpCommandGroup.h"
#include "WPILib.h"

class WaitForBallTestCommandGroup: public CommandGroup
{
public:
	WaitForBallTestCommandGroup() : CommandGroup("WaitForBallTestCommandGroup"){
		AddSequential(new IntakeBallCommandGroup());
		AddParallel(new AutoDriveCommand(.3,.3));
		AddSequential(new WaitCommand(.5));
		AddSequential(new WaitForBallCommand());
		AddSequential(new BringIntakeUpCommandGroup());
		AddSequential(new AutoDriveCommand(0,0,.11));
	}
};

#endif
