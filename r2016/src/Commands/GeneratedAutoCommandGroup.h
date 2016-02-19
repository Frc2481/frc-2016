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
#include "Commands/ZeroGyroCommand.h"
#include "Commands/ShooterOnTargetCommand.h"
#include "WPILib.h"

class GeneratedAutoCommandGroup: public CommandGroup
{
public:
	GeneratedAutoCommandGroup(Command* traverseCommand, int position)
		: CommandGroup("GeneratedAutoCommandGroup"){
		double angleArray[6] = {0, 0, 30, 0, -5, -30};
		if (traverseCommand){
			AddSequential(new ZeroGyroCommand());
			AddParallel(new TurnLightRingOnCommand());
			AddParallel(new TurnOnShooterCommand());
			AddSequential(new DriveDistanceCommand(13100));
//			AddSequential(new AutoDriveCommand(.5,.5,1));
			AddSequential(traverseCommand);
			AddSequential(new RotateToAngleCommand(angleArray[position]));    //disabling for middle pos
			//AddSequential(new WaitCommand(1));
			AddSequential(new RotateToAngleFromCameraCommand());
			AddSequential(new ShooterOnTargetCommand());
			AddSequential(new FireBallCommandGroup());
			AddSequential(new TurnOffShooterCommand());
			AddSequential(new RotateToAngleCommand(180));
//			AddSequential(new Auto180TurnCommandGroup());
//			AddSequential(new WaitCommand(.2));
			AddSequential(new DriveDistanceCommand(1000));
			AddSequential(traverseCommand);
			AddSequential(new IntakeBallCommandGroup());
			AddSequential(new AutoDriveCommand(.3,.3));
			AddSequential(new WaitForBallCommand());
//			AddSequential(new RotateToAngleCommand(180));
//			AddSequential(new RotateFPSCommand(position));
//			AddSequential(new AcquireBallCommandGroup());
//			AddSequential(new WaitCommand(.25));
////			AddSequential(new DriveDistanceCommand(-500));
//			AddSequential(new AutoDriveCommand(-.5,-.5,1));
//			AddSequential(new RotateToAngleCommand(0));
//			AddSequential(new RotateFPSCommand(position));
//			AddSequential(new RotateToAngleCommand(0));
//			AddSequential(new AutoDriveCommand(0,0,.11));
		}
	}
};

#endif
