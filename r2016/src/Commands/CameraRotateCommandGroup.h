#ifndef CameraRotateCommandGroup_H
#define CameraRotateCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/LockOnTargetCommand.h"
#include "WPILib.h"

class CameraRotateCommandGroup: public CommandGroup
{
public:
	CameraRotateCommandGroup(CameraProcessor::target_type_t target){
			AddSequential(new LockOnTargetCommand(target));
			AddSequential(new RotateToAngleFromCameraCommand());
	}
};

#endif
