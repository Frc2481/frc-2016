#ifndef TraverseTerrainCommandGroup_H
#define TraverseTerrainCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/AutoDriveCommand.h"
#include "WPILib.h"

class TraverseTerrainCommandGroup: public CommandGroup
{
public:
	TraverseTerrainCommandGroup() : CommandGroup("TraverseTerrainCommandGroup"){
		AddSequential(new AutoDriveCommand(.7,.7,3));
	}
};

#endif
