#ifndef GeneratedAutoCommandGroup_H
#define GeneratedAutoCommandGroup_H

#include "Commands/RotateToAngleCommand.h"
#include "Commands/AutoBlockOneCommandGroup.h"
#include "Commands/AutoBlockTwoCommandGroup.h"
#include "WPILib.h"

class GeneratedAutoCommandGroup: public CommandGroup
{
public:
	GeneratedAutoCommandGroup(Command* traverseCommand, int position)
		: CommandGroup("GeneratedAutoCommandGroup"){
		double angleArray[6] = {0, 0, 30, 0, 0, -25};
		if (traverseCommand){
			AddSequential(new AutoBlockOneCommandGroup());
			AddSequential(traverseCommand);
			AddSequential(new RotateToAngleCommand(angleArray[position]));    //disabling for middle pos
			AddSequential(new AutoBlockTwoCommandGroup());
		}
	}
};

#endif
