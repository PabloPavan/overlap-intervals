#include <iostream>
#include <vector>

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;


int main(int argc, char const *argv[]){

	string input_path;
	string output_path;

	if(argc==2) { 
		cout << endl << "--Following Are The Command Line Arguments Passed--" << endl; 
		for (int i = 1; i < argc; ++i)
			cout << endl <<"argv["<<i<<"]: " << argv[i] << endl; 

		input_path = argv[1];
		output_path = argv[2];

	}else{
		cout <<"Error: argument -- usage: " << argv[0] << " path of the input file [.csv] -- path of the output file [.csv] " << endl;
		exit(1);
	

	char line[BUFFER_SIZE];
	char delim[] = ";";

	FILE *f = fopen(input_path.c_str(), "r");

	char *header = fgets(line, sizeof(line), f); // skip header
	// start;end;duration;phases;nphases;jobs;njobs;days;ndays


	while(fgets(line, sizeof(line), f)){
		long int start_time;
		long int end_time;
		string phases;
		string jobs;
		string days
 




		char *token = strtok(line,delim); //filename
		filename(token);
		token = strtok(NULL,delim); //start_time
		start_time = atoi(token);
		token = strtok(NULL,delim); //end_time
		end_time = atoi(token);
		token = strtok(NULL,delim); //start
		start = atof(token);
		token = strtok(NULL,delim); //end
		end = atof(token);
		token = strtok(NULL,delim); //info
		token[strlen(token)-1] = '\0'; // remove \n
		string info(token);
		start  = start * 1000000; 
		start_time = start_time - epoch_time; 
		start_time = start_time * 1000000;
		long int starti = (long int) start;
		long int start_ = start_time + starti;
		end = end * 1000000;
		long int endi = (long int) end;
		long int end_ = start_ + (endi - starti);

		heap_min->insert(new Node(idx_find(info, info_v),idx_find(filename, filename_v),day,start_,end_));

	}



	return 0;
}
