
#ifndef TraverseMoatCommandGroup_H
#define TraverseMoatCommandGroup_H

#include "Commands/CommandGroup.h"
#include "commands/DriveUntilLevelCommand.h"
#include "WPILib.h"

class TraverseMoatCommandGroup: public CommandGroup
{
public:
	TraverseMoatCommandGroup() : CommandGroup("TraverseMoatCommandGroup"){
		AddSequential(new AutoDriveCommand(1,1,2));
		AddSequential(new AutoDriveCommand(.5,.5));
		AddSequential(new DriveUntilLevelCommand());
	}
};

#endif
