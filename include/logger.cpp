#include "logger.h"
#include <iostream>
#include <fstream>
#include <ctime> 
#include <cstring>

using namespace std;


char *Logger::timestamp(){
	char *timestamp = (char*) calloc(1, sizeof(tm));
	time_t t = time(0);
	tm* now = localtime(&t);

	sprintf(timestamp, "%d-%d-%d %d:%d:%d", now->tm_mday, now->tm_mon + 1, now->tm_year + 1900, now->tm_hour, now->tm_min, now->tm_sec);
        
	return timestamp;

}

inline string getLabel(typelog type) {
    string label;
    switch(type) {
        case DEBUG: label = "DEBUG"; break;
        case INFO:  label = "INFO "; break;
        case WARN:  label = "WARN "; break;
        case ERROR: label = "ERROR"; break;
    }
    return label;

Logger::Logger(typelog type, const char message[]){
	msglevel = type;

	this->file.open(path, fstream::out | fstream::app);
}

Logger::~Logger() { /* O(1) */
    delete this;
    this->file.close();

}


void Logger::dump( const char message[]){
	if(this->file.is_open()){
		this->file << "[" << timestamp() << "]" << " " << "[" << type << "]" << " " << message << endl;
	}else{
		cout << "!PANIC the log file is not open" << endl;
		exit(0);
	}
}








