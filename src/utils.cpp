#include "utils.h"


int idx_find(char *word, vector<char*>&v){
	int idx = 0;
	for (idx = 0; idx < v.size(); ++idx)
		if(strcmp(v[idx],word) == 0) 
			break;
	if(idx == v.size())
		v.push_back(word);	
	return idx;	

}

/* remove values duplicates 
	recive vector pointer of nodes and name of funtion 
	return values vector

 */
vector<int> remove_duplicates(vector<Node*>&v, vector<int> (Node::*functionPtr)()){
	vector<int> vec;
 	set<int> s;
 	for(int i = 0; i < v.size(); ++i){
 		vector<int> u = (v[i]->*functionPtr)();
 		for(int j = 0; j < u.size(); ++j)
			s.insert(u[j]);
 	}
 	vec.assign(s.begin(),s.end()); 
 	return vec;
}

int min_find(vector<Node*>&v){
    int min = 0;
    for(int i = 1; i < v.size(); ++i)
        if(v[i]->getEnd() < v[min]->getEnd())
        	min = i;
    return min;
}

Node* back_pop(vector<Node*>&v){
	Node *no;
	no = v.back();
	v.pop_back();
	return no;
}

void dump_file(int long new_end, vector<Node*>&v){
	// open csv final file and add new line
	// start and end 
	// phase and jobs sep by ,
	// day 

	char path_save[] = "../data/final.csv";

	if(!first_write){
		first_write = true;
		last_end = new_end;
	}

	if (v[0]->getStart() > last_end){
		#ifdef DUMP
		cout << "start: " << last_end << " end: " << v[0]->getStart()  << " duration: " << v[0]->getStart()-last_end; 
		cout << " phases: " << -1; 
		cout << " jobs: " << -1 << endl << endl;
		#endif

		fstream save_file;

		save_file.open(path_save, fstream::app);

		save_file <<  last_end <<";"<< v[0]->getStart() <<";"<< v[0]->getStart()-last_end <<";"<< -1 <<";"<< 0 <<";"<< -1 <<";"<< 0 << endl;

		save_file.close();
	}
	
	last_end = new_end;

	vector<int> jobs_vec = remove_duplicates(v, &Node::getJob);
	vector<int> phases_vec = remove_duplicates(v, &Node::getPhase);
	vector<int> days_vec = remove_duplicates(v, &Node::getDay);

	char *jobs = (char*) calloc(v.size() * 2 + 1, sizeof(char));
	char *phases = (char*) calloc(v.size() * 2 + 1, sizeof(char));
	char *days = (char*) calloc(v.size() * 2 + 1, sizeof(char));
	char *tmp = (char*) calloc(3, sizeof(char));

	int number_of_jobs = 0;
	for (number_of_jobs = 0; number_of_jobs < jobs_vec.size()-1; ++number_of_jobs){
		sprintf(tmp, "%d,", jobs_vec[number_of_jobs]);
		strcat(jobs, tmp);
	}
	sprintf(tmp, "%d", jobs_vec[number_of_jobs++]);
	strcat(jobs, tmp);

	int number_of_phases = 0;
	for (number_of_phases = 0; number_of_phases < phases_vec.size()-1; ++number_of_phases){
		sprintf(tmp, "%d,", phases_vec[number_of_phases]);
		strcat(phases, tmp);
	}
	sprintf(tmp, "%d", phases_vec[number_of_phases++]);
	strcat(phases, tmp);

	int number_of_days = 0;
	for (number_of_days = 0; number_of_days < days_vec.size()-1; ++number_of_days){
		sprintf(tmp, "%d,", days_vec[number_of_days]);
		strcat(days, tmp);
	}
	sprintf(tmp, "%d", days_vec[number_of_days++]);
	strcat(days, tmp);


	#ifdef DUMP
	cout << "start: " << v[0]->getStart() << " end: " << new_end << " duration: " << new_end-v[0]->getStart(); 
	cout << " phases: " << phases; //<< phases << " number of phases: " << number_of_phases; 
	cout << " jobs: " << jobs;//<< " number of jobs: " << number_of_jobs;
	cout << " days: " << days;
	cout << endl << endl;
	#endif 

	fstream save_file;

	save_file.open(path_save, fstream::app);

	save_file <<  v[0]->getStart() <<";"<< new_end <<";"<< new_end-v[0]->getStart() <<";"<< phases <<";"<< number_of_phases <<";"<< jobs <<";"<< number_of_jobs <<";"<< days <<";"<< number_of_days << endl;

	save_file.close();

	free(jobs);
	free(phases);
	free(tmp);

}

void dump_dict(const char path[], vector<char*>&v){
	fstream save_file;
	save_file.open(path, fstream::out);

	save_file << "id;" << "name" << endl; 

	for (int i = 0; i < v.size(); ++i){
		save_file << i << ";" << v[i] << endl;
	}
}

void create_intervals_without_next(vector<Node*> nodes){
	Node* n_current;
	Node* n_next;
	Node* no;

	Heap *aux_heap = new Heap(nodes.size()+1);

	for (int i = 0; i < nodes.size(); ++i)
		aux_heap->insert(new Node(nodes[i]->getPhase(), nodes[i]->getJob(), nodes[i]->getDay(), nodes[i]->getEnd(), nodes[i]->getStart()));
	

	stack <vector<Node*>> stack_dump; 
	stack <long int> stack_end;
	while(!aux_heap->isEmpty()){
	 	vector<Node*> nodes;
	 	vector<Node*> nexts;

	 	n_current = aux_heap->extract();

	 	if(!aux_heap->isEmpty()){

	 		nodes.push_back(n_current);

	 		if(!aux_heap->isEmpty())
		 		while(n_current->getStart() == aux_heap->top()->getStart()){
		 			nodes.push_back(aux_heap->extract());
		 			if(aux_heap->isEmpty())
		 				break;
		 		}

	 		if(!aux_heap->isEmpty()){

	 			n_next = aux_heap->extract();

	 			nexts.push_back(n_next);
	 			if(!aux_heap->isEmpty())
			 		while(n_next->getStart() == aux_heap->top()->getStart() && !aux_heap->isEmpty()){
			 			nexts.push_back(aux_heap->extract());	
			 			if(aux_heap->isEmpty())
		 					break;
			 		}	

				int idx_min_nodes = min_find(nodes);
				int idx_min_nexts = min_find(nexts);

				if(nodes[idx_min_nodes]->getStart() < nexts[idx_min_nexts]->getStart()){
					vector<Node*> tmp;
					for (int i = 0; i < nexts.size(); ++i)
						tmp.push_back(new Node(nexts[i]->getPhase(), nexts[i]->getJob(), nexts[i]->getDay(), nodes[idx_min_nodes]->getStart(), nexts[i]->getEnd()));
				
					stack_dump.push(tmp);
					stack_end.push(nexts[idx_min_nexts]->getStart());

					no  = new Node(nexts,nodes, nexts[idx_min_nexts]->getEnd(), nodes[idx_min_nodes]->getStart());
					aux_heap->insert(no);
			 	}
			}else{

				vector<Node*> tmp;
				for (int i = 0; i < nodes.size(); ++i)
					tmp.push_back(new Node(nodes[i]->getPhase(), nodes[i]->getJob(), nodes[i]->getDay(), nodes[i]->getEnd(), nodes[i]->getStart()));

				stack_dump.push(tmp);
				stack_end.push(tmp[0]->getEnd());
			}
		}else{
			nodes.push_back(n_current);
			stack_dump.push(nodes);
			stack_end.push(nodes[0]->getEnd());

		}
	}

	while (!stack_dump.empty()) { 
		dump_file(stack_end.top(),stack_dump.top());
		stack_end.pop();
		stack_dump.pop(); 
	} 	

}