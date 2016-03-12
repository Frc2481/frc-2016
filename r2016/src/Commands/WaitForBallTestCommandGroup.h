#ifndef WaitForBallTestCommandGroup_H
#define WaitForBallTestCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/AutoDriveCommand.h"
#include "Commands/WaitForBallCommand.h"
#include "Commands/IntakeBallCommandGroup.h"
#include "Commands/BringIntakeUpCommandGroup.h"
#include "Commands/DriveDistanceCommand.h"
#include "WPILib.h"

class WaitForBallTestCommandGroup: public CommandGroup
{
public:
	WaitForBallTestCommandGroup() : CommandGroup("WaitForBallTestCommandGroup"){
		AddSequential(new IntakeBallCommandGroup());
		AddSequential(new WaitCommand(1));
		AddSequential(new DriveDistanceCommand(1,1,6000));
		AddParallel(new AutoDriveCommand(.4,.4));
//		AddSequential(new WaitCommand(.5));
		AddSequential(new WaitForBallCommand());
		AddSequential(new AutoDriveCommand(-.5,-.5,.5));
//		AddSequential(new AutoDriveCommand(0,0,.11));
		AddSequential(new BringIntakeUpCommandGroup());
	}
};

#endif
