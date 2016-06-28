#ifndef AutoBlockOneCommandGroup_H
#define AutoBlockOneCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/ZeroGyroCommand.h"
#include "Commands/TurnLightRingOnCommand.h"
#include "Commands/TurnOnShooterCommand.h"
#include "Commands/DriveDistanceCommand.h"
#include "WPILib.h"

class AutoBlockOneCommandGroup: public CommandGroup
{
public:
	AutoBlockOneCommandGroup() : CommandGroup("AutoBlockOneCommandGroup"){
		AddSequential(new ZeroGyroCommand());
		AddParallel(new TurnOnShooterCommand());
		AddParallel(new TurnLightRingOnCommand());
		AddSequential(new DriveDistanceCommand(.35,.35,1000));
		AddSequential(new DriveDistanceCommand(1,1,9000));
	}
};

#endif
