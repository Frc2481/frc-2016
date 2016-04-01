#ifndef Instrumentation__h_
#define Instrumentation__h_

#include <iomanip> // using setw() for printing
#include "WPILib.h" // CANTalon

class instrumentation {
public:
	static void OnNoProgress()
	{
		std::cout << "NOPROGRESS\n";
	}
	static void OnUnderrun()
	{
		std::cout << "UNDERRUN\n";
	}
	static const char * StrOutputEnable(unsigned int value)
	{
		static const char table[][6] = {" Dis "," En  ","Hold ","Inval"};
		if(value > 3)
			value = 3;
		return table[value];
	}
	/**
	 * Prints and/or logging to watch the MP signals
	 */
	static void Process(CANTalon::MotionProfileStatus & status)
	{
		static double timeout = 0;
		static int count = 0;

		const char delim[] = "\t";
		const char endline[] = "\n";

		double now = GetTime();

		if((now-timeout) > 0.2){
			timeout = now;
			/* fire a loop every 200ms */

			if(--count <= 0){
				count = 8;
				/* every 8 loops, print our columns */
				std::cout
							<< "outputEnable" << delim
							<< "topBufferRem" << delim
							<< "topBufferCnt" << delim
							<< "btmBufferCnt" << delim
							<< "     IsValid" << delim
							<< " HasUnderrun" << delim
							<< "  IsUnderrun" << delim
							<< "      IsLast" << delim
							<< "     VelOnly" << delim
							<< "     targPos" << delim
							<< "     targVel" << delim
							<< " profSlotSel" << delim
							<< "   timeDurMs" << delim

							<< endline;
			}
			/* every loop, print our values */
			std::cout
						<< std::setw(12)<< StrOutputEnable(status.outputEnable) << delim
						<< std::setw(12)<< status.topBufferRem << delim
						<< std::setw(12)<< status.topBufferCnt << delim
						<< std::setw(12)<< status.btmBufferCnt << delim
						<< std::setw(12)<< (status.activePointValid ? "1" : "") << delim
						<< std::setw(12)<< (status.hasUnderrun ? "1" : "") << delim
						<< std::setw(12)<< (status.isUnderrun ? "1" : "") << delim
						<< std::setw(12)<< (status.activePoint.isLastPoint ? "1" : "") << delim
						<< std::setw(12)<< (status.activePoint.velocityOnly ? "1" : "") << delim
						<< std::setw(12)<< status.activePoint.position << delim
						<< std::setw(12)<< status.activePoint.velocity << delim
						<< std::setw(12)<< status.activePoint.profileSlotSelect << delim
						<< std::setw(12)<< status.activePoint.timeDurMs << delim

						<< endline;
		}
	}
};
#endif // Instrumentation__h_
