#include "node.h"
#include "heap.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <cstring>
#include <string>
#include <fstream>
#include <iomanip>  
#include <vector>
#include <algorithm>

using namespace std;

#define DUMP
#define BUFFER_SIZE 2048

int main(int argc, char const *argv[]){

	int i;
	Heap h(5);
	int l =  0;
	FILE *f = fopen("../data/intervals.small.csv", "r");
	char line[BUFFER_SIZE];
	char delim[] = ";";
	fgets(line, sizeof(line), f); // skip header

	Node *no;

	vector<char*> filename_v;
	//vector<char[BUFFER_SIZE]> info_v;

	while(fgets(line, sizeof(line), f)){
		char *filename = (char *) calloc(BUFFER_SIZE, sizeof(char));
		long int start_time;
		long int end_time;
		double start;
		double end;
		char *info;

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
		info = token;
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

		cout << "linha " << l << endl;
		#ifdef DUMP
		printf(" start_time final : %ld\n",  start_time);
		printf(" end_time final : %ld\n",  end_time);
		#endif



		for (i = 0; i < filename_v.size(); ++i)
			if(strcmp(filename_v[i],filename) == 0){
				cout << "\t\tfilename  " << filename << endl;
				cout << "\t\tvector " << filename_v[i] << endl;
				cout << "\t\tachou index:" << i << endl;
				break;
			}
		if(i == filename_v.size()){
			cout << "\t\t\tadicionei esse cara " << filename << endl;
			filename_v.push_back(filename);	
		}
		
		// nao sei pq nao funciona isso, da o mesmo resultado do codigo acima
		// vector<char*>::iterator filename_it = find(filename_v.begin(), filename_v.end(), filename);
		// if (filename_it != filename_v.end()){
		// 	int index = distance(filename_v.begin(), filename_it);
		// 	#ifdef DUMP
		//  	cout <<"Index of element in vector : "<< index << endl;
		//  	#endif DUMP
		// }else{
		// 	filename_v.insert(filename_v.begin(), filename);
		// }


		// no  = new Node(1,1,1,2,100);

		// h.insert(no);
		l++;
	}

	for (vector<char*>::iterator i = filename_v.begin(); i != filename_v.end(); ++i)
		{
			cout << "oi:   " << *i << endl;
		}

	// cout << h.getSize() << endl;

	// Node* nx = h.extract();

	// cout << "phase " << nx->getPhase() << endl;
	// cout << "job " << nx->getJob() << endl;
	// cout << "day " << nx->getDay() << endl;
	// cout << "start " << nx->getStart() << endl;


   fclose(f);
	return 0;
}