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
		AddParallel(new TurnLightRingOnCommand());
		AddParallel(new TurnOnShooterCommand());
		AddSequential(new DriveDistanceCommand(.7,.7,650));
	}
};

#endif
