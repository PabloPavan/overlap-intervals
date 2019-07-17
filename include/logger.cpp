#include "logger.h"
#include <iostream>
#include <fstream>
#include <ctime> 
#include <cstring>

using namespace std;

namespace logger{

	char *timestamp(){
		char *timestamp = (char*) calloc(1, sizeof(tm));
		time_t t = time(0);
		tm* now = localtime(&t);

		sprintf(timestamp, "%d-%d-%d %d:%d:%d", now->tm_mday, now->tm_mon + 1, now->tm_year + 1900, now->tm_hour, now->tm_min, now->tm_sec);
	        
		return timestamp;

	}

	void start(const char path[]){
		file.open(path, fstream::out | fstream::app);
	}

	void end(){
		file.close();
	}


	void dump(const char type[], const char message[]){
		if(file.is_open()){
			file << "[" << timestamp() << "]" << " " << "[" << type << "]" << " " << message << endl;
		}else{
			cout << "!PANIC the log file is not open" << endl;
			exit(0);
		}
	}
}







