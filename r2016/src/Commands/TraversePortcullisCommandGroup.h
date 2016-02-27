#ifndef TraversePortcullisCommandGroup_H
#define TraversePortcullisCommandGroup_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"

class TraversePortcullisCommandGroup: public CommandGroup
{
public:
	TraversePortcullisCommandGroup() : CommandGroup("TraversePortcullisCommandGroup"){
		AddSequential(new LowerIntakeCommand());
		AddSequential(new AutoDriveCommand(.2,.2,.5));
		AddParallel(new RaiseIntakeCommand());
		AddSequential(new AutoDriveCommand(.5,.5,1));
	}
};

#endif
