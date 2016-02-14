#ifndef TraverseWallCommandGroup_H
#define TraverseWallCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/AutoDriveCommand.h"
#include "WPILib.h"

class TraverseWallCommandGroup: public CommandGroup
{
public:
	TraverseWallCommandGroup() : CommandGroup("TraverseWallCommandGroup"){
		AddSequential(new AutoDriveCommand(.25, .25, .5));
		AddSequential(new AutoDriveCommand(.6, .6, .25));
		AddSequential(new AutoDriveCommand(.25, .25, .5));
	}
};

#endif
