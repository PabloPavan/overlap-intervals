#include "node.h"
#include "heap.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <set>

using namespace std;

#define DUMP
#define BUFFER_SIZE 4096

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
 	for(int i = 0; i < v.size(); i++){
 		vector<int> u = (v[i]->*functionPtr)();
 		for(int j = 0; j < u.size(); j++)
			s.insert(u[j]);
 	}
 	vec.assign(s.begin(),s.end()); 
 	return vec;
}


long int min_find(vector<Node*>&v){
	// cout << "aaa ";
	// for(int i=0; i < v.size(); i++)
	// 	cout << v[i]->getEnd() <<  " ";
	// cout << endl;
    int min = 0;
    for(int i = 1; i < v.size(); i++)
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

void make_new_interval(int long new_end, vector<Node*>&v){
	// open csv final file and add new line
	// start and end 
	// phase and jobs sep by ,
	// day 

	// printf("%p\n xxx %p\n", v, &Node::getJob);
	// cout << endl << "jobs before: ";
	// for(int i=0; i < v.size(); i++)
	// 	cout << " " << v[i]->getJob();
	// cout << endl;
	vector<int> jobs_vec = remove_duplicates(v, &Node::getJob);
	// cout << "jobs after: ";
	// for(int i=0; i < jobs_vec.size(); i++)
	// 	cout << " " << jobs_vec[i];
	// cout << endl;
	// cout << "phases before: ";
	// for(int i=0; i < v.size(); i++)
	// 	cout << " " << v[i]->getPhase();
	// cout << endl;
	vector<int> phases_vec = remove_duplicates(v, &Node::getPhase);
	// 	cout << "phases after: ";
	// for(int i=0; i < phases_vec.size(); i++)
	// 	cout << " " << phases_vec[i];
	// cout << endl << endl;

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
	cout << "start: " << v[0]->getStart() << " end: " << new_end << " phases: " << phases; 
	// cout << " number of phases: " << number_of_phases  << " jobs: " << jobs << " number of jobs: " << number_of_jobs << endl << endl;
	cout << " jobs: " << jobs << endl << endl;
	#endif 

	free(jobs);
	free(phases);
	free(tmp);
}
	


int main(int argc, char const *argv[]){
	//long int epoch_time = 1325376000;
	long int epoch_time = 0;
	Heap *h;
	h = new Heap(30000);

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
		//strcpy (filename,token);
		strcpy(filename, token);
		filename = (char *) realloc(filename, (strlen(filename) + 1) * sizeof(char));
		//cout << filename << endl;
		token = strtok(NULL,delim);// joid 
		token = strtok(NULL,delim); //uid
		token = strtok(NULL,delim); //runtime
		token = strtok(NULL,delim); //start_time
		start_time = atoi(token);
		//cout << start_time << endl;
		token = strtok(NULL,delim); //end_time
		end_time = atoi(token);
		//cout << end_time << endl;
		token = strtok(NULL,delim); //exec
		token = strtok(NULL,delim); //file
		token = strtok(NULL,delim); //interval-id
		token = strtok(NULL,delim); //start
		start = atof(token);
		//printf("%f\n",  start);
		token = strtok(NULL,delim); //end
		end = atof(token);
		//printf("%f\n",  end);
		token = strtok(NULL,delim); //info
		strcpy(info, token);
		info = (char *) realloc(info, (strlen(info) + 1) * sizeof(char));
		//cout << info << endl;
		token = strtok(NULL,delim); //X1_access_count
		token = strtok(NULL,delim); //X1_access_size
		token = strtok(NULL,delim); //read_bytes
		token = strtok(NULL,delim); //write_bytes

		// convert the start_time, end_time, start and end to micro
		start  = start * 1000000; 
		start_time = start_time - epoch_time; 
		start_time = start_time * 1000000;
		long int starti = (long int) start;

		start_time = start_time + starti;

		end = end * 1000000;
		// end_time = end_time - epoch_time; 
		// end_time = end_time * 1000000;
		long int endi = (long int) end;
		end_time = start_time + (endi - starti);



		#ifdef DUMP
		cout << "[" << start_time << ", " << end_time << "]" << endl;
		#endif

		no  = new Node(idx_find(info, info_v),idx_find(filename, filename_v),1,start_time,end_time);
		h->insert(no);

		// free(filename);
		// free(info);
		
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

		#ifdef DUMP
		cout << "phase;  job;  day;  start;  end " << endl;
		cout << "[ ";
		for(int i = 0; i < n_current->getPhase().size(); ++i)
			cout << info_v[n_current->getPhase()[i]] << " ";
		cout << "] [ ";
		for(int i = 0; i < n_current->getJob().size(); ++i)
			cout << n_current->getJob()[i] << " ";
		cout << "] [ ";
		for(int i = 0; i < n_current->getDay().size(); ++i)
			cout << n_current->getDay()[i] << " ";
		cout << "]  " << n_current->getStart() << " " << n_current->getEnd() << endl;
		#endif

		if(!h->isEmpty()){
	 		nodes.push_back(n_current);

		 	do{
		 		//cout << "before if - nodes size = " << nodes.size() << " " << h->getSize() << endl;
		 		n_temp = h->extract();
				//cout << "after  if - nodes size = " << nodes.size() << " " << h->getSize() << endl;
		 		nodes.push_back(n_temp);
		 		//cout << "botei start " << n_temp->getStart() << " end " << n_temp->getEnd() << " " << info_v[n_temp->getPhase()[0]] << endl;
		 	}while(n_temp->getStart() == n_current->getStart());
			
		
			// ultimo elemento do nodes é o n_next node 
			n_next = back_pop(nodes);

		
		 	int min_end = min_find(nodes);
		 	cout << "min(end) start " << nodes[min_end]->getStart() << " end " << nodes[min_end]->getEnd() << " " << info_v[nodes[min_end]->getPhase()[0]] <<  endl;
			if(n_next->getStart() < nodes[min_end]->getEnd()){
				make_new_interval(n_next->getStart(), nodes);
				vector<int> gamb; gamb.push_back(1);
		 	 	no  = new Node(n_next->getPhase()[0], nodes, n_next->getJob()[0], nodes, 1, gamb, n_next->getStart(), nodes[min_end]->getEnd());
		 	 	cout << "novo1 start " << n_next->getStart() << " end " << nodes[min_end]->getEnd() <<  endl;
		 	 	h->insert(no);	 	 

			 	if(nodes[min_end]->getEnd() <= n_next->getEnd()){
			 	 	no  = new Node(n_next->getPhase()[0], n_next->getJob()[0], 1, nodes[min_end]->getEnd(), n_next->getEnd());
			 	 	cout << "novo2 start " << nodes[min_end]->getEnd() << " end " <<  n_next->getEnd() <<  " " << info_v[n_next->getPhase()[0]] <<  endl;
			 	 	h->insert(no);
			 	 }
		 	 	// cout << "xxc start " << no->getStart() << " end " << no->getEnd() <<  endl;
			}else{
		 		make_new_interval(nodes[min_end]->getEnd(), nodes);
		 		h->insert(n_next);
		 		cout << "else start " << n_next->getStart() << " end " <<  n_next->getEnd() <<  " " << info_v[n_next->getPhase()[0]] <<  endl;
			}

			// make_new_interval(new_end, nodes);
		
		}else{
			//cout << "else - nodes size = " << nodes.size() << endl;
			nodes.push_back(n_current);



			// for (int i = 0; i < nodes.size(); ++i){
			//  cout << nodes[i]->getStart() << endl;
			//  cout << nodes[i]->getEnd() << endl;
			// }
			

			make_new_interval(n_current->getEnd(), nodes);
		}

			 	
	}

	// n_current = h->extract();
	// vector<Node*> nodes;
	// nodes.push_back(n_current);
	// make_new_interval(n_current->getEnd(), nodes);




	#ifdef DUMP
	cout << "size of heap after: " << h->getSize() << endl;
	#endif

   
	return 0;
}
