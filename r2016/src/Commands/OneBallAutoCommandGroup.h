#ifndef OneBallAutoCommandGroup_H
#define OneBallAutoCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/TurnOnShooterCommand.h"
#include "Commands/TurnOffShooterCommand.h"
#include "Commands/FireBallCommandGroup.h"
#include "Commands/ShooterOnTargetCommand.h"
#include "WPILib.h"

class OneBallAutoCommandGroup: public CommandGroup
{
public:
	OneBallAutoCommandGroup() : CommandGroup("OneBallAuto"){
		AddSequential(new TurnOnShooterCommand());
		AddSequential(new ShooterOnTargetCommand());
		AddSequential(new FireBallCommandGroup());
		AddSequential(new TurnOffShooterCommand());
	}
};

#endif
