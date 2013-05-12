
#include <iostream>

#include "log.h"

int main(int argc, char* argv[])
{
	Logger log;

	//set log file
	//log.set_file("c.log");

	//set log level
	log.set_level(0);

	log.info()<<"info"<<std::endl;
	
	log.warning()<<"warning"<<std::endl;

	log.error()<<"error"<<std::endl;

	log.fatal()<<"fatal"<<std::endl;
	
	return 0;
}
