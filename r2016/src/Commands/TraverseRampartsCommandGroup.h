#ifndef TraverseRampartsCommandGroup_H
#define TraverseRampartsCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/AutoDriveCommand.h"
#include "Commands/DriveUntilLevelCommand.h"
#include "WPILib.h"

class TraverseRampartsCommandGroup: public CommandGroup
{
public:
	TraverseRampartsCommandGroup() : CommandGroup("TraverseRampartsCommandGroup"){
		AddSequential(new AutoDriveCommand(.5,.6,2));
		AddParallel(new AutoDriveCommand(.6,.6));
		AddSequential(new DriveUntilLevelCommand());
	}
};

#endif
