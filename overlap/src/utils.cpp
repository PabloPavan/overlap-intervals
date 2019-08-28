#include "../include/utils.h"

/**
 * Read the input file
 * 
 * @param heap pointer, index of the vector that contains the input files' path, ref vector filename, and ref vector info
 * @return the heap's size
 */


unsigned int read_file(Heap_min *heap_min, string path, long int day, vector<string>&filename_v, vector<string>&info_v){

	const long int epoch_time = 1325376000;
	char line[BUFFER_SIZE];
	char delim[] = ";";

	#ifdef LOG
		L_(ldebug) << "read file: " << path;
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

		heap_min->insert(new Node(idx_find(info, info_v),idx_find(filename, filename_v),day,start_,end_));

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
 * @param ref of the nodes vector and functions' ref of class Node
 * @return a vector with with unique values
 */

vector<int> remove_duplicates(Node* node, vector<int> (Node::*functionPtr)()){
	vector<int> vec;
	set<int> s;

	vector<int> u = (node->*functionPtr)();
	for(int j = 0; j < u.size(); ++j)
		s.insert(u[j]);
	
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

statistics_data extract_statistics(vector<int> &v){

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


void dump_file(int long new_end, Node* node){


	string path_save = output_path+"final.csv";

	vector<int> jobs_vec = remove_duplicates(node, &Node::getJob);
	vector<int> phases_vec = remove_duplicates(node, &Node::getPhase);
	vector<int> days_vec = remove_duplicates(node, &Node::getDay);

	statistics_data jobs = extract_statistics(jobs_vec);
	statistics_data phases = extract_statistics(phases_vec);
	statistics_data days = extract_statistics(days_vec);


	if(!first_write){

		fstream save_file;
		save_file.open(path_save, fstream::out);

		save_file << "start;" << "end;" << "duration;" << "phases;" << "nphases;" << "jobs;" << "njobs;" << "days;" << "ndays" << endl; 

		save_file.close();

		first_write = true;
		last_end = new_end;
	}

	fstream save_file;
	save_file.open(path_save, fstream::app);

	if (node->getStart() > last_end){
		#ifdef LOG
			L_(ldebug) << "save - " << "start: " << last_end << " end: " << node->getStart()  << " duration: " << node->getStart()-last_end << " phases: " << -1 << " jobs: " << -1 << " days: " << days.values;
		#endif
		save_file <<  last_end <<";"<< node->getStart() <<";"<< node->getStart()-last_end <<";"<< -1 <<";"<< 0 <<";"<< -1 <<";"<< 0 <<";"<< days.values <<";"<< days.times << endl;
		
	}
	
	last_end = new_end;

	#ifdef LOG
		L_(ldebug) << "save - " <<  "start: " << node->getStart() << " end: " << new_end << " duration: " << new_end-node->getStart() << " phases: " << phases.values << " jobs: " << jobs.values << " days: " << days.values;
	#endif 

	save_file <<  node->getStart() <<";"<< new_end <<";"<< new_end-node->getStart() <<";"<< phases.values <<";"<< phases.times <<";"<< jobs.values <<";"<< jobs.times <<";"<< days.values <<";"<< days.times << endl;
	
	save_file.close();

	string folder = output_path+"phases_"+phases.values+".csv";

	if(!file_exists(folder.c_str())){
		#ifdef LOG
			L_(ldebug) << "Cannot open "<< folder << ", file does not exist. Creating new file..";
		#endif 
		save_file.open(folder, ios::out | ios::trunc);
		save_file << "start;" << "end;" << "duration;" << "jobs;" << "njobs;" << "days;" << "ndays" << endl;
		save_file << node->getStart() <<";"<< new_end <<";"<< new_end-node->getStart() <<";"<< jobs.values <<";"<< jobs.times <<";"<< days.values <<";"<< days.times << endl;
		save_file.close();	
	}else{
		save_file.open(folder, ios::app);
		#ifdef LOG
			L_(ldebug) << "Success "<<  folder <<" found.";
		#endif 
		save_file << node->getStart() <<";"<< new_end <<";"<< new_end-node->getStart() <<";"<< jobs.values <<";"<< jobs.times <<";"<< days.values <<";"<< days.times << endl;
		save_file.close();
	}

	for (int i = 0; i < phases_vec.size(); ++i){

		string folder = output_path+"patterns_"+to_string(phases_vec[i])+".csv";

		if(!file_exists(folder.c_str())){
			#ifdef LOG
				L_(ldebug) << "Cannot open "<< folder << ", file does not exist. Creating new file..";
			#endif 
			save_file.open(folder, ios::out | ios::trunc);
			save_file << "start;" << "end;" << "duration;" << "jobs;" << "njobs;" << "days;" << "ndays" << endl;
			save_file << node->getStart() <<";"<< new_end <<";"<< new_end-node->getStart() <<";"<< jobs.values <<";"<< jobs.times <<";"<< days.values <<";"<< days.times << endl;
			save_file.close();	
		}else{
			save_file.open(folder, ios::app);
			#ifdef LOG
				L_(ldebug) << "Success "<<  folder <<" found.";
			#endif 
			save_file << node->getStart() <<";"<< new_end <<";"<< new_end-node->getStart() <<";"<< jobs.values <<";"<< jobs.times <<";"<< days.values <<";"<< days.times << endl;
			save_file.close();
		}
	}


	free(jobs.values);
	free(phases.values);
	free(days.values);

}

/**
 * Saving a file with the vector of dict
 *
 * @param the file path and the vector
 */



void dump_dict(string path, vector<string>&v){
	#ifdef LOG
		L_(ldebug) << "dump dict file: " << path;
	#endif 
	fstream save_file;
	save_file.open(path, fstream::out);

	save_file << "id;" << "name" << endl; 

	for (int i = 0; i < v.size(); ++i){
		save_file << i << ";" << v[i] << endl;
	}
}

/**
 * Creating intervals that not have a next interval
 *
 * @param vector of the Nodes
 */
void create_intervals_without_next(Heap_min *heap_min, vector<Node*>& nodes){
	Node* n_current;
	Node* n_next;

	Heap_max *heap_max = new Heap_max(nodes.size()+1);

	for (int i = 0; i < nodes.size(); ++i)
		heap_max->insert(new Node(nodes[i], nodes[i]->getEnd(), nodes[i]->getStart()));
		

	#ifdef LOG
		L_(ldebug) << "max heap size: " << heap_max->getSize();
	#endif	
	while(!heap_max->isEmpty()){
		vector<Node*> nodes;
		vector<Node*> nexts;

		n_current = heap_max->extract();

		if(!heap_max->isEmpty()){

			nodes.push_back(n_current);

			if(!heap_max->isEmpty())
				while(n_current->getStart() == heap_max->top()->getStart()){
					nodes.push_back(heap_max->extract());
					if(heap_max->isEmpty())
						break;
				}

			if(!heap_max->isEmpty()){

				n_next = heap_max->extract();

				nexts.push_back(n_next);
				if(!heap_max->isEmpty())
					while(n_next->getStart() == heap_max->top()->getStart()){
						nexts.push_back(heap_max->extract());	
						if(heap_max->isEmpty())
							break;
					}

				int idx_min_nodes = min_find(nodes);
				int idx_min_nexts = min_find(nexts);

				if(nodes[idx_min_nodes]->getStart() > nexts[idx_min_nexts]->getStart()){
					
					heap_min->insert(new Node(nodes, nexts[idx_min_nexts]->getStart(), nodes[idx_min_nodes]->getStart()));
					
					#ifdef LOG
						L_(ldebug) << "new inside - start " << nexts[idx_min_nexts]->getStart() << " end " <<  nexts[idx_min_nexts]->getEnd();
					#endif
					heap_max->insert(new Node(nexts,nodes, nexts[idx_min_nexts]->getStart(),  nexts[idx_min_nexts]->getEnd()));
					
					for (int i = 0; i < nodes.size(); ++i){
						delete nodes[i];
					}

					for (int i = 0; i < nexts.size(); ++i){
						delete nexts[i];
					}
				}
			}else{
				#ifdef LOG
					L_(ldebug) << "else 1 inside - start " << nodes[0]->getStart() << " end " << nodes[0]->getEnd();
				#endif
				heap_min->insert(new Node(nodes, nodes[0]->getEnd(), nodes[0]->getStart()));
				for (int i = 0; i < nodes.size(); ++i){
					delete nodes[i];
				}
			}
		}else{
			#ifdef LOG
				L_(ldebug) << "else 2 inside - start " << n_current->getStart() << " end " << n_current->getEnd();
			#endif
			heap_min->insert(new Node(n_current, n_current->getEnd(), n_current->getStart()));
			delete n_current;

		}	
	}
	#ifdef LOG
		L_(ldebug) << "max size of heap after: " << heap_max->getSize();
	#endif	
		delete heap_max;
}