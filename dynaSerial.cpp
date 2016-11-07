
#include "dynaSerial.h"

dynaSerial::dynaSerial(std::string portName) : _stream(new LibSerial::SerialStream) , _portName(portName)
{
	// Set the values after opening the port . Otherwise 
	// it takes up default values and we cannot communicate using them.. 
	_stream->Open(_portName ,  std::ios::out | std::ios::in );
	_stream->SetBaudRate(LibSerial::SerialStreamBuf::BAUD_115200);	
	_stream->SetNumOfStopBits(1);
	_stream->SetCharSize(LibSerial::SerialStreamBuf::CHAR_SIZE_8);
	_stream->SetParity(LibSerial::SerialStreamBuf::PARITY_NONE);

	
	// give value to magic number
	_magic_no_ax_write = 3; 
	_magic_no_ax_read = 4 ; 
	_reg_no_read = 43 ; 
	_reg_no_write = 30 ;
}

/* 
 * ID will be a single byte while value will be two bytes 
 *
 */
void dynaSerial::driveServo(int id , int value)
{
	std::cout << " PORT OPEN " << isOpen() << std::endl;
	std::string sendStr;
	// Initial two bytes
	sendStr+=((char)0xFF) ; sendStr += ( (char)0xFF);

	// id 
	sendStr+=((char)id);
	// remaining bytes to be send 
	sendStr += (char)5;
	
	// value to send to ax for writing 
	sendStr += ((char) _magic_no_ax_write);	
	sendStr += (char)_reg_no_write ; 

	*_stream.get() << sendStr ;

	//write the high byte
	char highByteServoPos = (value % 256);
	char lowByteServoPos = (value >> 8);

	*_stream.get() << highByteServoPos ; 
	*_stream.get() << lowByteServoPos ; 

	char checkSum = 255 - ((id + 5 + _magic_no_ax_write + _reg_no_write + (int)highByteServoPos + (int)lowByteServoPos ) % 256 ) ;

	*_stream.get() << checkSum ; 

	std::cout << " SEND SIGNAL :"  << sendStr << std::endl;
}



/*
int dynaSerial::readServoPos(int id )
{
	_stream->flush();
	
	return id;
}
*/

bool dynaSerial::isOpen() const
{
	return _stream->IsOpen();	
}

/*

int main(int argc , char ** argv)
{
	std::string port("/dev/ttyUSB0");

	dynaSerial serial(port);
	std::cout << serial.isOpen()<< std::endl;
	for( int i = 0 ; i < 8 ; i++)
	{
			
		serial.driveServo(i,500);
	}


};

*/
