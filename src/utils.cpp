#include "utils.h"

/**
 * Creating a dict using vector
 * if word exists in vector return the index
 * if word doesn't exist create a new value in vector
 * 
 * @param word that needs be find, ref for the vector
 * @return the index of the vector that contains the word
 */

int idx_find(char *word, vector<char*>&v){
	int idx = 0;
	for (idx = 0; idx < v.size(); ++idx)
		if(strcmp(v[idx],word) == 0) 
			break;
	if(idx == v.size())
		v.push_back(word);	
	return idx;	

}

/**
 * Removing values duplicates using a set
 * 
 * @param ref of the nodes vector and functions' ref of class Node
 * @return a vector with with unique values
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

/**
 * Finding a minimum value from a vector
 * 
 * @param ref of the nodes vector
 * @return the minimum value
 */

int min_find(vector<Node*>&v){
    int min = 0;
    for(int i = 1; i < v.size(); ++i)
        if(v[i]->getEnd() < v[min]->getEnd())
        	min = i;
    return min;
}

/**
 * Return and remove a value from a vector of the nodes
 * 
 * @param ref of the nodes vector
 * @return an object of Node
 */

Node* back_pop(vector<Node*>&v){
	Node *no;
	no = v.back();
	v.pop_back();
	return no;
}

/**
 * Creating statistics of a vector.
 * Creating a char with the values of the vector separated by comma
 * Count the number of values in the vector
 *
 * @param ref of the int vector
 * @return a struct with the number of values and the char
 */

statistics_data extract_statistics(vector<int> &v){

	char *value = (char*) calloc(v.size() * 2 + 1, sizeof(char));
	char *tmp = (char*) calloc(3, sizeof(char));

	int i = 0;
	for (i = 0; i < v.size()-1; ++i){
		sprintf(tmp, "%d,", v[i]);
		strcat(value, tmp);
	}
	sprintf(tmp, "%d", v[i++]);
	strcat(value, tmp);

	free(tmp);

	return statistics_data(i, value);
}

/**
 * Saving a file with the interval data
 * If exist a idle time between the before and the current interval 
 * save this in file
 * 
 *
 * @param time final of the interval, ref of the Node vector that
 * contains the info about the interval
 */

void dump_file(int long new_end, vector<Node*>&v){

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

	statistics_data jobs = extract_statistics(jobs_vec);
	statistics_data phases = extract_statistics(phases_vec);
	statistics_data days = extract_statistics(days_vec);

	#ifdef DUMP
	cout << "start: " << v[0]->getStart() << " end: " << new_end << " duration: " << new_end-v[0]->getStart(); 
	cout << " phases: " << phases.values; //<< phases << " number of phases: " << number_of_phases; 
	cout << " jobs: " << jobs.values;//<< " number of jobs: " << number_of_jobs;
	cout << " days: " << days.values;
	cout << endl << endl;
	#endif 

	fstream save_file;

	save_file.open(path_save, fstream::app);

	save_file <<  v[0]->getStart() <<";"<< new_end <<";"<< new_end-v[0]->getStart() <<";"<< phases.values <<";"<< phases.times <<";"<< jobs.values <<";"<< jobs.times <<";"<< days.values <<";"<< days.times << endl;

	save_file.close();

	free(jobs.values);
	free(phases.values);
	free(days.values);

}

/**
 * Saving a file with the vector of dict
 *
 * @param the file path and the vector
 */

void dump_dict(const char path[], vector<char*>&v){
	fstream save_file;
	save_file.open(path, fstream::out);

	save_file << "id;" << "name" << endl; 

	for (int i = 0; i < v.size(); ++i){
		save_file << i << ";" << v[i] << endl;
	}
}

// void dump_staticstics(vector<Node*>&v){

// }

/**
 * Creating intervals that not have a next interval
 *
 * @param vector of the Nodes
 */
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