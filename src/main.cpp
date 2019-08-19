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


#define HEAP_SIZE 30000

int main(int argc, char const *argv[]){

	#ifdef LOG
		initLogger( "logger.log", ldebug);
		L_(linfo) << "program started";
	#endif

	char* line =(char *) calloc(BUFFER_SIZE, sizeof(char));
	vector<char*> path_v;
	ifstream file_path;
	
	file_path.open("../data/path.dat");
	if (!file_path) {
		#ifdef LOG
			L_(lerror) << "Unable to open path.dat file";
		#endif
		exit(1);
	}
	
	while (file_path >> line) {
		line = (char *) realloc(line, (strlen(line) + 1) * sizeof(char));
		path_v.push_back(line);
	}

	file_path.close();
	
	Heap_min *heap_min;
	heap_min = new Heap_min(HEAP_SIZE);

	vector<string> filename_v;
	vector<string> info_v;

	long int day = 3; 
	int idx = 0;
	unsigned int heap_total_size;
	heap_total_size = read_file(heap_min, path_v[idx++], day, filename_v, info_v);

	#ifdef LOG
		L_(ldebug) << "min heap size: " << heap_min->getSize();
	#endif	

	Node* n_current;
	Node* n_next;

	vector<Node*> nodes;
	vector<Node*> nexts;


	while(!heap_min->isEmpty()){

		if (idx > path_v.size() && heap_min->getSize() < (heap_total_size*0.2)){
			cout << "aconteceu" << endl;
			heap_total_size = read_file(heap_min, path_v[idx++], ++day, filename_v, info_v);
		}

		n_current = heap_min->extract();

		if(!heap_min->isEmpty()){

			nodes.push_back(n_current);
			if(!heap_min->isEmpty())
				while(n_current->getStart() == heap_min->top()->getStart() && !heap_min->isEmpty()){
					nodes.push_back(heap_min->extract());
					if(heap_min->isEmpty())
						break;
				}

			if(!heap_min->isEmpty()){

				n_next = heap_min->extract();

				nexts.push_back(n_next);
				if(!heap_min->isEmpty())
					while(n_next->getStart() == heap_min->top()->getStart()){
						nexts.push_back(heap_min->extract());	
						if(heap_min->isEmpty())
							break;
					}	


				if(nodes.size() > 1){	
					create_intervals_without_next(heap_min, nodes);
					for (int i = 0; i < nodes.size(); ++i){
						delete nodes[i];
					}

					nodes.clear();
				}else{
					heap_min->insert(nodes[0]);
					nodes.clear();
				}	

				if (nexts.size() > 1){
					create_intervals_without_next(heap_min, nexts);
					for (int i = 0; i < nexts.size(); ++i){
						delete nexts[i];
					}
					nexts.clear();

				}else{
					heap_min->insert(nexts[0]);
					nexts.clear();
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
					nodes.clear();
				}else{
					dump_file(nodes[0]->getEnd(), nodes[0]);
					delete nodes[0];
					nodes.clear();
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

	dump_dict("../data/phases.csv", info_v);
	dump_dict("../data/jobs.csv", filename_v);


	for (int i = 0; i < path_v.size(); ++i){
		free(path_v[i]);
	}

	delete heap_min;
	endLogger();

	return 0;
}
