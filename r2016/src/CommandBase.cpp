#include "CommandBase.h"
#include "Commands/Scheduler.h"

// Initialize a single static instance of all of your subsystems to NULL
std::unique_ptr<CameraProcessor> CommandBase::mCameraProcessor;
std::unique_ptr<DriveTrain> CommandBase::driveTrain;
std::unique_ptr<Intake> CommandBase::intake;
std::unique_ptr<Shooter> CommandBase::shooter;
std::unique_ptr<OI> CommandBase::oi;

CommandBase::CommandBase(char const *name) :
		Command(name)
{
}

CommandBase::CommandBase() :
		Command()
{

}

void CommandBase::init()
{
	// Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	mCameraProcessor.reset(new CameraProcessor());
	driveTrain.reset(new DriveTrain());
	intake.reset(new Intake());
	shooter.reset(new Shooter());
	oi.reset(new OI());
}
