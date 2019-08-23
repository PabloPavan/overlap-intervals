#include "../include/interval.h"


Interval::Interval(int64_t start_time, int64_t end_time, string phases, int nphases, string jobs, int njobs, string days, int ndays){
	this->start_time = start_time;
	this->end_time = end_time;
	this->phases = phases;
	this->nphases = nphases;
	this->jobs = jobs;
	this->njobs = njobs;
	this->days = days;
	this->ndays = ndays;


}

Interval::~Interval() { /* O(n lg n) */
	
}

int64_t Interval::getStart_time() { /* O(1) */
	return this->start_time;
}

int64_t Interval::getEnd_time() { /* O(1) */
	return this->end_time;
}

string Interval::getPhases() { /* O(1) */
	return this->phases;
}

int Interval::getnPhases() { /* O(1) */
	return this->nphases;
}

string Interval::getJobs() { /* O(1) */
	return this->jobs;
}

int Interval::getnJobs() { /* O(1) */
	return this->njobs;
}

string Interval::getDays() { /* O(1) */
	return this->days;
}

int Interval::getnDays() { /* O(1) */
	return this->ndays;
}