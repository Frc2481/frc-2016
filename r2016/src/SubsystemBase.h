/*
 * SubsytemBase.h
 *
 *  Created on: Jan 22, 2016
 *      Author: Eli Willett
 */

#ifndef SRC_SUBSYSTEMBASE_H_
#define SRC_SUBSYSTEMBASE_H_

#include <Commands/Command.h>
#include <Commands/Subsystem.h>

class SubsystemBase : public Subsystem, public Command{
public:
	SubsystemBase(const std::string &name);
	virtual ~SubsystemBase();
	virtual void Periodic() = 0;
	void Initialize() {}
	void Execute();
	bool IsFinished();
	void End() {}
	void Interrupted() {}
};

#endif /* SRC_SUBSYSTEMBASE_H_ */
