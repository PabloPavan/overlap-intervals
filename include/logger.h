#ifndef LOGGER_H
#define	LOGGER_H

#include <fstream>
#include <ctime> 

using namespace std;

namespace logger{

    fstream file;
    char *timestamp();

    void start(const char path[]);
    void end();
    
  	void dump(const char type[], const char message[]);
}
#endif	/* LOGGER_H */