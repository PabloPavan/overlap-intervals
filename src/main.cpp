#include "node.h"
#include "heap.h"
#include <iostream>
#include <cstring>
#include <vector>


using namespace std;

#define DUMP
#define BUFFER_SIZE 2048

int idx_find(char *word, vector<char*>&v){
	int idx = 0;
	for (idx = 0; idx < v.size(); ++idx)
		if(strcmp(v[idx],word) == 0) 
			break;

	if(idx == v.size())
		v.push_back(word);	
	
	return idx;	
}

int main(int argc, char const *argv[]){

	Heap h(30000);
	FILE *f = fopen("../data/intervals.csv", "r");
	char line[BUFFER_SIZE];
	char delim[] = ";";
	fgets(line, sizeof(line), f); // skip header

	Node *no;

	vector<char*> filename_v;
	vector<char*> info_v;

	//vector<char[BUFFER_SIZE]> info_v;

	while(fgets(line, sizeof(line), f)){
		char *filename = (char *) calloc(BUFFER_SIZE, sizeof(char));
		long int start_time;
		long int end_time;
		double start;
		double end;
		char *info = (char *) calloc(BUFFER_SIZE, sizeof(char));

		char *token = strtok(line,delim); //filename
		//strcpy (filename,token);
		strcpy(filename, token);
		filename = (char *) realloc(filename, (strlen(filename) + 1) * sizeof(char));
		//cout << filename << endl;
		token = strtok(NULL,delim);// joid 
		token = strtok(NULL,delim); //uid
		token = strtok(NULL,delim); //runtime
		token = strtok(NULL,delim); //start_time
		start_time = atoi(token);
		//cout << start_time << endl;
		token = strtok(NULL,delim); //end_time
		end_time = atoi(token);
		//cout << end_time << endl;
		token = strtok(NULL,delim); //exec
		token = strtok(NULL,delim); //file
		token = strtok(NULL,delim); //interval-id
		token = strtok(NULL,delim); //start
		start = atof(token);
		//printf("%f\n",  start);
		token = strtok(NULL,delim); //end
		end = atof(token);
		//printf("%f\n",  end);
		token = strtok(NULL,delim); //info
		strcpy(info, token);
		info = (char *) realloc(info, (strlen(info) + 1) * sizeof(char));
		//cout << info << endl;
		token = strtok(NULL,delim); //X1_access_count
		token = strtok(NULL,delim); //X1_access_size
		token = strtok(NULL,delim); //read_bytes
		token = strtok(NULL,delim); //write_bytes

		// convert the start_time, end_time, start and end to micro
		start  = start * 1000000;
		start_time = start_time * 1000000;
		long int starti = (long int) start;
		start_time = start_time + starti;
		end  = end * 1000000;
		end_time = end_time * 1000000;
		long int endi = (long int) end;
		end_time = end_time + endi;

		#ifdef DUMP
		printf("start_time: %ld\n",  start_time);
		printf("end_time: %ld\n",  end_time);
		#endif

		int idx_f = idx_find(filename, filename_v);

		int idx_i = idx_find(info, info_v);

		#ifdef DUMP
		printf("index filename (job): %d\n",  idx_f);
		printf("index info (phase): %d\n",  idx_i);
		#endif


		// no  = new Node(info_i,filename_i,1,start_time,end_time);
		// h.insert(no);
		
	}


	for (vector<char*>::iterator i = filename_v.begin(); i != filename_v.end(); ++i)
		{
			cout << ":   " << *i << endl;
		}

	cout << h.getSize() << endl;

	// Node* nx = h.extract();

	// cout << "phase " << nx->getPhase() << endl;
	// cout << "job " << nx->getJob() << endl;
	// cout << "day " << nx->getDay() << endl;
	// cout << "start " << nx->getStart() << endl;


   fclose(f);
	return 0;
}