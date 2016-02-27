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
		AddSequential(new WaitCommand(1));
		AddSequential(new DriveDistanceCommand(.5,.5,500));
		AddSequential(new RaiseIntakeCommand());
		AddSequential(new DriveDistanceCommand(.5,.5,500));
		AddSequential(new WaitCommand(1));
	}
};

#endif
