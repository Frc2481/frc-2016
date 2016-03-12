#ifndef TraversePortcullisCommandGroup_H
#define TraversePortcullisCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/ToggleShooterPositionCommand.h"
#include "Commands/LowerIntakeCommand.h"
#include "Commands/AutoDriveCommand.h"
#include "Commands/RaiseIntakeCommand.h"
#include "Commands/WaitCommand.h"
#include "WPILib.h"

class TraversePortcullisCommandGroup: public CommandGroup
{
public:
	TraversePortcullisCommandGroup() : CommandGroup("TraversePortcullisCommandGroup"){
		AddSequential(new ToggleShooterPositionCommand());
		AddParallel(new LowerIntakeCommand());
		AddSequential(new WaitCommand(1));
		AddSequential(new AutoDriveCommand(.25,.25,1));
		AddParallel(new RaiseIntakeCommand());
		AddSequential(new AutoDriveCommand(.5,.5,1));
		AddSequential(new ToggleShooterPositionCommand());
	}
};

#endif
