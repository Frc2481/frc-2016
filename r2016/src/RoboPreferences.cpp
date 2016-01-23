/*
 * RoboPreferences.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: Paul
 */

#include <RoboPreferences.h>
#include "WPILib.h"

RoboPreferences::RoboPreferences() {

}

RoboPreferences::~RoboPreferences() {
	// TODO Auto-generated destructor stub
}

RoboPreferences* RoboPreferences::GetInstance() {
	static RoboPreferences instance;
	return &instance;
}

bool RoboPreferences::GetBool(const std::string& key, bool defaultVal) {
	return Preferences::GetInstance()->GetBoolean(key, defaultVal);
}

void RoboPreferences::SetBool(const std::string& key, bool val) {
	Preferences::GetInstance()->PutBoolean(key, val);
}

double RoboPreferences::GetDouble(const std::string& key, double defaultVal) {
	return Preferences::GetInstance()->GetDouble(key, defaultVal);
}

void RoboPreferences::SetDouble(const std::string& key, double val) {
	Preferences::GetInstance()->PutDouble(key, val);
}
