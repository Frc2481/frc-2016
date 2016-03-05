#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <string>
#include "Commands/Command.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/Intake.h"
#include "OI.h"
#include "WPILib.h"
#include "Subsystems/CameraProcessor.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Kicker.h"

/**
 * The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use CommandBase.examplesubsystem
 */
class CommandBase: public Command
{
public:
	CommandBase(char const *name);
	CommandBase();
	static void init();

	static std::shared_ptr<NetworkTable> logTable;

	// Create a single static instance of all of your subsystems
	static std::unique_ptr<CameraProcessor> mCameraProcessor;
	static std::unique_ptr<DriveTrain> driveTrain;
	static std::unique_ptr<Intake> intake;
	static std::unique_ptr<Shooter> shooter;
	static std::unique_ptr<Kicker> kicker;
	static std::unique_ptr<OI> oi;
};

#endif
