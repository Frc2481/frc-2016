#ifndef GeneratedAutoCommandGroup_H
#define GeneratedAutoCommandGroup_H

#include "Commands/RotateToAngleCommand.h"
#include "Commands/AutoBlockOneCommandGroup.h"
#include "Commands/AutoBlockTwoCommandGroup.h"
#include "Commands/RoughRotationCommand.h"
#include "Commands/DriveUntilBatterCommand.h"
#include "Commands/LockOnTargetCommand.h"
#include "WPILib.h"

class GeneratedAutoCommandGroup: public CommandGroup
{
public:
	GeneratedAutoCommandGroup(Command* traverseCommand, int position, int driveBack)
		: CommandGroup("GeneratedAutoCommandGroup"){
		double angleArray[6] = {0, 0, 30, 0, 0, -25};
		if (traverseCommand){
			AddSequential(new AutoBlockOneCommandGroup());
			AddSequential(traverseCommand);

//			AddSequential(new AutoDriveCommand(-.5,-.5));
//			AddSequential(new DriveUntilBatterCommand());
//			AddSequential(new AutoDriveCommand(.5,.5,.5));

			AddSequential(new RotateToAngleCommand(angleArray[position]));    //disabling for middle pos
			if (position == 2) {
				AddSequential(new LockOnTargetCommand(CameraProcessor::LEFT_TARGET));
			} else {
				AddSequential(new LockOnTargetCommand(CameraProcessor::RIGHT_TARGET));
			}
			AddSequential(new AutoBlockTwoCommandGroup());
			AddSequential(new RotateToAngleCommand(0));
			AddSequential(new DriveDistanceCommand(.5, .5, 2000));
			if (dynamic_cast<TraverseChevalFrieseCommandGroup*>(traverseCommand) != 0 ||
					dynamic_cast<TraverseRampartsCommandGroup*>(traverseCommand) != 0) {
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
