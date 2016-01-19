/*
 * RoboUtils.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: FIRSTMentor
 */

#include <RoboUtils.h>

RoboUtils::RoboUtils() {
	// TODO Auto-generated constructor stub

}

RoboUtils::~RoboUtils() {
	// TODO Auto-generated destructor stub
}

double RoboUtils::constrainDeg0To360(double deg) {
	while (deg > 360) {
		deg -= 360;
	}
	while (deg < 0) {
		deg += 360;
	}
	return deg;
}

double RoboUtils::constrainDegNeg180To180(double deg) {
	return constrainDeg0To360(deg + 180) - 180;
}

