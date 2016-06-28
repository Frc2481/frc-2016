#ifndef UnClogCommandGroup_H
#define UnClogCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/TurnOffShooterCommand.h"
#include "Commands/TurnOnShooterCommand.h"
#include "Commands/TurnOnShooterRevCommand.h"
#include "Commands/WaitCommand.h"
#include "Commands/ShooterUpCommand.h"
#include "WPILib.h"

class UnClogCommandGroup: public CommandGroup
{
public:
	UnClogCommandGroup() : CommandGroup("UnClogCommandGroup"){
		AddSequential(new ShooterUpCommand());
		AddSequential(new TurnOnShooterCommand());
		AddSequential(new WaitCommand(.2));
		AddSequential(new TurnOffShooterCommand());
		AddSequential(new WaitCommand(.5));
		AddSequential(new TurnOnShooterRevCommand());
	}
};

#endif
