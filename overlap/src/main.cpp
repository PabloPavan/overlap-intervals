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
	heap_total_size = read_file(heap_min, front_pop(path_l), day, filename_v, info_v);
	
	Node* n_current;
	Node* n_next;


	while(!heap_min->isEmpty()){

		vector<Node*> nodes;
		vector<Node*> nexts;

		if (!path_l.empty() && heap_min->getSize() < (heap_total_size*0.2)){
			#ifdef LOG
				L_(linfo) << "size of the heap current: " << heap_min->getSize() << " -- 20 perc of the total size: " << (heap_total_size*0.2);
			#endif

			dump_dict(phases_path, info_v);
			dump_dict(jobs_path, filename_v);

			heap_total_size = read_file(heap_min, front_pop(path_l), ++day, filename_v, info_v);

		}
		
		n_current = heap_min->extract();

		if(!heap_min->isEmpty()){

			nodes.emplace_back(n_current);
			if(!heap_min->isEmpty())
				while(n_current->getStart() == heap_min->top()->getStart() && !heap_min->isEmpty()){
					nodes.emplace_back(heap_min->extract());
					if(heap_min->isEmpty())
						break;
				}

			if(!heap_min->isEmpty()){

				n_next = heap_min->extract();

				nexts.emplace_back(n_next);
				if(!heap_min->isEmpty())
					while(n_next->getStart() == heap_min->top()->getStart()){
						nexts.emplace_back(heap_min->extract());	
						if(heap_min->isEmpty())
							break;
					}	


				if(nodes.size() > 1){	
					create_intervals_without_next(heap_min, nodes);
					for (int i = 0; i < nodes.size(); ++i){
						delete nodes[i];
					}

				}else{
					heap_min->insert(nodes[0]);
				}	

				if (nexts.size() > 1){
					create_intervals_without_next(heap_min, nexts);
					for (int i = 0; i < nexts.size(); ++i){
						delete nexts[i];
					}

				}else{
					heap_min->insert(nexts[0]);
				}

				n_current = heap_min->extract();
				n_next = heap_min->extract();
				
				if(n_next->getStart() < n_current->getEnd()){
					dump_file(n_next->getStart(), n_current);
					if (n_current->getEnd() < n_next->getEnd()){
						heap_min->insert(new Node(n_next, n_current, n_next->getStart(), n_current->getEnd()));
						#ifdef LOG
							L_(ldebug) << "new 1 - start " << n_next->getStart() << " end " << n_current->getEnd();
						#endif
					}else if(n_next, n_current, n_next->getStart() != n_next->getEnd()){
						heap_min->insert(new Node(n_next, n_current, n_next->getStart(), n_next->getEnd()));
						#ifdef LOG
							L_(ldebug) << "new 2 - start " << n_next->getStart() << " end " << n_next->getEnd();
						#endif	
					} 	 
					if(n_current->getEnd() < n_next->getEnd()){
						heap_min->insert(new Node(n_next, n_current->getEnd(), n_next->getEnd()));
						#ifdef LOG
							L_(ldebug) << "new 3 - start " << n_current->getEnd() << " end " << n_next->getEnd();
						#endif	
					}else if(n_current, n_next->getEnd() != n_current->getEnd()){	
						heap_min->insert(new Node(n_current, n_next->getEnd(), n_current->getEnd()));
						#ifdef LOG
							L_(ldebug) << "new 4 - start " << n_next->getEnd() << " end " << n_current->getEnd();
						#endif
					}
					delete n_current;
					delete n_next;		
				}else{
					#ifdef LOG
						L_(ldebug) << "else 1";
					#endif
					heap_min->insert(n_next);
					dump_file(n_current->getEnd(), n_current);
					delete n_current;
				} 				
			}else{
				#ifdef LOG
					L_(ldebug) << "else 2";
				#endif
				if(nodes.size() > 1){		
					create_intervals_without_next(heap_min, nodes);
					for (int i = 0; i < nodes.size(); ++i){
						delete nodes[i];
					}
				}else{
					dump_file(nodes[0]->getEnd(), nodes[0]);
					delete nodes[0];			
				}
			}
		}else{
			#ifdef LOG
				L_(ldebug) << "else 3";
			#endif
			dump_file(n_current->getEnd(), n_current);
			delete n_current;
		}	
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
