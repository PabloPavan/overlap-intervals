#include "../include/utils.h"

/**
 * Read the input file
 * 
 * @param heap pointer, index of the vector that contains the input files' path, ref vector filename, and ref vector info
 * @return the heap's size
 */

unsigned int read_file(Heap_min *heap_min, string path, long int *min_timestamp, vector<string>&filename_v, vector<string>&info_v){

	//const long int epoch_time = 0;
	const long int epoch_time = 1325376000;
	char line[BUFFER_SIZE];
	char delim[] = ";";

	#ifdef LOG
		L_(linfo) << "read file: " << path;
	#endif

	FILE *f = fopen(path.c_str(), "r");

	char *header = fgets(line, sizeof(line), f); // skip header

	while(fgets(line, sizeof(line), f)){
		long int start_time;
		long int end_time;
		double start;
		double end;

		char *token = strtok(line,delim); //filename
		string filename(token);
		token = strtok(NULL,delim); //start_time
		start_time = atoi(token);
		token = strtok(NULL,delim); //end_time
		end_time = atoi(token);
		token = strtok(NULL,delim); //start
		start = atof(token);
		token = strtok(NULL,delim); //end
		end = atof(token);
		token = strtok(NULL,delim); //info
		token[strlen(token)-1] = '\0'; // remove \n
		string info(token);
		start  = start * 1000000; 
		start_time = start_time - epoch_time; 
		start_time = start_time * 1000000;
		long int starti = (long int) start;
		long int start_ = start_time + starti;
		end = end * 1000000;
		long int endi = (long int) end;
		long int end_ = start_ + (endi - starti);

		if (*min_timestamp == -1 || *min_timestamp > start_)
			*min_timestamp = start_;

		heap_min->insert(make_tuple(start_,new Node(idx_find(info, info_v),idx_find(filename, filename_v),day,start_,end_)));
		heap_min->insert(make_tuple(end_,new Node(idx_find(info, info_v),idx_find(filename, filename_v),day,start_,end_)));

	}
	
	fclose(f);
	#ifdef LOG
		L_(ldebug) << "min heap size: " << heap_min->getSize();
	#endif
	return heap_min->getSize();
}

/**
 * Creating a dict using vector
 * if word exists in vector return the index
 * if word doesn't exist create a new value in vector
 * 
 * @param word that needs be find, ref for the vector
 * @return the index of the vector that contains the word
 */

int idx_find(string word, vector<string>&v){
	int idx = 0;
	for (idx = 0; idx < v.size(); ++idx)
		if(v[idx].compare(word) == 0) 
			break;
	if(idx == v.size())
		v.push_back(word);	
	return idx;	
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
 * Return and remove a value from list of the strign
 * 
 * @param ref of the string list
 * @return the value of the front
 */

string front_pop(list<string>&l){
	string str;
	str = l.front();
	l.pop_front();
	return str;
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


void dump_file(int long start, int long end, const vector<Node*>& nodes){


	if(!first_write){

		main_file << "start;" << "end;" << "duration;" << "phases;" << "nphases;" << "jobs;" << "njobs;" << "days;" << "ndays" << "\n"; 
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
