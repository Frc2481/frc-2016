#ifndef TraverseRampartsCommandGroup_H
#define TraverseRampartsCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/AutoDriveCommand.h"
#include "WPILib.h"

class TraverseRampartsCommandGroup: public CommandGroup
{
public:
	TraverseRampartsCommandGroup() : CommandGroup("TraverseRampartsCommandGroup"){
		AddSequential(new AutoDriveCommand(.3, .3, .25));
		AddSequential(new AutoDriveCommand(.45, .3, .25));
		AddSequential(new AutoDriveCommand(.3, .3, .25));
		AddSequential(new AutoDriveCommand(.3, .45, .25));
		AddSequential(new AutoDriveCommand(.2, .2, .11));
	}
};

#endif
