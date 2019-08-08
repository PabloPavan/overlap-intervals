#include "utils.h"


#define HEAP_SIZE 30000

int main(int argc, char const *argv[]){

	Heap_min *h;
	h = new Heap_min(HEAP_SIZE);

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

				// int idx_min_nodes = min_find(nodes);
				// int idx_min_nexts = min_find(nexts);

			 	if(nodes.size() > 1){
			 		cout << "nodes 1" << endl;
			 		create_intervals_without_next(h, nodes);
			 		nodes.clear();
			 	}else{
			 		h->insert(nodes[0]);	
			 	}	

			 	if (nexts.size() > 1){
				 	cout << "nexts 1" << endl;
				 	create_intervals_without_next(h, nexts);
				 	nexts.clear();

				}else{
					h->insert(nexts[0]);
				}

				n_current = h->extract();
				n_next = h->extract();
			 	
				if(n_next->getStart() < n_current->getEnd()){
					cout << "aqui" << endl;

					dump_file(n_next->getStart(), n_current);

					if (n_current->getEnd() < n_next->getEnd()){

				 	 	no  = new Node(n_next, n_current, n_next->getStart(), n_current->getEnd());
				 	 	h->insert(no);	
				 	 	cout << "novo 1 " << n_next->getStart() << " " << n_current->getEnd()  << endl;
				 	}else{
				 	 	no  = new Node(n_next, n_current, n_next->getStart(), n_next->getEnd());
				 	 	h->insert(no);
				 	 	cout << "novo 2 " << n_next->getStart() << " " << n_next->getEnd() << endl;	
				 	} 	 
				 	if(n_current->getEnd() < n_next->getEnd()){
						no  = new Node(n_next, n_current->getEnd(), n_next->getEnd());
				 	 	h->insert(no);
				 	 	cout << "novo 3 " <<  n_current->getEnd() << " " << n_next->getEnd() << endl;
				 	}else{
						no  = new Node(n_current, n_next->getEnd(), n_current->getEnd());	
					 	h->insert(no);
					 	cout << "novo 4 " <<  n_next->getEnd() << " " << n_current->getEnd() << endl;	
				 	}		
			 	}else{
					cout << "else 1" << endl;
					//for (int i = 0; i < nexts.size(); ++i)
					h->insert(n_next);
					dump_file(n_current->getEnd(), n_current);

				} 				
	 		}else{
	 			cout << "else 2" << endl;
	 			if(nodes.size() > 1){		
					create_intervals_without_next(h, nodes);
					nodes.clear();
				}else{
					dump_file(nodes[0]->getEnd(), nodes[0]);
					nodes.clear();
				}
	 		}
	 	}else{
	 		cout << "else 3" << endl;
	 		dump_file(n_current->getEnd(), n_current);
	 	}	
	}

	#ifdef DUMP
	cout << "size of heap after: " << h->getSize() << endl;
	#endif

	dump_dict("../data/phases.csv", info_v);
	dump_dict("../data/jobs.csv", filename_v);

	return 0;
}
