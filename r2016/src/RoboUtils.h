/*
 * RoboUtils.h
 *
 *  Created on: Jan 18, 2016
 *      Author: FIRSTMentor
 */

#ifndef SRC_ROBOUTILS_H_
#define SRC_ROBOUTILS_H_
#include <algorithm>

class RoboUtils {
public:
	RoboUtils();
	virtual ~RoboUtils();
	static double constrainDeg0To360(double deg);
	static double constrainDegNeg180To180(double deg);
	template < typename T >
	static T constrain(T val, T minVal, T maxVal) {
		return std::min(std::max(val, minVal),maxVal);
	}
};

#endif /* SRC_ROBOUTILS_H_ */
