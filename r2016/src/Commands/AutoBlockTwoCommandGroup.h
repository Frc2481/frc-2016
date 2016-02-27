#ifndef AutoBlockTwoCommandGroup_H
#define AutoBlockTwoCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/RotateToAngleCommand.h"
#include "Commands/ShooterOnTargetCommand.h"
#include "Commands/FireBallCommandGroup.h"
#include "Commands/TurnOffShooterCommand.h"
#include "WPILib.h"

class AutoBlockTwoCommandGroup: public CommandGroup
{
public:
	AutoBlockTwoCommandGroup() : CommandGroup("AutoBlockTwoCommandGroup"){
		AddSequential(new RotateToAngleFromCameraCommand());
		AddSequential(new ShooterOnTargetCommand());
		AddSequential(new FireBallCommandGroup());
		AddSequential(new TurnOffShooterCommand());
	}
};

#endif
