#ifndef INTERVAL_H
#define	INTERVAL_H

#include <string>
#include <iostream>
using namespace std;

class Interval{

private:

	int64_t start_time;
	int64_t end_time;
	string phases;
	int nphases;
	string jobs;
	int njobs;
	string days;
	int ndays;

public:
	Interval(int64_t start_time, int64_t end_time, string phases, int nphases, string jobs, int njobs, string days, int ndays);
	~Interval();

	int64_t getStart_time();
	int64_t getEnd_time();
	string getPhases();
	int getnPhases();
	string getJobs();
	int getnJobs();
	string getDays();
	int getnDays();
};



#endif