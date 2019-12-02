#include "../include/utils.h"
#include "../include/logger.h"
#include "../include/node.h"
#include "../include/heap_min.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include<tuple>


string input_path, output_path;

fstream main_file;

int main(int argc, char const *argv[]){

	if(argc==3) { 
		cout << endl << "--Following Are The Command Line Arguments Passed--" << endl; 
		for (int i = 1; i < argc; ++i)
			cout << endl <<"argv["<<i<<"]: " << argv[i] << endl; 

		input_path = argv[1];
		output_path = argv[2];

	}else{
		cout <<"Error: argument -- usage: " << argv[0] << " path of the input file [.csv] -- folder's path of the output file [path/]" << endl;
		exit(1);
	}

	#ifdef LOG
		initLogger( "logger.log", linfo);
		L_(linfo) << "Program started";
		L_(linfo) << "Following Are The Command Line Arguments Passed";
		L_(linfo) << "argv[1]: " << input_path << " -- argv[2]: " << output_path;
	#endif

	string line;
	ifstream file_path;
	
	string path_save = output_path+"final.csv";
	main_file.open(path_save, fstream::app);

	Heap_min *heap_min;
	heap_min = new Heap_min();

	unsigned int heap_total_size = 0;
	int64_tmin_timestamp = -1; 

	heap_total_size = read_file(heap_min, input_path , &min_timestamp); 

	int64_tclock = min_timestamp;

	tuple<int64_t, Node*> n_current;

	vector<Node*> current_pattern;

	while(!heap_min->isEmpty()){

		n_current = heap_min->extract();

		if(get<1>(n_current)->getStart() == get<1>(n_current)->getEnd()){
			delete get<1>(n_current);
			continue;
		}

		if(get<0>(n_current) > clock){
			dump_file(clock, get<0>(n_current), current_pattern);
		}

		if(get<0>(n_current) == get<1>(n_current)->getStart()){
			current_pattern.push_back(get<1>(n_current));
		} else if(get<0>(n_current) == get<1>(n_current)->getEnd()){
			for (int i = 0; i < current_pattern.size(); ++i){
				if(nodes_equals_compare(get<1>(n_current), current_pattern[i])){
					delete current_pattern[i];
					current_pattern.erase(current_pattern.begin()+i);
				}
			}
			delete get<1>(n_current);
		}
		else{
		 	#ifdef LOG
				L_(lerror) << "PANIC in main: the conditions doesn't match";
		 	#endif
		 	exit(1);
		}
		
	clock = get<0>(n_current);
	}

	#ifdef LOG
		L_(linfo) << "min size of heap after: " << heap_min->getSize();
	#endif

	delete heap_min;
	main_file.close();

	endLogger();

	return 0;
}
