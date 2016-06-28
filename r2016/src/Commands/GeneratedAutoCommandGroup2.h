#ifndef GeneratedAutoCommandGroup2_H
#define GeneratedAutoCommandGroup2_H

#include "Commands/RotateToAngleCommand.h"
#include "Commands/AutoBlockOneCommandGroup.h"
#include "Commands/AutoBlockTwoCommandGroup.h"
#include "Commands/RoughRotationCommand.h"
#include "Commands/DriveUntilBatterCommand.h"
#include "Commands/LockOnTargetCommand.h"
#include "Commands/ShooterOnTargetCommand.h"
#include "Commands/FireBallCommandGroup.h"
#include "Commands/TurnOffShooterCommand.h"
#include "Commands/ZeroGyroCommand.h"
#include "Commands/TurnLightRingOnCommand.h"
#include "Commands/TurnOnShooterCommand.h"
#include "Commands/DriveDistanceCommand.h"
#include "Commands/TraverseChevalFrieseCommandGroup.h"
#include "Commands/ShiftDriveTrainCommand.h"
#include "Commands/WaitCommand.h"
#include "WaitForCameraSteadyCommand.h"
#include "WPILib.h"

class GeneratedAutoCommandGroup2: public CommandGroup
{
public:
	GeneratedAutoCommandGroup2(Command* traverseCommand, int position, int driveBack)
		: CommandGroup("GeneratedAutoCommandGroup2"){
		double angleArray[6] = {0, 0, 30, 0, 0, -25};
		if (traverseCommand){
			AddSequential(new ZeroGyroCommand());
			AddParallel(new TurnOnShooterCommand());
			AddParallel(new TurnLightRingOnCommand());
			AddSequential(new DriveDistanceCommand(.35,.35,1000));
			AddSequential(new ShiftDriveTrainCommand(true));
			AddSequential(new DriveDistanceCommand(1,1,7000));
			AddSequential(new ShiftDriveTrainCommand(false));
			AddSequential(new WaitCommand(.3));
			AddSequential(new AutoDriveCommand(.4, .4, .3));
			AddSequential(new AutoDriveCommand(1, 1, 1.5));
			if (position == 2 || position == 5) {
				AddSequential(new LockOnTargetCommand(CameraProcessor::LEFT_TARGET));
				if (position == 2){
					AddSequential(new DriveDistanceCommand(.6,.6,2000));
				}
			} else {
				AddSequential(new LockOnTargetCommand(CameraProcessor::RIGHT_TARGET));
			}

			AddSequential(new WaitCommand(.1));
			AddSequential(new RotateToAngleCommand(angleArray[position]));    //disabling for middle pos
			AddSequential(new WaitForCameraSteadyCommand());
			AddSequential(new RotateToAngleFromCameraCommand());
			AddSequential(new ShooterOnTargetCommand());
			AddSequential(new WaitCommand(.5));
			AddSequential(new FireBallCommandGroup());
	//		AddSequential(new FireBallCommandGroup());
			AddSequential(new TurnOffShooterCommand());
			AddSequential(new RotateToAngleCommand(0));
			if (position != 2) {
				AddSequential(new DriveDistanceCommand(.5, .5, 2000));
			}
			if (dynamic_cast<TraverseChevalFrieseCommandGroup*>(traverseCommand) != 0) {
				AddSequential(new Rotate180Command(.5));
			} else {
				AddSequential(new Rotate180Command());
			}
			if (driveBack==1) {
				AddSequential(new DriveDistanceCommand(.5, .5, 2000));
				AddSequential(traverseCommand);
			}
		}
	}
};

#endif
