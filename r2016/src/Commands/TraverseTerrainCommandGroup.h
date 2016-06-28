#ifndef TraverseTerrainCommandGroup_H
#define TraverseTerrainCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/AutoDriveCommand.h"
#include "WPILib.h"

class TraverseTerrainCommandGroup: public CommandGroup
{
public:
	TraverseTerrainCommandGroup() : CommandGroup("TraverseTerrainCommandGroup"){
		AddSequential(new AutoDriveCommand(1,1,1.55));
	}
};

#endif
