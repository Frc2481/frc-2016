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
public:

	class Target {
	public:
		static const int k_pixelTolerance = 2;
		double width;
		double height;
		double area;
		double x;
		double y;
		double distance;
		double angle;
		bool operator==(const Target& other) {
			if (fabs(x - other.x) < k_pixelTolerance &&
					fabs(y - other.y) < k_pixelTolerance) {
				return true;
			}
			return false;
		}
	};

	enum target_type_t{
		LEFT_TARGET = 0,
		RIGHT_TARGET,
		AUTO_TARGET,
		TARGET_TYPE_SIZE
	};

private:
	const int k_resX = 320;
	const int k_resY = 240;
	const int k_FOV = 37.4;
	const int k_tWidthIn = 20;
	const int k_tHeightIn = 12;
	const double k_xOffset = -11.0;
	const double k_yOffset = -8.5;
	const double k_sizeTolerance = 0.3;
	double m_OffsetAngle = 1.5;
	bool m_targetVisible;
	bool m_onTarget;
	Target m_targets[TARGET_TYPE_SIZE];
	Target m_prevTargets[TARGET_TYPE_SIZE];
	int m_steadyCount;

	int m_prevOwlCounter;
	int m_owlMissingCounter;
	int m_robotCounter;
	double m_shotRange = 190;
	std::shared_ptr<NetworkTable> m_table;
	Solenoid* m_cameraLight;
	target_type_t m_activeTarget;

public:
	CameraProcessor();
	virtual ~CameraProcessor();
	bool isTargetAvailable();
	bool isOnTarget();
	double getAngle();
	void incOffsetAngle();
	void decOffSetAngle();
	void calculate();
	void calculateDistanceAndAngleOfTarget(Target& target);
	void SetLight(bool state);
	void Periodic();
	void lockOnTarget(target_type_t target);
	void calculateSteadyCount();
	bool isCameraSteady();
};

#endif /* SRC_SUBSYSTEMS_CAMERAPROCESSOR_H_ */
