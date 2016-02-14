#ifndef TraverseMoatCommandGroup_H
#define TraverseMoatCommandGroup_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"

class TraverseMoatCommandGroup: public CommandGroup
{
public:
	TraverseMoatCommandGroup() : CommandGroup("TraverseMoatCommandGroup"){
		AddSequential(new AutoDriveCommand(.4, .4, .7));
	}
};

#endif
