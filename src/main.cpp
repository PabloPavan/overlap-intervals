#include "node.h"
#include "heap.h"
#include <iostream>
#include <cstring>
#include <vector>


using namespace std;

#define DUMP
#define BUFFER_SIZE 2048

int idx_find(char *word, vector<char*>&v){
	int idx = 0;
	for (idx = 0; idx < v.size(); ++idx)
		if(strcmp(v[idx],word) == 0) 
			break;

	if(idx == v.size())
		v.push_back(word);	
	
	return idx;	

}
long int min_find(vector<Node*>&v){
    long int min = v[0]->getEnd();
    for(int i=0; i < v.size(); i++)
        if(v[i]->getEnd() < min)
        	min = v[i]->getEnd();

    return min;
}

Node* back_pop(vector<Node*>&v){
	Node * no;
	no = v.back();
	v.pop_back();
	return no;
}

void make_new_interval(int long new_end, vector<Node*>&v){
	// open csv final file and add new line
	// start and end 
	// phase and jobs sep by ,
	// day 
	char sep[] = ",";
	// char 
	char* jobs = (char*) calloc(1, sizeof(int));

	cout << (char[255]) v[0]->getJob() << endl;

	static_cast<char>(i);
	//(char) v[0]->getJob()

	cout << "asdada  " << jobs << endl;
	//strcat(jobs, sep);
	// for(int i=1; i < v.size(); i++){
		
	// 	//jobs+= (char*) v[0]->getJob();
	// }

	cout << "start: " << v[0]->getStart() << "end: " << new_end << "phases: " << endl;
}
	


int main(int argc, char const *argv[]){

	Heap h(30000);

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
		start_time = start_time * 1000000;
		long int starti = (long int) start;
		start_time = start_time + starti;
		end  = end * 1000000;
		end_time = end_time * 1000000;
		long int endi = (long int) end;
		end_time = end_time + endi;

		#ifdef DUMP
		printf("start_time: %ld\n",  start_time);
		printf("end_time: %ld\n",  end_time);
		#endif

		no  = new Node(idx_find(info, info_v),idx_find(filename, filename_v),1,start_time,end_time);
		h.insert(no);
		
	}
	fclose(f);

	#ifdef DUMP
	for (int i = 0; i < info_v.size(); ++i)
		printf("Index: %d = %s\n", i, info_v[i]);
	
	for (int i = 0; i < filename_v.size(); ++i)
		printf("Index: %d = %s\n", i, filename_v[i]);

	cout << "size of heap before: " << h.getSize() << endl;
	#endif

	Node* nx;
	Node* x;
	Node* next;

	//cout << "funciona " << h.extract()->getEnd() << endl;

	while(!h.isEmpty()){
		vector<Node*> nodes;
		long int new_end = 0;

		nx = h.extract();
		cout << "phase " << nx->getPhase() << endl;
		cout << "job " << nx->getJob() << endl;
		cout << "day " << nx->getDay() << endl;
		cout << "start " << nx->getStart() << endl;
		cout << "end " << nx->getEnd() << endl;

	 	nodes.push_back(nx);
	 	// for (int i = 0; i < nodes.size(); ++i)
			// printf("Index: %d = %ld\n", i, nodes[i]->getStart());
	 	do{
	 		x = h.extract();
	 		nodes.push_back(x); 
	 	}while(x->getStart() == nx->getStart());
		// ultimo elemento do nodes é o next node 
	 	next = back_pop(nodes);

	 	if(next->getStart() <= min_find(nodes)){
	 		new_end = next->getStart();
	 	}else{
	 		new_end = min_find(nodes);
	 	}
 	
 		make_new_interval(new_end, nodes);

	 	// }
		//nx->destroy();


	 }




	#ifdef DUMP
	cout << "size of heap after: " << h.getSize() << endl;
	#endif

   
	return 0;
}