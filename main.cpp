#include "dynaSerial.h"
#include <string>
#include <thread>
#include <iostream>

static const std::string  PORT = "/dev/ttyUSB0";
static const int numServos = 3 * 4;
static const int arrServoID[numServos] = { 16 , 14 ,12 , 1 , 17 , 9 , 11 , 2 , 6 , 13 , 3 , 7};
static const int arrServoVal[numServos / 3] = { 500 , 500 ,800};


int main()
{
	// the controller is at port

	dynaSerial serialCon(PORT);		

	// Go throu each of the servos and make them all point to a single number
	int val = 400 ; 
	int sign = 1; 

	while(1)
	{
		for(int i = 0 ; i < numServos ; ++i)
		{
			std::cout << "Send value : " << val << " to servo : " << arrServoID[i] << std::endl;
			serialCon.driveServo(arrServoID[i] , arrServoVal[i% 3]);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		//val += 20 * sign ; 

		if(val > 600) sign = -1 ;
	
		if(val < 400 ) sign = 1 ; 
	}
		
}


