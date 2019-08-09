#include "utils.h"
#include "logger.h"
#include "node.h"
#include "heap_min.h"
#include "heap_max.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>


#define HEAP_SIZE 30000

int main(int argc, char const *argv[]){

	#ifdef LOG
		initLogger( "logger.log", ldebug);
		L_(linfo) << "program started";
	#endif
	
	Heap_min *heap_min;
	heap_min = new Heap_min(HEAP_SIZE);

	vector<char*> filename_v;
	vector<char*> info_v;

	read_file(heap_min, 0, filename_v, info_v);

	#ifdef LOG
		L_(ldebug) << "min heap size: " << heap_min->getSize();
	#endif	

	Node* n_current;
	Node* n_next;

	int interation = 0;
	while(!heap_min->isEmpty()){
		interation++;
		vector<Node*> nodes;
		vector<Node*> nexts;
		n_current = heap_min->extract();

		if(!heap_min->isEmpty()){

			nodes.push_back(n_current);
			if(!heap_min->isEmpty())
				while(n_current->getStart() == heap_min->top()->getStart()){
					nodes.push_back(heap_min->extract());
					if(heap_min->isEmpty())
						break;
				}

			if(!heap_min->isEmpty()){

				n_next = heap_min->extract();

				nexts.push_back(n_next);
				if(!heap_min->isEmpty())
					while(n_next->getStart() == heap_min->top()->getStart() && !heap_min->isEmpty()){
						nexts.push_back(heap_min->extract());	
						if(heap_min->isEmpty())
							break;
					}	


				if(nodes.size() > 1){	
					create_intervals_without_next(heap_min, nodes);
					nodes.clear();
				}else{
					heap_min->insert(nodes[0]);	
					nodes.clear();
				}	

				if (nexts.size() > 1){
					create_intervals_without_next(heap_min, nexts);
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
				}else{
					#ifdef LOG
						L_(ldebug) << "else 1";
					#endif
					heap_min->insert(n_next);
					dump_file(n_current->getEnd(), n_current);
				} 				
			}else{
				#ifdef LOG
					L_(ldebug) << "else 2";
				#endif
				if(nodes.size() > 1){		
					create_intervals_without_next(heap_min, nodes);
					nodes.clear();
				}else{
					dump_file(nodes[0]->getEnd(), nodes[0]);
					nodes.clear();
				}
			}
		}else{
			#ifdef LOG
				L_(ldebug) << "else 3";
			#endif
			dump_file(n_current->getEnd(), n_current);
		}	
	}

	#ifdef LOG
		L_(ldebug) << "min size of heap after: " << heap_min->getSize();
	#endif

	dump_dict("../data/phases.csv", info_v);
	dump_dict("../data/jobs.csv", filename_v);

	endLogger();
	return 0;
}
