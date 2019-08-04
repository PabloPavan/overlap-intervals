#include "utils.h"


#define HEAP_SIZE 30000

int main(int argc, char const *argv[]){

	Heap *h;
	h = new Heap(HEAP_SIZE);

	vector<char*> filename_v;
	vector<char*> info_v;

	read_file(h, 0, filename_v, info_v);

	#ifdef DUMP
		cout << endl << "heap size: " << h->getSize() << endl << endl;
	#endif	
	
	#ifdef DUMP
	for (int i = 0; i < info_v.size(); ++i)
		cout << "[" << i << "] = " << info_v[i] << endl;
	cout << endl;
	for (int i = 0; i < filename_v.size(); ++i)
		cout << "[" << i << "] = " << filename_v[i] << endl;
	#endif

	Node* n_current;
	Node* n_next;
	Node *no;
	//cout << "funciona " << h->extract()->getEnd() << endl;
	cout << endl;

	int interation = 0;
	while(!h->isEmpty()){
		interation++;
	 	vector<Node*> nodes;
	 	vector<Node*> nexts;
	 	n_current = h->extract();

	 	if(!h->isEmpty()){

	 		nodes.push_back(n_current);
	 		if(!h->isEmpty())
		 		while(n_current->getStart() == h->top()->getStart()){
		 			nodes.push_back(h->extract());
		 			if(h->isEmpty())
		 				break;
		 		}

	 		if(!h->isEmpty()){

	 			n_next = h->extract();

	 			nexts.push_back(n_next);
	 			if(!h->isEmpty())
			 		while(n_next->getStart() == h->top()->getStart() && !h->isEmpty()){
			 			nexts.push_back(h->extract());	
			 			if(h->isEmpty())
		 					break;
			 		}	

				int idx_min_nodes = min_find(nodes);
				int idx_min_nexts = min_find(nexts);

				if(nexts[idx_min_nexts]->getStart() < nodes[idx_min_nodes]->getEnd()){
					dump_file(nexts[idx_min_nexts]->getStart(), nodes);	 
			
					if (nodes[idx_min_nodes]->getEnd() < nexts[idx_min_nexts]->getEnd()){
				 	 	no  = new Node(nexts, nodes, nexts[idx_min_nexts]->getStart(), nodes[idx_min_nodes]->getEnd());
				 	 	h->insert(no);	
				 	}else{
				 	 	no  = new Node(nexts, nodes, nexts[idx_min_nexts]->getStart(), nexts[idx_min_nexts]->getEnd());
				 	 	h->insert(no);	
				 	} 	 
				 	if(nodes[idx_min_nodes]->getEnd() < nexts[idx_min_nexts]->getEnd()){
				 	 	no  = new Node(nexts, nodes[idx_min_nodes]->getEnd(), nexts[idx_min_nexts]->getEnd());
				 	 	h->insert(no);

				 	 }else{
				 	 	no  = new Node(nodes, nexts[idx_min_nexts]->getEnd(), nodes[idx_min_nodes]->getEnd());	
				 	 	h->insert(no);
				 	 }	
				}else{
					for (int i = 0; i < nexts.size(); ++i)
						h->insert(nexts[i]);

					if(nodes.size() > 1){
						create_intervals_without_next(nodes);
					}else{
						dump_file(nodes[0]->getEnd(), nodes);
					}
				} 				
	 		}else{
	 			if(nodes.size() > 1){		
					create_intervals_without_next(nodes);
				}else{
					dump_file(nodes[0]->getEnd(), nodes);
				}
	 		}
	 	}else{
	 		nodes.push_back(n_current);
	 		dump_file(n_current->getEnd(), nodes);
	 	}	
	}

	#ifdef DUMP
	cout << "size of heap after: " << h->getSize() << endl;
	#endif

	dump_dict("../data/phases.csv", info_v);
	dump_dict("../data/jobs.csv", filename_v);

	return 0;
}
