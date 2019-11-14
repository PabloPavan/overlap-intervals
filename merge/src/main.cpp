#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "../include/interval.h"

using namespace std;


bool compare_intervals(Interval *last, Interval *current);


int main(int argc, char const *argv[]){

	string input_path;
	string output_path;

	if(argc==3) { 
		cout << endl << "--Following Are The Command Line Arguments Passed--" << endl; 
		for (int i = 1; i < argc; ++i)
			cout << endl <<"argv["<<i<<"]: " << argv[i] << endl; 

		input_path = argv[1];
		output_path = argv[2];

	}else{
		cout <<"Error: argument -- usage: " << argv[0] << " path of the input file [.csv] -- path of the output file [.csv] " << endl;
		exit(1);
	}


	char line[4096];
	char delim[] = ";";

	fstream save_file;
	save_file.open(output_path, fstream::out);

	save_file << "start;end;duration;phases;nphases;jobs;njobs;days;ndays" << endl;

	FILE *f = fopen(input_path.c_str(), "r");

	char *header = fgets(line, sizeof(line), f); // skip header
	// start;end;duration;phases;nphases;jobs;njobs;days;ndays

	fgets(line, sizeof(line), f);
	char *token = strtok(line,delim);
	int64_t start_time = atol(token); // start_time
	token = strtok(NULL,delim); //end_time
	int64_t end_time = atol(token);
	token = strtok(NULL,delim); //duration
	token = strtok(NULL,delim); //phases
	string phases(token);
	token = strtok(NULL,delim); //nphases
	int nphases = atoi(token);
	token = strtok(NULL,delim); //jobs
	string jobs(token);
	token = strtok(NULL,delim); //njobs
	int njobs = atoi(token);
	token = strtok(NULL,delim); // days
	string days(token);
	token = strtok(NULL,delim); //ndays
	int ndays = atoi(token);

	Interval *last = new Interval(start_time, end_time, phases, nphases, jobs, njobs, days, ndays);

	// cout << " anterior -------- start_time " << last->getStart_time() << " end_time " << last->getStart_time() << " phases " << last->getPhases() << " nphases " << last->getnPhases() << " jobs " << last->getJobs() << " njobs " << last->getnJobs() << " days " << last->getDays() << " ndays " << last->getnDays() << endl;

	while(fgets(line, sizeof(line), f)){

		char *token = strtok(line,delim);
		int64_t start_time = atol(token); // start_time
		token = strtok(NULL,delim); //end_time
		int64_t end_time = atol(token);
		token = strtok(NULL,delim); //duration
		token = strtok(NULL,delim); //phases
		string phases(token);
		token = strtok(NULL,delim); //nphases
		int nphases = atoi(token);
		token = strtok(NULL,delim); //jobs
		string jobs(token);
		token = strtok(NULL,delim); //njobs
		int njobs = atoi(token);
		token = strtok(NULL,delim); // days
		string days(token);
		token = strtok(NULL,delim); //ndays
		int ndays = atoi(token);

		Interval *current = new Interval(start_time, end_time, phases, nphases, jobs, njobs, days, ndays);		

		if (!compare_intervals(last, current)){
		 	save_file << last->getStart_time() <<";"<< current->getStart_time() <<";"<< current->getStart_time()-last->getStart_time() <<";"<< last->getPhases() <<";"<< last->getnPhases() <<";"<< last->getJobs() <<";"<< last->getnJobs() <<";"<< last->getDays() <<";"<< last->getnDays() << endl;
			*last = *current;	
		 }

		delete current;
	}

	delete last;

	fclose(f);
	save_file.close();

	return 0;
}

bool compare_intervals(Interval *last, Interval *current){

	if (last->getPhases() == current->getPhases() && last->getJobs() == current->getJobs() && last->getDays() == current->getDays())
		return true;	
	return false;
}