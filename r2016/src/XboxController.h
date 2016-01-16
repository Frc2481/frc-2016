/*
 * XboxController.h
 *
 *  Created on: Jan 22, 2013
 *      Author: Team2481
 */

#ifndef XBOXCONTROLLER_H_
#define XBOXCONTROLLER_H_

#include "WPILib.h"



class XboxController: public Joystick {
public:
	static const uint32_t xbLeftXAxis;
	static const uint32_t xbLeftYAxis;
	static const uint32_t xbLeftTrigger;
	static const uint32_t xbRightTrigger;
	static const uint32_t xbRightXAxis;
	static const uint32_t xbRightYAxis;
	static const uint32_t xbAButton;
	static const uint32_t xbBButton;
	static const uint32_t xbXButton;
	static const uint32_t xbYButton;
	static const uint32_t xbStartButton;
	static const uint32_t xbBackButton;
	static const uint32_t xbRightBumper;
	static const uint32_t xbLeftBumper;
	static const uint32_t xbRightStickCLick;
	static const uint32_t xbLeftStickClick;
	static const uint32_t xbDPadTop;
	static const uint32_t xbDPadRight;
	static const uint32_t xbDPadBottom;
	static const uint32_t xbDPadLeft;
	
	XboxController(uint32_t port);
	virtual ~XboxController();
	
};

#endif /* XBOXCONTROLLER_H_ */
