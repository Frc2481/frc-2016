#ifndef TraverseChevalFrieseCommandGroup_H
#define TraverseChevalFrieseCommandGroup_H

#include "Commands/LowerIntakeCommand.h"
#include "Commands/RaiseIntakeCommand.h"
#include "Commands/CommandGroup.h"
#include "Commands/DriveDistanceCommand.h"
#include "Commands/AutoDriveCommand.h"
#include "WPILib.h"

class TraverseChevalFrieseCommandGroup: public CommandGroup
{
public:
	TraverseChevalFrieseCommandGroup() : CommandGroup("TraverseChevalFrieseCommandGroup"){
		AddSequential(new LowerIntakeCommand());
		AddSequential(new DriveDistanceCommand(500));
		AddParallel(new RaiseIntakeCommand());
		AddSequential(new AutoDriveCommand(0,0));
	}
};

#endif
