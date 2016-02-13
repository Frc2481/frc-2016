#ifndef FireBallCommandGroup_H
#define FireBallCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/ExtendKickerCommand.h"
#include "Commands/RetractKickerCommand.h"
#include "Commands/WaitCommand.h"
#include "WPILib.h"

class FireBallCommandGroup: public CommandGroup
{
public:
	FireBallCommandGroup() : CommandGroup("FireBallCommandGroup"){
		AddSequential(new ExtendKickerCommand());
		AddSequential(new WaitCommand(.2));
		AddSequential(new RetractKickerCommand());
	}
};

#endif
