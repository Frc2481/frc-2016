/*
 * RoboPreferences.h
 *
 *  Created on: Jan 23, 2016
 *      Author: Paul
 */

#ifndef SRC_ROBOPREFERENCES_H_
#define SRC_ROBOPREFERENCES_H_

#include <string>

class RoboPreferences {
protected:
	RoboPreferences();
	virtual ~RoboPreferences();
public:
	static RoboPreferences *GetInstance();
	bool GetBool(const std::string& key, bool defaultVal = false);
	double GetDouble(const std::string& key, double defaultVal = 0);
	void SetBool(const std::string& key, bool val);
	void SetDouble(const std::string& key, double val);
};

#endif /* SRC_ROBOPREFERENCES_H_ */
