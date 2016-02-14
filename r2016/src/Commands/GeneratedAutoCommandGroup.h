#ifndef GeneratedAutoCommandGroup_H
#define GeneratedAutoCommandGroup_H

#include "Commands/BringIntakeUpCommandGroup.h"
#include "Commands/AcquireBallCommandGroup.h"
#include "Commands/FireBallCommandGroup.h"
#include "Commands/CommandGroup.h"
#include "Commands/RotateFPSCommand.h"
#include "Commands/RotateToAngleCommand.h"
#include "Commands/AutoDriveCommand.h"
#include "Commands/TurnOffShooterCommand.h"
#include "Commands/TurnOnShooterCommand.h"
#include "Commands/WaitCommand.h"
#include "Commands/Auto180TurnCommandGroup.h"
#include "Commands/DriveDistanceCommand.h"
#include "WPILib.h"

class GeneratedAutoCommandGroup: public CommandGroup
{
public:
	GeneratedAutoCommandGroup(Command* traverseCommand, int position)
		: CommandGroup("GeneratedAutoCommandGroup"){
		if (traverseCommand){
			AddSequential(new DriveDistanceCommand(500));
			AddSequential(traverseCommand);
			AddParallel(new RotateToAngleCommand(0));
			AddSequential(new TurnOnShooterCommand());
			AddSequential(new RotateToAngleFromCameraCommand());
			AddSequential(new WaitCommand(.25));
			AddSequential(new FireBallCommandGroup());
			AddSequential(new Auto180TurnCommandGroup());
			AddSequential(new WaitCommand(.2));
			AddSequential(traverseCommand);
			AddSequential(new RotateToAngleCommand(180));
			AddSequential(new RotateFPSCommand(position));
			AddParallel(new AcquireBallCommandGroup());
			AddSequential(new DriveDistanceCommand(500));
			AddSequential(new WaitCommand(.25));
			AddSequential(new DriveDistanceCommand(-500));
			AddSequential(new RotateToAngleCommand(0));
			AddSequential(new RotateFPSCommand(position));
			AddSequential(new RotateToAngleCommand(0));
			AddSequential(new AutoDriveCommand(0,0));
		}
	}
};

#endif
