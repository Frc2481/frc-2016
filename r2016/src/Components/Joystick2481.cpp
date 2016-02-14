/*
 * Joystick2481.cpp
 *
 *  Created on: Jan 21, 2013
 *      Author: Team2481
 */

#include "Joystick2481.h"
#include <math.h>

Joystick2481::Joystick2481(int port) : Joystick(port) {
	s = 0.375;
	m = 1.340508;
	t = 0.381021;
	b = -0.340508;
}

Joystick2481::~Joystick2481() {
	// TODO Auto-generated destructor stub
}

float Joystick2481::GetRawAxis(int axis, bool boost) {
	float x = Joystick::GetRawAxis(axis);
	float scale = boost ? 1.0f:0.5f;

    if (x < -t){
        return scale * (m * x - b);
    }
    if (x > -t && x < t){
        return scale * (1 / (pow(s,2.0)) * pow(x,3.0));
    }
    else{
        return scale * (m * x + b);
    }
	
}
