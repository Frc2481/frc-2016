#ifndef GeneratedAutoCommandGroup_H
#define GeneratedAutoCommandGroup_H

#include "Commands/RotateToAngleCommand.h"
#include "Commands/AutoBlockOneCommandGroup.h"
#include "Commands/AutoBlockTwoCommandGroup.h"
#include "Commands/RoughRotationCommand.h"
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
			AddSequential(new RotateToAngleCommand(angleArray[position]));    //disabling for middle pos
			AddSequential(new AutoBlockTwoCommandGroup());
			if (driveBack==1) {
				AddSequential(new DriveDistanceCommand(.5, .5, 1000));
				if (dynamic_cast<TraverseChevalFrieseCommandGroup*>(traverseCommand) != 0 ||
						dynamic_cast<TraverseRampartsCommandGroup*>(traverseCommand) != 0) {

					AddSequential(new Rotate180Command(.5));
				} else {
					AddSequential(new Rotate180Command());
				}
				AddSequential(new DriveDistanceCommand(.5, .5, 1000));
				AddSequential(traverseCommand);
			}


		}
	}
};

#endif
