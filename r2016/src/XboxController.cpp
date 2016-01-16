/*
 * XboxController.cpp
 *
 *  Created on: Jan 22, 2013
 *      Author: Team2481
 */

#include "XboxController.h"

const uint32_t XboxController::xbLeftXAxis = 0;
const uint32_t XboxController::xbLeftYAxis = 1;
const uint32_t XboxController::xbLeftTrigger = 2;
const uint32_t XboxController::xbRightTrigger = 3;
const uint32_t XboxController::xbRightXAxis = 4;
const uint32_t XboxController::xbRightYAxis = 5;
const uint32_t XboxController::xbAButton = 1;
const uint32_t XboxController::xbBButton = 2;
const uint32_t XboxController::xbXButton = 3;
const uint32_t XboxController::xbYButton = 4;
const uint32_t XboxController::xbStartButton = 8;
const uint32_t XboxController::xbBackButton = 7;
const uint32_t XboxController::xbRightBumper = 6;
const uint32_t XboxController::xbLeftBumper = 5;
const uint32_t XboxController::xbRightStickCLick = 10;
const uint32_t XboxController::xbLeftStickClick = 9;
const uint32_t XboxController::xbDPadTop = 0;
const uint32_t XboxController::xbDPadRight = 90;
const uint32_t XboxController::xbDPadBottom = 180;
const uint32_t XboxController::xbDPadLeft = 270;


XboxController::XboxController(uint32_t port) : Joystick(port){}

XboxController::~XboxController() {}
