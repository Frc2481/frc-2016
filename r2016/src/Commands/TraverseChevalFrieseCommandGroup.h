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
		AddSequential(new DriveDistanceCommand(.8,.8,5000));
		AddSequential(new RaiseIntakeCommand());
		AddSequential(new AutoDriveCommand(.6,.6));
		AddSequential(new DriveUntilLevelCommand());
		AddSequential(new WaitCommand(1));
	}
};

#endif
