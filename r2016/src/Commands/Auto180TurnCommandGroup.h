#ifndef Auto180TurnCommandGroup_H
#define Auto180TurnCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/RotateToAngleCommand.h"
#include "Commands/DriveDistanceCommand.h"
#include "WPILib.h"

class Auto180TurnCommandGroup: public CommandGroup
{
public:
	Auto180TurnCommandGroup() : CommandGroup("Auto180TurnCommandGroup"){
		AddSequential(new RotateToAngleCommand(90));
		AddSequential(new DriveDistanceCommand(.5,.5,500));
		AddSequential(new RotateToAngleCommand(180));
	}
};

#endif
