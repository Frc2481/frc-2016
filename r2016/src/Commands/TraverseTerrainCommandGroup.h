#ifndef TraverseTerrainCommandGroup_H
#define TraverseTerrainCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/AutoDriveCommand.h"
#include "WPILib.h"

class TraverseTerrainCommandGroup: public CommandGroup
{
public:
	TraverseTerrainCommandGroup() : CommandGroup("TraverseTerrainCommandGroup"){
		AddSequential(new AutoDriveCommand(.3, .3, .3));
		AddSequential(new AutoDriveCommand(.5, .5, .3));
		AddSequential(new AutoDriveCommand(.25, .25, .3));
	}
};

#endif
