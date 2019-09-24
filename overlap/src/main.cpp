#include "../include/utils.h"
#include "../include/logger.h"
#include "../include/node.h"
#include "../include/heap_min.h"
#include "../include/heap_max.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <list>


#define HEAP_SIZE 900E6

string input_path, output_path;



int main(int argc, char const *argv[]){

	if(argc==3) { 
		cout << endl << "--Following Are The Command Line Arguments Passed--" << endl; 
		for (int i = 1; i < argc; ++i)
			cout << endl <<"argv["<<i<<"]: " << argv[i] << endl; 

		input_path = argv[1];
		output_path = argv[2];

	}else{
		cout <<"Error: argument -- usage: " << argv[0] << " path of the input file [.dat] -- folder's path of the output file [path/]" << endl;
		exit(1);
	}

	#ifdef LOG
		initLogger( "logger.log", ldebug);
		L_(linfo) << "Program started";
		L_(linfo) << "Following Are The Command Line Arguments Passed";
		L_(linfo) << "argv[1]: " << input_path << " -- argv[2]: " << output_path;
	#endif

	
	string line;
	list<string> path_l;
	ifstream file_path;
	
	file_path.open(input_path);
	if (!file_path) {
		#ifdef LOG
			L_(lerror) << "Unable to open: " << input_path << " file";
		#endif
		exit(1);
	}
	
	while (file_path >> line) {
		#ifdef LOG
			L_(linfo) << "Input list: " << line;
		#endif
		path_l.push_back(line);
	}

	file_path.close();


	Heap_min *heap_min;
	heap_min = new Heap_min(HEAP_SIZE);

	vector<string> filename_v;
	vector<string> info_v;

	string jobs_path, phases_path;
	phases_path = output_path + "dict_phases.csv";
	jobs_path = output_path + "dict_jobs.csv";

	long int day = 3; 
	unsigned int heap_total_size = 0;
	long int min_timestamp = -1; 
	heap_total_size = read_file(heap_min, front_pop(path_l), &min_timestamp, day, filename_v, info_v); 


	long int clock = min_timestamp;

	cout << clock << endl;
	cout << heap_total_size << endl;
	
	Node* n_current;
	Node* n_next;

	vector<Node*> current_pattern;

	cout << "before" << endl;
	for (int i = 0; i < heap_min->getSize(); ++i){
		n_current = heap_min->print(i);
		cout << "nodes["<<i<<"] - start " << n_current->getStart() << " end " <<  n_current->getEnd() << endl;
	}

	// n_current  = heap_min->extract();

	// cout << "extract nodes[0]- start " << n_current->getStart() << " end " <<  n_current->getEnd() << endl;

	// cout << "after" << endl;
	// for (int i = 0; i < heap_min->getSize(); ++i){
	// 	n_current = heap_min->print(i);
	// 	cout << "nodes["<<i<<"] - start " << n_current->getStart() << " end " <<  n_current->getEnd() << endl;
	// }


	while(!heap_min->isEmpty()){

		if (!path_l.empty() && heap_min->getSize() < (heap_total_size*0.2)){
			#ifdef LOG
				L_(linfo) << "size of the heap current: " << heap_min->getSize() << " -- 20 perc of the total size: " << (heap_total_size*0.2);
			#endif

			dump_dict(phases_path, info_v);
			dump_dict(jobs_path, filename_v);

			heap_total_size = read_file(heap_min, front_pop(path_l), &min_timestamp, ++day, filename_v, info_v);

		}
		
		if(heap_min->getSize() > 1){
			n_current = heap_min->extract();
			cout << "aqui" << endl;
			n_next = heap_min->extract();

			cout<< "if principal "  << n_next->getStart() << "  " << clock << " " << current_pattern.size() << endl;
			if(n_next->getStart() > clock){

				if (current_pattern.size() == 0)
					break;

				cout << "salvar o intervalo start " << clock << " end " << n_current->getStart() << " size " << current_pattern.size() << endl;
				dump_file(clock, n_current->getStart(), current_pattern);

				// for (int i = 0; i < current_pattern.size(); ++i){
				// 	delete current_pattern[i];
				// }
			}

			cout << n_next->getStart() << "  " <<  n_current->getStart() << endl;
			cout << n_next->getEnd() << "  " <<  n_current->getEnd() << endl;
			if(n_next->getStart() == n_current->getStart()){
				current_pattern.push_back(n_current);
				cout << "if" << endl;
			}else if(n_next->getEnd() == n_current->getEnd()){
				current_pattern.pop_back();
				cout << "else" << endl;
			}
			

			cout <<"before " << clock << " after " <<  n_next->getStart() << endl;
			clock = n_next->getStart();
			heap_min->insert(n_next);

	}

	cout << "deu aaqui" << endl;
	n_current = heap_min->extract();
	current_pattern.push_back(n_current);
	dump_file(clock, n_current->getStart(), current_pattern);

	}


	#ifdef LOG
		L_(ldebug) << "min size of heap after: " << heap_min->getSize();
	#endif


	dump_dict(phases_path, info_v);
	dump_dict(jobs_path, filename_v);


	delete heap_min;
	endLogger();

	return 0;
}
