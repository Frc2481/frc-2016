#ifndef GeneratedAutoBatterShotsCommandGroup_H
#define GeneratedAutoBatterShotsCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/DriveDistanceCommand.h"
#include "Commands/DriveUntilBatterCommand.h"
#include "Commands/ToggleShooterPositionCommand.h"
#include "Commands/AutoBlockOneCommandGroup.h"
#include "Commands/RotateToAngleCommand.h"
#include "Commands/WaitCommand.h"
#include "Commands/FireBallCommandGroup.h"
#include "Commands/TurnOnShooterCommand.h"
#include "Commands/TurnOffShooterCommand.h"
#include "WPILib.h"

class GeneratedAutoBatterShotsCommandGroup: public CommandGroup
{
public:
	GeneratedAutoBatterShotsCommandGroup(Command* traverseCommand, int position) : CommandGroup("GeneratedAutoBatterShotsCommandGroup") {
		double angleArray[4] = {55.9, 28, 333.5, 309.9};
		double distanceArray[4] = {65809, 14252, 11085, 22697};
		if (traverseCommand){
			AddSequential(new ToggleShooterPositionCommand());
			AddSequential(new AutoBlockOneCommandGroup());
			AddSequential(traverseCommand);
			AddSequential(new RotateToAngleCommand(angleArray[position - 2]));
			AddSequential(new WaitCommand(.25));
			AddSequential(new DriveDistanceCommand(.7,.7,distanceArray[position - 2]));
			AddSequential(new WaitCommand(.25));
			AddSequential(new RotateToAngleCommand(0));
			AddParallel(new AutoDriveCommand(.5,.5));
			AddSequential(new DriveUntilBatterCommand());
			AddSequential(new FireBallCommandGroup());
			AddSequential(new TurnOffShooterCommand());
			AddParallel(new AutoDriveCommand(-.5,-.5,.5));
			AddSequential(new ToggleShooterPositionCommand());
		}

	}
};

#endif
