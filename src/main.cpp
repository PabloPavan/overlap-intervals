#include "utils.h"


#define BUFFER_SIZE 4096

int main(int argc, char const *argv[]){
	//long int epoch_time = 1325376000;
	long int epoch_time = 0;

	Heap *h;
	h = new Heap(30000);

	char path_save[] = "../data/final.csv";
	fstream save_file;
	save_file.open(path_save, fstream::out);

	save_file << "start;" << "end;" << "duration;" << "phases;" << "nphases;" << "jobs;" << "njobs" << endl; 

	save_file.close();

	FILE *f = fopen("../data/intervals.small.csv", "r");
	char line[BUFFER_SIZE];
	char delim[] = ";";

	Node *no;
	vector<char*> filename_v;
	vector<char*> info_v;

	fgets(line, sizeof(line), f); // skip header

	while(fgets(line, sizeof(line), f)){
		char *filename = (char *) calloc(BUFFER_SIZE, sizeof(char));
		long int start_time;
		long int end_time;
		double start;
		double end;
		char *info = (char *) calloc(BUFFER_SIZE, sizeof(char));

		char *token = strtok(line,delim); //filename
		strcpy(filename, token);
		filename = (char *) realloc(filename, (strlen(filename) + 1) * sizeof(char));
		token = strtok(NULL,delim); //start_time
		start_time = atoi(token);
		token = strtok(NULL,delim); //end_time
		end_time = atoi(token);
		token = strtok(NULL,delim); //start
		start = atof(token);
		token = strtok(NULL,delim); //end
		end = atof(token);
		token = strtok(NULL,delim); //info
		strcpy(info, token);
		info[strlen(info)-1] = '\0';
		info = (char *) realloc(info, (strlen(info) + 1) * sizeof(char));
		// convert the start_time, end_time, start and end to micro
		start  = start * 1; 
		start_time = start_time - epoch_time; 
		start_time = start_time * 1;
		long int starti = (long int) start;

		long int start_ = start_time + starti;

		end = end * 1;
		long int endi = (long int) end;
		long int end_ = start_ + (endi - starti);

		#ifdef DUMP
		cout << "[" << start_ << ", " << end_ << "]" << endl;
		#endif

		no  = new Node(idx_find(info, info_v),idx_find(filename, filename_v),1,start_,end_);
		h->insert(no);
	}

	#ifdef DUMP
		cout << endl << "heap size: " << h->getSize() << endl << endl;
	#endif	
	
	fclose(f);

	#ifdef DUMP
	for (int i = 0; i < info_v.size(); ++i)
		cout << "[" << i << "] = " << info_v[i] << endl;
	cout << endl;
	for (int i = 0; i < filename_v.size(); ++i)
		cout << "[" << i << "] = " << filename_v[i] << endl;
	#endif

	Node* n_current;
	Node* n_temp;
	Node* n_next;
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


	 		#ifdef DUMP
	 		for (int i = 0; i < nodes.size(); ++i){
	 			cout << interation << " nodes:  " << i << " " << nodes[i]->getStart() << endl << endl;
	 		}
	 		#endif

	 		//cout << "size : " << h->getSize() << endl;

	 		if(!h->isEmpty()){

	 			n_next = h->extract();

	 			nexts.push_back(n_next);
	 			if(!h->isEmpty())
			 		while(n_next->getStart() == h->top()->getStart() && !h->isEmpty()){
			 			nexts.push_back(h->extract());	
			 			if(h->isEmpty())
		 					break;
			 		}	
	 			#ifdef DUMP
	 			for (int i = 0; i < nexts.size(); ++i){
	 				cout << interation << " nexts:  " << i << " " <<  nexts[i]->getStart() << endl << endl;
	 			}
	 			#endif

				int idx_min_nodes = min_find(nodes);
				int idx_min_nexts = min_find(nexts);

				if(nexts[idx_min_nexts]->getStart() < nodes[idx_min_nodes]->getEnd()){
					dump_file(nexts[idx_min_nexts]->getStart(), nodes);	 
			
					if (nodes[idx_min_nodes]->getEnd() < nexts[idx_min_nexts]->getEnd()){
						cout << "novo 1 " << nexts[idx_min_nexts]->getStart() << " ; " << nodes[idx_min_nodes]->getEnd() << endl;
				 	 	no  = new Node(nexts, nodes, nexts[idx_min_nexts]->getStart(), nodes[idx_min_nodes]->getEnd());
				 	 	h->insert(no);	
				 	}else{
				 		cout << "novo 2 " << nexts[idx_min_nexts]->getStart() << " ; " << nexts[idx_min_nexts]->getEnd() << endl;
				 	 	no  = new Node(nexts, nodes, nexts[idx_min_nexts]->getStart(), nexts[idx_min_nexts]->getEnd());
				 	 	h->insert(no);	
				 	} 	 
				 	if(nodes[idx_min_nodes]->getEnd() < nexts[idx_min_nexts]->getEnd()){
				 		cout << "novo 3 " << nodes[idx_min_nodes]->getEnd() << " ; " << nexts[idx_min_nexts]->getEnd() << endl;
				 	 	no  = new Node(nexts, nodes[idx_min_nodes]->getEnd(), nexts[idx_min_nexts]->getEnd());
				 	 	h->insert(no);

				 	 }else{
				 	 	cout << "novo 4 " << nexts[idx_min_nexts]->getEnd() << " ; " << nodes[idx_min_nodes]->getEnd() << endl;
				 	 	no  = new Node(nodes, nexts[idx_min_nexts]->getEnd(), nodes[idx_min_nodes]->getEnd());	
				 	 	h->insert(no);
				 	 }	
				}else{

					cout << "else 1" << endl;
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
			cout << "else 3" << endl;
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
