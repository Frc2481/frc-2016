#ifndef BringIntakeUpCommandGroup_H
#define BringIntakeUpCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/RaiseIntakeCommand.h"
#include "Commands/StopIntakeCommand.h"
#include "WPILib.h"

class BringIntakeUpCommandGroup: public CommandGroup
{
public:
	BringIntakeUpCommandGroup() : CommandGroup("BringIntakeUpCommandGroup"){
		AddParallel(new RaiseIntakeCommand());
		AddSequential(new WaitCommand(1.5));
		AddSequential(new StopIntakeCommand());
	}
};

#endif
