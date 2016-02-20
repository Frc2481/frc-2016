#ifndef TraverseMoatCommandGroup_H
#define TraverseMoatCommandGroup_H

#include "Commands/CommandGroup.h"
#include "commands/DriveUntilLevelCommand.h"
#include "WPILib.h"

class TraverseMoatCommandGroup: public CommandGroup
{
public:
	TraverseMoatCommandGroup() : CommandGroup("TraverseMoatCommandGroup"){
		AddSequential(new AutoDriveCommand(.7,.7,2));
		AddParallel(new AutoDriveCommand(.7,.7));
		AddSequential(new DriveUntilLevelCommand());
	}
};

#endif
