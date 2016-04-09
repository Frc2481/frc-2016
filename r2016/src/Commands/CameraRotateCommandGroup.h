#ifndef CameraRotateCommandGroup_H
#define CameraRotateCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/LockOnTargetCommand.h"
#include "Commands/WaitForCameraSteadyCommand.h"
#include "Commands/ShooterUpCommand.h"
#include "WPILib.h"

class CameraRotateCommandGroup: public CommandGroup
{
public:
	CameraRotateCommandGroup(CameraProcessor::target_type_t target){
			AddSequential(new ShooterUpCommand());
			AddSequential(new LockOnTargetCommand(target));
			AddSequential(new WaitForCameraSteadyCommand());
			AddSequential(new RotateToAngleFromCameraCommand());
	}
};

#endif
