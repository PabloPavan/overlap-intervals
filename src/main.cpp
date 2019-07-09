#include "node.h"
#include "heap.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <set>


using namespace std;

#define DUMP
#define BUFFER_SIZE 4096

bool first_write = false;
long int last_end = 0;

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

	char *jobs = (char*) calloc(v.size() * 2 + 1, sizeof(char));
	char *phases = (char*) calloc(v.size() * 2 + 1, sizeof(char));
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


	#ifdef DUMP
	cout << "start: " << v[0]->getStart() << " end: " << new_end << " duration: " << new_end-v[0]->getStart(); 
	cout << " phases: " << phases; //<< phases << " number of phases: " << number_of_phases; 
	cout << " jobs: " << jobs;//<< " number of jobs: " << number_of_jobs;
	cout << endl << endl;
	#endif 

	fstream save_file;

	save_file.open(path_save, fstream::app);

	save_file <<  v[0]->getStart() <<";"<< new_end <<";"<< new_end-v[0]->getStart() <<";"<< phases <<";"<< number_of_phases <<";"<< jobs <<";"<< number_of_jobs << endl;

	save_file.close();

	free(jobs);
	free(phases);
	free(tmp);

	
}
	
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
		info = (char *) realloc(info, (strlen(info) + 1) * sizeof(char));
		// convert the start_time, end_time, start and end to micro
		start  = start * 1; 
		start_time = start_time - epoch_time; 
		start_time = start_time * 1;
		long int starti = (long int) start;

		long int start_ = start_time + starti;

		end = end * 1;
		// end_time = end_time - epoch_time; 
		// end_time = end_time * 1000000;
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
	while(!h->isEmpty()){
		vector<Node*> nodes;
		long int new_end = 0;
		n_current = h->extract();
		if(!h->isEmpty()){
	 		nodes.push_back(n_current);
		 	do{ 		
			 	n_temp = h->extract();
			 	nodes.push_back(n_temp);

		 	}while(h->getSize() >=1 && n_temp->getStart() == n_current->getStart());
			
			n_next = back_pop(nodes); // ultimo elemento do nodes é o n_next node 
		 	int idx_min = min_find(nodes);
			if(n_next->getStart() < nodes[idx_min]->getEnd()){
				dump_file(n_next->getStart(), nodes);	 
		
				if (nodes[idx_min]->getEnd() < n_next->getEnd()){
					cout << "novo 1 " << n_next->getStart() << " ; " << nodes[idx_min]->getEnd() << endl;
			 	 	no  = new Node(n_next->getPhase(), n_next->getJob(), n_next->getDay(), nodes, n_next->getStart(), nodes[idx_min]->getEnd());
			 	 	h->insert(no);	
			 	}else{
			 		cout << "novo 2 " << n_next->getStart() << " ; " << n_next->getEnd() << endl;
			 	 	no  = new Node(n_next->getPhase(), n_next->getJob(), n_next->getDay(), nodes, n_next->getStart(), n_next->getEnd());
			 	 	h->insert(no);	
			 	} 	 
			 	if(nodes[idx_min]->getEnd() < n_next->getEnd()){
			 		cout << "novo 3 " << nodes[idx_min]->getEnd() << " ; " << n_next->getEnd() << endl;
			 	 	no  = new Node(n_next->getPhase(), n_next->getJob(), n_next->getDay(), nodes[idx_min]->getEnd(), n_next->getEnd());
			 	 	h->insert(no);

			 	 }else{
			 	 	cout << "novo 4 " << n_next->getEnd() << " ; " << nodes[idx_min]->getEnd() << endl;
			 	 	no  = new Node(nodes, n_next->getEnd(), nodes[idx_min]->getEnd());	
			 	 	h->insert(no);
			 	 }	
			}else{
				cout << "else 1" << endl;
			 	h->insert(n_next);
		 		dump_file(nodes[idx_min]->getEnd(), nodes);		 		
			}
		}else{
			cout << "else 2" << endl;
			nodes.push_back(n_current);
			dump_file(n_current->getEnd(), nodes);
		}		 	
	}

	#ifdef DUMP
	cout << "size of heap after: " << h->getSize() << endl;
	#endif

	char path_save_phases[] = "../data/phases.csv";

	fstream save_file_phases;
	save_file_phases.open(path_save_phases, fstream::out);

	save_file_phases << "id;" << "name" << endl; 

	for (int i = 0; i < info_v.size(); ++i){
		save_file_phases << i << ";" << info_v[i];
	}

	save_file_phases.close();

	char path_save_jobs[] = "../data/jobs.csv";

	fstream save_file_jobs;
	save_file_jobs.open(path_save_jobs, fstream::out);

	save_file_jobs << "id;" << "name" << endl; 

	for (int i = 0; i < filename_v.size(); ++i){
		save_file_jobs << i << ";" << filename_v[i] << endl;;
	}

	save_file_jobs.close();


	return 0;
}
