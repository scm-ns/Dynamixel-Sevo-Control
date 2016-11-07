/* 
 * To COMPILE >> 
 * 	g++-5 dyna_ros.cpp -lserial -pthread -std=c++11
 */

#ifndef DYNA_SERIAL_H
#define DYNA_SERIAL_H

#include <string>
#include <iostream>
#include <memory>
#include <iomanip>
#include <cstdio>
#include <unistd.h>
#include <SerialStream.h>

class dynaSerial
{
	private:
		std::unique_ptr<LibSerial::SerialStream> _stream;
		std::string _portName ;		
		int _magic_no_ax_write ; 
		int _magic_no_ax_read ;
		int _reg_no_write;
		int _reg_no_read;
	public: 
		dynaSerial(std::string portName);
		bool isOpen() const ;
		// drive servo with id to positioin of value 
		void driveServo(int id , int value);

//		int readServoPos(int id );

};

#endif
