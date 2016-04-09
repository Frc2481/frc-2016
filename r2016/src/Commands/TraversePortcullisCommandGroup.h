#ifndef TraversePortcullisCommandGroup_H
#define TraversePortcullisCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/ToggleShooterPositionCommand.h"
#include "Commands/LowerIntakeCommand.h"
#include "Commands/AutoDriveCommand.h"
#include "Commands/RaiseIntakeCommand.h"
#include "Commands/WaitCommand.h"
#include "Commands/DriveDistanceCommand.h"
#include "WPILib.h"

class TraversePortcullisCommandGroup: public CommandGroup
{
public:
	TraversePortcullisCommandGroup() : CommandGroup("TraversePortcullisCommandGroup"){
		AddSequential(new AutoDriveCommand(0,0,1));
		AddSequential(new AutoDriveCommand(-.5,-.5,.25));
		AddSequential(new ToggleShooterPositionCommand());
		AddSequential(new LowerIntakeCommand());
		AddSequential(new WaitCommand(2));
		AddSequential(new AutoDriveCommand(.25,.25,1.5));
		AddSequential(new RaiseIntakeCommand());
		AddSequential(new WaitCommand(.5));
		AddSequential(new AutoDriveCommand(.25,.25,.5));
		AddSequential(new DriveDistanceCommand(.5,.5,16000));
		AddSequential(new ToggleShooterPositionCommand());
	}
};

#endif
