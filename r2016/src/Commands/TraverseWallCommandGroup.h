#ifndef TraverseWallCommandGroup_H
#define TraverseWallCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/AutoDriveCommand.h"
#include "Commands/DriveUntilLevelCommand.h"
#include "WPILib.h"

class TraverseWallCommandGroup: public CommandGroup
{
public:
	TraverseWallCommandGroup() : CommandGroup("TraverseWallCommandGroup"){
		AddSequential(new AutoDriveCommand(.4, .4, .1));
		AddSequential(new AutoDriveCommand(.8, .8, 1.5));
		AddParallel(new AutoDriveCommand(.5, .5));
		AddSequential(new DriveUntilLevelCommand());
		AddSequential(new AutoDriveCommand(0,0));
	}
};

#endif
