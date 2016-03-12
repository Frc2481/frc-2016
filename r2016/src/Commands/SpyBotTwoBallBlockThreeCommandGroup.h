#ifndef SpyBotTwoBallBlockThreeCommandGroup_H
#define SpyBotTwoBallBlockThreeCommandGroup_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"

class SpyBotTwoBallBlockThreeCommandGroup: public CommandGroup
{
public:
	SpyBotTwoBallBlockThreeCommandGroup(){
		AddParallel(new AutoDriveCommand(0,0,0));
	}
};

#endif
