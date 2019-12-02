#include "../include/utils.h"

/**
 * Read the input file
 * 
 * @param heap pointer, index of the vector that contains the input files' path, ref vector filename, and ref vector info
 * @return the heap's size
 */

unsigned int read_file(Heap_min *heap_min, string path, int64_t*min_timestamp){

	char line[BUFFER_SIZE];
	char delim[] = ";";

	#ifdef LOG
		L_(linfo) << "read file: " << path;
	#endif

	FILE *f = fopen(path.c_str(), "r");

	char *header = fgets(line, sizeof(line), f); // skip header

	while(fgets(line, sizeof(line), f)){

		char *token = strtok(line,delim);
		int64_t start_time = atol(token); // start_time
		token = strtok(NULL,delim); //end_time
		int64_t end_time = atol(token);
		token = strtok(NULL,delim); //duration
		token = strtok(NULL,delim); //phases
		string phases(token);
		token = strtok(NULL,delim); //nphases
		token = strtok(NULL,delim); //jobs
		string jobs(token);
		token = strtok(NULL,delim); //njobs
		token = strtok(NULL,delim); // days
		string days(token);
		token = strtok(NULL,delim); //ndays


		if (*min_timestamp == -1 || *min_timestamp > start_time)
			*min_timestamp = start_time;

		heap_min->insert(make_tuple(start_time,new Node(phases, jobs, days, start_time,end_time)));
		heap_min->insert(make_tuple(end_time,new Node(phases, jobs, days, start_time,end_time)));

	}
	
	fclose(f);
	#ifdef LOG
		L_(ldebug) << "min heap size: " << heap_min->getSize();
	#endif
	return heap_min->getSize();
}


/**
 * Removing values duplicates using a set
 * 
 * @param ref of the node and functions' ref of class Node
 * @return a vector with with unique values
 */

void remove_duplicates(const vector<Node*>& nodes, int (Node::*functionPtr)(), vector<int>&v){
	//unordered_set<int> s;
	set<int> s;
	//s.reserve(10000);
	for (int i = 0; i < nodes.size(); ++i){	
	//	vector<int> u = (nodes[i]->*functionPtr)();
	//	for(int j = 0; j < u.size(); ++j)
		s.insert((nodes[i]->*functionPtr)());
	}
	
	v.assign(s.begin(),s.end());
       	//sort(v.begin(), v.end());
}



/**
 * Creating statistics of a vector.
 * Creating a char with the values of the vector separated by comma
 * Count the number of values in the vector
 * the "11" value is the limit of the int size 
 * the "12" value is the limit of the int size + /0
 *
 * @param ref of the int vector
 * @return a struct with the number of values and the char
 */

inline statistics_data extract_statistics(const vector<int> &v){

	char *value = (char*) calloc(v.size() * 11 + 1, sizeof(char));
	char *tmp = (char*) calloc(12, sizeof(char));

	int i = 0;
	for (i = 0; i < v.size()-1; ++i){
		sprintf(tmp, "%d,", v[i]);
		strcat(value, tmp);
		bzero(tmp, 12);
	}
	sprintf(tmp, "%d", v[i++]);
	strcat(value, tmp);

	free(tmp);

	return statistics_data(i, value);
}

/**
 * Checking if file exists
 * If exist return true
 * 
 *
 * @param char of the path file
 * @return true if file exists, or false if file doesnt
 */

inline bool file_exists (const char filename[]) {
	struct stat buffer;   
	return (stat (filename, &buffer) == 0); 
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


void dump_file(int64_t start, int64_t end, const vector<Node*>& nodes){


	if(!first_write){

		main_file << "start;end;duration;phases;nphases;jobs;njobs;days;ndays" << "\n"; 
		first_write = true;
	
	}

	if (nodes.size() == 0){
		#ifdef LOG
			L_(ldebug) << "save - " << "start: " << start << " end: " << end  << " duration: " << end-start << " phases: " << -1 << " jobs: " << -1 << " days: " << -1;
		#endif
		main_file <<  start <<";"<< end <<";"<< end-start <<";"<< -1 <<";"<< 0 <<";"<< -1 <<";"<< 0 <<";" << -1 <<";"<< 0 << "\n";
		return;	
	}
	 
	vector<int> jobs_vec;
	vector<int> phases_vec;
	vector<int> days_vec;

	remove_duplicates(nodes, &Node::getJob, jobs_vec);
	remove_duplicates(nodes, &Node::getPhase, phases_vec);
	remove_duplicates(nodes, &Node::getDay, days_vec);

	statistics_data jobs = extract_statistics(jobs_vec);
	statistics_data phases = extract_statistics(phases_vec);
	statistics_data days = extract_statistics(days_vec);

	
	#ifdef LOG
		L_(ldebug) << "save - " <<  "start: " << start << " end: " << end << " duration: " << end-start << " phases: " << phases.values << " jobs: " << jobs.values << " days: " << days.values;
	#endif
	
	main_file <<  start <<";"<< end <<";"<< end-start <<";"<< phases.values <<";"<< phases.times <<";"<< jobs.values <<";"<< jobs.times <<";"<< days.values <<";"<< days.times << "\n";
	

	string folder = output_path+"phases_"+phases.values+".csv";

	fstream save_file;

	if(!file_exists(folder.c_str())){
		#ifdef LOG
			L_(ldebug) << "Cannot open "<< folder << ", file does not exist. Creating new file..";
		#endif 
		save_file.open(folder, ios::out | ios::trunc);
		save_file << "start;" << "end;" << "duration;" << "jobs;" << "njobs;" << "days;" << "ndays" << "\n";
		save_file << start <<";"<< end <<";"<< end-start <<";"<< jobs.values <<";"<< jobs.times <<";"<< days.values <<";"<< days.times << "\n";
		save_file.close();	
	}else{
		save_file.open(folder, ios::app);
		#ifdef LOG
			L_(ldebug) << "Success "<<  folder <<" found.";
		#endif 
		save_file << start <<";"<< end <<";"<< end-start <<";"<< jobs.values <<";"<< jobs.times <<";"<< days.values <<";"<< days.times << "\n";
		save_file.close();
	}

	// for (int i = 0; i < phases_vec.size(); ++i){

	// 	string folder = output_path+"patterns_"+to_string(phases_vec[i])+".csv";

	// 	if(!file_exists(folder.c_str())){
	// 		#ifdef LOG
	// 			L_(ldebug) << "Cannot open "<< folder << ", file does not exist. Creating new file..";
	// 		#endif 
	// 		save_file.open(folder, ios::out | ios::trunc);
	// 		save_file << "start;" << "end;" << "duration;" << "jobs;" << "njobs;" << "days;" << "ndays" << endl;
	// 		save_file << start <<";"<< end <<";"<< end-start <<";"<< jobs.values <<";"<< jobs.times <<";"<< days.values <<";"<< days.times << endl;
	// 		save_file.close();	
	// 	}else{
	// 		save_file.open(folder, ios::app);
	// 		#ifdef LOG
	// 			L_(ldebug) << "Success "<<  folder <<" found.";
	// 		#endif 
	// 		save_file << start <<";"<< end <<";"<< end-start <<";"<< jobs.values <<";"<< jobs.times <<";"<< days.values <<";"<< days.times << endl;
	// 		save_file.close();
	// 	}
	// }


	free(jobs.values);
	free(phases.values);
	free(days.values);
}

/**
 * Saving a file with the vector of dict
 *
 * @param the file path and the vector
 */



void dump_dict(string path, const vector<string>&v){
	#ifdef LOG
		L_(linfo) << "dump dict file: " << path;
	#endif 
	fstream save_file;
	save_file.open(path, fstream::out);

	save_file << "id;" << "name" << endl; 

	for (int i = 0; i < v.size(); ++i){
		save_file << i << ";" << v[i] << endl;
	}

	save_file.close();
}

/**
 * compare to nodes and return true if they are equals
 *
 * @param two nodes pointers that need compare
 * @return true if they are equals, false if they are not equals
 */

bool nodes_equals_compare(Node* lhs,  Node* rhs){
    return lhs->getStart() == rhs->getStart()
        && lhs->getEnd() == rhs->getEnd()
        && lhs->getPhase() == rhs->getPhase()
        && lhs->getJob() == rhs->getJob()
        && lhs->getDay() == rhs->getDay();
}
