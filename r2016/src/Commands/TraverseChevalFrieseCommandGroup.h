#ifndef TraverseChevalFrieseCommandGroup_H
#define TraverseChevalFrieseCommandGroup_H

#include "Commands/LowerIntakeCommand.h"
#include "Commands/RaiseIntakeCommand.h"
#include "Commands/CommandGroup.h"
#include "Commands/DriveDistanceCommand.h"
#include "Commands/AutoDriveCommand.h"
#include "Commands/DriveUntilLevelCommand.h"
#include "WPILib.h"

class TraverseChevalFrieseCommandGroup: public CommandGroup
{
public:
	TraverseChevalFrieseCommandGroup() : CommandGroup("TraverseChevalFrieseCommandGroup"){
		AddSequential(new LowerIntakeCommand());
		AddSequential(new WaitCommand(2));
		AddSequential(new DriveDistanceCommand(.8,.8,7000));
		AddSequential(new RaiseIntakeCommand());
		AddSequential(new AutoDriveCommand(.8,.8));
		AddSequential(new DriveUntilLevelCommand());
		AddSequential(new AutoDriveCommand(.8,.8,.25));
		AddSequential(new WaitCommand(1));
	}
};

#endif
