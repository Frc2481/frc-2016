#ifndef IntakeBallCommandGroup_H
#define IntakeBallCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/LowerIntakeCommand.h"
#include "Commands/TurnIntakeOnFwdCommand.h"
#include "Commands/RetractKickerCommand.h"
#include "WPILib.h"

class IntakeBallCommandGroup: public CommandGroup
{
public:
	IntakeBallCommandGroup() : CommandGroup("IntakeBallCommandGroup"){
		//AddSequential(new RetractKickerCommand());
		AddSequential(new LowerIntakeCommand());
		AddSequential(new TurnIntakeOnFwdCommand());
	}
};

#endif
