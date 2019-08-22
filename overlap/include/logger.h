#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <sstream>
#include <string>
#include <stdio.h>

using namespace std;

inline string NowTime();

enum TLogLevel {lerror, lwarning, linfo, ldebug, ldebug1, ldebug2, ldebug3, ldebug4};

template <typename T>
class Log{
public:
	Log();
	virtual ~Log();
	ostringstream& Get(TLogLevel level = linfo);
public:
	static TLogLevel& ReportingLevel();
	static string ToString(TLogLevel level);
	static TLogLevel FromString(const string& level);
protected:
	ostringstream os;
private:
	Log(const Log&);
	Log& operator=(const Log&);
};

template <typename T>
Log<T>::Log(){
}

template <typename T>
ostringstream& Log<T>::Get(TLogLevel level){
	os << "[" << NowTime() << "]";
	os << " " << "[" << ToString(level) << "]";
	os << " " << string(level > ldebug ? level - ldebug : 0, '\t');
	return os;
}

template <typename T>
Log<T>::~Log(){
	os << endl;
	T::Output(os.str());
}

template <typename T>
TLogLevel& Log<T>::ReportingLevel(){
	static TLogLevel reportingLevel = ldebug4;
	return reportingLevel;
}

template <typename T>
string Log<T>::ToString(TLogLevel level){
	static const char* const buffer[] = {"ERROR", "WARNING", "INFO", "DEBUG", "DEBUG1", "DEBUG2", "DEBUG3", "DEBUG4"};
	return buffer[level];
}

template <typename T>
TLogLevel Log<T>::FromString(const string& level){
	if (level == "DEBUG4")
		return ldebug4;
	if (level == "DEBUG3")
		return ldebug3;
	if (level == "DEBUG2")
		return ldebug2;
	if (level == "DEBUG1")
		return ldebug1;
	if (level == "DEBUG")
		return ldebug;
	if (level == "INFO")
		return linfo;
	if (level == "WARNING")
		return lwarning;
	if (level == "ERROR")
		return lerror;
	Log<T>().Get(lwarning) << "Unknown logging level '" << level << "'. Using INFO level as default.";
	return linfo;
}

class Output2FILE{
public:
	static FILE*& Stream();
	static void Output(const string& msg);
	static void Dump(const string& msg);
};

inline FILE*& Output2FILE::Stream(){
	static FILE* pStream = stderr;
	return pStream;
}	

inline void Output2FILE::Output(const string& msg){   
	FILE* pStream = Stream();
	if (!pStream)
		return;
	fprintf(pStream, "%s", msg.c_str());
	fflush(pStream);
	#ifdef DUMP
		Dump(msg);
	#endif
}

inline void Output2FILE::Dump(const string& msg){   
	printf("%s", msg.c_str());
}

#define FILELOG_DECLSPEC  
class FILELOG_DECLSPEC FILELog : public Log<Output2FILE> {};
//typedef Log<Output2FILE> FILELog;

#ifndef FILELOG_MAX_LEVEL
#define FILELOG_MAX_LEVEL ldebug4
#endif

#define FILE_LOG(level) \
	if (level > FILELOG_MAX_LEVEL) ;\
	else if (level > FILELog::ReportingLevel() || !Output2FILE::Stream()) ; \
	else FILELog().Get(level)

#define L_(level) \
if (level > FILELOG_MAX_LEVEL) ;\
else if (level > FILELog::ReportingLevel() || !Output2FILE::Stream()) ; \
else FILELog().Get(level)


#include <sys/time.h>

inline string NowTime(){

	char *timestamp = (char*) calloc(1, sizeof(tm));
	time_t t;
	time(&t);
	tm* now = localtime(&t);
	sprintf(timestamp, "%d-%d-%d %d:%d:%d", now->tm_mday, now->tm_mon + 1, now->tm_year + 1900, now->tm_hour, now->tm_min, now->tm_sec);

	struct timeval tv;
	gettimeofday(&tv, 0);
	
	sprintf(timestamp, "%s.%03ld", timestamp, (long)tv.tv_usec / 1000);
	string result(timestamp);
	free(timestamp);
	return result;
}


inline void initLogger(const char * file, TLogLevel level){
	FILELog::ReportingLevel() = level;
	FILE* log_fd = fopen(file, "w" );
	Output2FILE::Stream() = log_fd;
}

inline void endLogger(){
	if (Output2FILE::Stream())
		fclose(Output2FILE::Stream());
}

#endif //__LOGGER_H__
