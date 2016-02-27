/*
 * CameraProcessor.h
 *
 *  Created on: Jan 16, 2016
 *      Author: FIRSTMentor
 */

#ifndef SRC_SUBSYSTEMS_CAMERAPROCESSOR_H_
#define SRC_SUBSYSTEMS_CAMERAPROCESSOR_H_
#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"
#include <SubsystemBase.h>

class CameraProcessor: public SubsystemBase {
private:
	Servo* m_cameraServo;
	double m_servoAngle;
	const int k_resX = 320;
	const int k_resY = 240;
	const int k_FOV = 37.4;
	const int k_tWidthIn = 20;
	const int k_tHeightIn = 12;
	const double k_CameraOffsetIn = 11.0;
	bool m_targetVisible;
	double m_angle;
	std::shared_ptr<NetworkTable> m_table;
	Solenoid* m_cameraLight;
public:

	CameraProcessor();
	virtual ~CameraProcessor();
	bool isTargetAvailable();
	double getAngle();
	void calculate();
	void SetLight(bool state);
	void Periodic();
	void SetServoPosition(double angle);
	double GetServoPosition();
};

#endif /* SRC_SUBSYSTEMS_CAMERAPROCESSOR_H_ */
