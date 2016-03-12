/*
 * ControllerMap.h
 *
 *  Created on: Feb 8, 2016
 *      Author: FIRSTMentor
 */

#ifndef SRC_CONTROLLERMAP_H_
#define SRC_CONTROLLERMAP_H_
#include <OI.h>
#include "WPILib.h"
#include <XboxController.h>
#include "Components/AnalogJoystickButton.h"
#include "Components/POVJoystickButton.h"

//Drive Stick
#define INTAKE_BUTTON AnalogJoystickButton(driveStick, XboxController::xbRightTrigger, .5)
#define CAMERA_ROTATE_BUTTON JoystickButton(driveStick, XboxController::xbAButton)
#define DRIVE_TRAIN_SHIFT_BUTTON JoystickButton(driveStick, XboxController::xbLeftBumper)
#define INTAKE_REVERSE_BUTTON JoystickButton(driveStick, XboxController::xbBButton)
#define PORTCULLIS_BUTTON JoystickButton(driveStick, XboxController::xbXButton)
#define STOP_SPIN_BUTTON JoystickButton(driveStick, XboxController::xbBackButton)

//Operator Stick
#define TURN_SHOOTER_ON_BUTTON JoystickButton(operatorStick, XboxController::xbRightBumper)
#define TURN_SHOOTER_OFF_BUTTON JoystickButton(operatorStick, XboxController::xbLeftBumper)
#define FIRE_BALL_BUTTON AnalogJoystickButton(operatorStick, XboxController::xbRightTrigger, .5)
#define TOGGLE_INTAKE_BUTTON JoystickButton(operatorStick, XboxController::xbStartButton)
#define TOGGLE_SHOOTER_ANGLE_BUTTON JoystickButton(operatorStick, XboxController::xbBButton)
#define REVERSE_SHOOTER_BUTTON JoystickButton(operatorStick, XboxController::xbBackButton)
#define SHOOTER_INC_BUTTON POVJoystickButton(operatorStick, 0, XboxController::xbDPadTop)
#define SHOOTER_DEC_BUTTON POVJoystickButton(operatorStick, 0, XboxController::xbDPadBottom)
#define CAMERA_INC_BUTTON POVJoystickButton(operatorStick, 0, XboxController::xbDPadRight)
#define CAMERA_DEC_BUTTON POVJoystickButton(operatorStick, 0, XboxController::xbDPadLeft)

//Debug Stick
#define NO_CAMERA_ROTATE_BUTTON JoystickButton(debugStick, XboxController::xbBButton)
#define TEST_INTAKE_WAIT_BUTTON JoystickButton(debugStick, XboxController::xbAButton)

#endif /* SRC_CONTROLLERMAP_H_ */
