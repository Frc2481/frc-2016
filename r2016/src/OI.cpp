/*
  * OI.cpp
 *
 *  Created on: Jan 16, 2016
 *      Author: Team2481
 */

#include "Commands/AcquireBallCommandGroup.h"
#include "Commands/ToggleShooterPositionCommand.h"
#include "Commands/TurnIntakeOnRevCommand.h"
#include <OI.h>
#include <ControllerMap.h>
#include "Commands/FireBallCommandGroup.h"
#include "Commands/WaitForBallTestCommandGroup.h"
#include "Commands/TurnOnShooterCommand.h"
#include "Commands/TurnOffShooterCommand.h"
#include "Commands/RotateToAngleCommand.h"
#include "Commands/ShiftDriveTrainCommand.h"
#include "Commands/ToggleIntakeCommand.h"
#include "Commands/TraversePortcullisCommandGroup.h"
#include "Commands/UnClogCommandGroup.h"
#include "Commands/StopDriveCommand.h"
#include "Commands/DecrementCameraOffsetCommand.h"
#include "Commands/DecrementShooterSpeedCommand.h"
#include "Commands/IncShooterSpeedCommand.h"
#include "Commands/IncrementCameraOffsetCommand.h"
#include "Commands/CameraRotateCommandGroup.h"

OI::OI() {
	driveStick = new Joystick2481(0);
	operatorStick = new Joystick2481(1);
	debugStick = new Joystick(2);

	intakeButton = new INTAKE_BUTTON;
	intakeButton->WhenPressed(new IntakeBallCommandGroup());
	intakeButton->WhenReleased(new BringIntakeUpCommandGroup());

	turnOnShooter = new TURN_SHOOTER_ON_BUTTON;
	turnOnShooter->WhenPressed(new TurnOnShooterCommand());

	turnOffShooter = new TURN_SHOOTER_OFF_BUTTON;
	turnOffShooter->WhenPressed(new TurnOffShooterCommand());

	manualIntakeButton = new TOGGLE_INTAKE_BUTTON;
	manualIntakeButton->WhenPressed(new ToggleIntakeCommand());

	intakeRevButton = new INTAKE_REVERSE_BUTTON;
	intakeRevButton->WhenPressed(new TurnIntakeOnRevCommand());
	intakeRevButton->WhenReleased(new StopIntakeCommand());

	rotateToRightAngleCam = new LOCK_ON_TARGET_RIGHT_BUTTON;
	rotateToRightAngleCam->WhenPressed(new CameraRotateCommandGroup(CameraProcessor::RIGHT_TARGET));

	rotateToLeftAngleCam = new LOCK_ON_TARGET_LEFT_BUTTON;
	rotateToLeftAngleCam->WhenPressed(new CameraRotateCommandGroup(CameraProcessor::LEFT_TARGET));

	driveTrainShift = new DRIVE_TRAIN_SHIFT_BUTTON;
	driveTrainShift->WhenPressed(new ShiftDriveTrainCommand(true));
	driveTrainShift->WhenReleased(new ShiftDriveTrainCommand(false));


	rotateToAngleNoCam = new NO_CAMERA_ROTATE_BUTTON;
	rotateToAngleNoCam->WhileHeld(new RotateToAngleCommand(90));

	fireBall = new FIRE_BALL_BUTTON;
	fireBall->WhenPressed(new FireBallCommandGroup(true));

	changeShooterAngle = new TOGGLE_SHOOTER_ANGLE_BUTTON;
	changeShooterAngle->WhenPressed(new ToggleShooterPositionCommand());

	waitForBallTest = new TEST_INTAKE_WAIT_BUTTON;
	waitForBallTest->WhenPressed(new WaitForBallTestCommandGroup());

//	portcullisTraverse = new PORTCULLIS_BUTTON;
//	portcullisTraverse->WhenPressed(new TraversePortcullisCommandGroup());

	shooterRevButton = new REVERSE_SHOOTER_BUTTON;
	shooterRevButton->WhenPressed(new UnClogCommandGroup());

	stopSpinButton = new STOP_SPIN_BUTTON;
	stopSpinButton->WhenPressed(new StopDriveCommand());

	shooterIncButton = new SHOOTER_INC_BUTTON;
	shooterIncButton->WhenPressed(new IncShooterSpeedCommand());

	shooterDecButton = new SHOOTER_DEC_BUTTON;
	shooterDecButton->WhenPressed(new DecrementShooterSpeedCommand());

	cameraIncButton = new CAMERA_INC_BUTTON;
	cameraIncButton->WhenPressed(new IncrementCameraOffsetCommand());

	cameraDecButton = new CAMERA_DEC_BUTTON;
	cameraDecButton->WhenPressed(new DecrementCameraOffsetCommand());

	operatorRevIntake = new OPERATOR_REV_INTAKE_BUTTON;
	operatorRevIntake->WhenPressed(new TurnIntakeOnRevCommand());
	operatorRevIntake->WhenReleased(new StopIntakeCommand());
}

OI::~OI() {
	// TODO Auto-generated destructor stub
}

Joystick2481* OI::GetDriveStick() {
	return driveStick;
}

Joystick2481* OI::GetOperatorStick() {
	return operatorStick;
}

Joystick* OI::GetDebugStick() {
	return debugStick;
}
