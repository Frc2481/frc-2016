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
		AddSequential(new AutoDriveCommand(.35,.35,.5));
		AddSequential(new AutoDriveCommand(.85,.5,1));
		AddSequential(new AutoDriveCommand(.5,.5,1.25));
		AddParallel(new AutoDriveCommand(.5,.5));
		AddSequential(new DriveUntilLevelCommand());
	}
};

#endif
