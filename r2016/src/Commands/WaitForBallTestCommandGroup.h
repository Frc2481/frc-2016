#ifndef WaitForBallTestCommandGroup_H
#define WaitForBallTestCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/AutoDriveCommand.h"
#include "Commands/WaitForBallCommand.h"
#include "WPILib.h"

class WaitForBallTestCommandGroup: public CommandGroup
{
public:
	WaitForBallTestCommandGroup() : CommandGroup("WaitForBallTestCommandGroup"){
		AddParallel(new AutoDriveCommand(.5,.5));
		AddSequential(new WaitForBallCommand());
		AddSequential(new AutoDriveCommand(0,0,.11));
	}
};

#endif
