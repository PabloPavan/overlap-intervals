#ifndef LOGGER_H
#define	LOGGER_H

#include <fstream>
#include <ctime> 

using namespace std;

enum typelog {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

struct structlog {
    cost char path[];
    typelog level = WARN;
};

extern structlog LOGCFG;

class Logger{

private:
    char *timestamp();
   
public:

	Logger(typelog type, const char message[]);
    ~Logger();

};
#endif	/* LOGGER_H */