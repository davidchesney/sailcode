#include <string.h>
#include <stdlib.h>

#include "logging.h"
#include "arduinoCom.h"
//#include "gaelforce.h"
//#include "environment.h"


int main(int argc, char* argv[]) {
	//Simple data logging test.
	double lat, lon;
	double heading, var, dev;
	double windSpeed, windDirection;
	double courseOverGround, speedOverGround;
	std::string resp;
	int stat=0;
	int pin= 2;
	char* buf;
	Logging::init();
	ArduinoCom ard("/dev/ttyACM0",pin);
	Logging::addDataSource(DOUBLE, "lat", &lat);
	Logging::addDataSource(DOUBLE, "lon", &lon);
	Logging::addDataSource(DOUBLE, "heading", &heading);
	Logging::addDataSource(DOUBLE, "var", &var);
	Logging::addDataSource(DOUBLE, "dev", &dev);
	Logging::addDataSource(DOUBLE, "windSpeed", &windSpeed);
	Logging::addDataSource(DOUBLE, "windDirection", &windDirection);
	Logging::addDataSource(DOUBLE, "courseOG", &courseOverGround);
	Logging::addDataSource(DOUBLE, "speedOG", &speedOverGround);
	
	while(true) {
		stat = ard.requestVariables("airmar","lat lon", resp);
		if(stat==0){ 
			//need to parse the variables string into the appropriate slots.
			buf = new char[resp.length()];
			strcpy(buf, resp.c_str());
			lat = atof(strtok(buf, ","));
			lon = atof(strtok(NULL, ","));

			delete[] buf;
		}
		stat = ard.requestVariables("airmar", "heading var dev", resp);
		if(stat==0) {
			buf = new char[resp.length()];
			strcpy(buf, resp.c_str());

			heading = atof(strtok(buf, ","));
			var = atof(strtok(NULL, ","));
			dev = atof(strtok(NULL, ","));

			delete[] buf;
		}
		stat = ard.requestVariables("airmar", "windSpeed windDirection courseOverGround speedOverGround", resp);
		if(stat==0) {
			buf = new char[resp.length()];
			strcpy(buf, resp.c_str());
			windSpeed = atof(strtok(buf, ","));
			windDirection = atof(strtok(NULL, ","));
			courseOverGround = atof(strtok(NULL, ","));
			speedOverGround = atof(strtok(NULL, ","));

			delete[] buf;
		}
		Logging::log();

		usleep(1000*5000);
	}
}


