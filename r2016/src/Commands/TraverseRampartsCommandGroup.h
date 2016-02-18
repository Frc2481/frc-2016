#ifndef TraverseRampartsCommandGroup_H
#define TraverseRampartsCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/AutoDriveCommand.h"
#include "WPILib.h"

class TraverseRampartsCommandGroup: public CommandGroup
{
public:
	TraverseRampartsCommandGroup() : CommandGroup("TraverseRampartsCommandGroup"){
		AddSequential(new AutoDriveCommand(SmartDashboard::GetNumber("TraverseRamparts Forward Slow", .3),
				SmartDashboard::GetNumber("TraverseRamparts Forward Slow", .3),
				SmartDashboard::GetNumber("TraverseRamparts 1 Time", .75)));
		AddSequential(new AutoDriveCommand(SmartDashboard::GetNumber("TraverseRamparts Forward Fast", .5),
				SmartDashboard::GetNumber("TraverseRamparts Mid Rotate", .7),
				SmartDashboard::GetNumber("TraverseRamparts 2 Time", .5)));
		AddSequential(new AutoDriveCommand(SmartDashboard::GetNumber("TraverseRamparts Forward Fast", .5),
				SmartDashboard::GetNumber("TraverseRamparts Forward Fast", .5),
				SmartDashboard::GetNumber("TraverseRamparts 3 Time", 3)));
	}
};

#endif
