/*
 * SubsytemBase.cpp
 *
 *  Created on: Jan 22, 2016
 *      Author: Eli Willett
 */

#include <SubsystemBase.h>

SubsystemBase::SubsystemBase(const std::string &name)
	: Subsystem(name), Command(name){
	this->SetRunWhenDisabled(true);
	this->Start();
}

SubsystemBase::~SubsystemBase() {
}

void SubsystemBase::Execute() {
	Periodic();
}

bool SubsystemBase::IsFinished() {
	return false;
}
