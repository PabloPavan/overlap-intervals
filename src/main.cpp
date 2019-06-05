#include "node.h"
#include "heap.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;


int main(int argc, char const *argv[])
{
	/* code */

	// Heap h(5);
	// cout << "size " << h.getSize() << endl;
	// // phase, job, day, start, end
	// Node n(1,1,1,2,100);

	// h.insert(&n);
    
 //    cout << "size " << h.getSize() << endl;

	// Node n2(2,2,1,1,120);

	// h.insert(&n2);

	// cout << "size " << h.getSize() << endl;

	// Node* nx = h.extract();

	// cout << "phase " << nx->getPhase() << endl;
	// cout << "job " << nx->getJob() << endl;
	// cout << "day " << nx->getDay() << endl;
	// cout << "start " << nx->getStart() << endl;
	// cout << "end " << nx->getEnd() << endl;

	// cout << "size " << h.getSize() << endl;



	//FILE *file = fopen("data/interval.csv", "r");
	ifstream infile("../data/intervals.csv");
	map<string, int> mymap;

	string cabecalho;
	string word;
	string filename;
	unsigned int jobid;
	unsigned int uid;
	unsigned int runtime;
	unsigned int start_time;
	unsigned int end_time;
	unsigned int exec;
	unsigned int file;
	unsigned int interval_id;
	float start;
	float end;
	string info;
	unsigned int X1_access_count,X1_access_size,read_bytes,write_bytes;


getline(infile, cabecalho);
while(getline(infile, word, ';')){
	filename = word;
	cout << "filename: " << filename << endl ;

	getline(infile, word, ';');
	jobid = stoi(word.c_str());
	cout << "jobid: " << jobid << endl ;

	getline(infile, word, ';');
	uid = stoi(word.c_str());
	cout << "uid: " << uid << endl ;

	getline(infile, word, ';');
	runtime = stoi(word.c_str());
	cout << "runtime: " << runtime << endl ;

	getline(infile, word, ';');
	start_time = stoi(word.c_str());
	cout << "start_time: " << start_time << endl ;

	getline(infile, word, ';');
	end_time = stoi(word.c_str());
	cout << "end_time: " << end_time << endl ;

	getline(infile, word, ';');
	cout << "exec: " << exec << endl ;

	getline(infile, word, ';');
	file = stoi(word.c_str());
	cout << "file: " << file << endl ;

	getline(infile, word, ';');
	interval_id = stoi(word.c_str());
	cout << "interval_id: " << interval_id << endl ;

	getline(infile, word, ';');
	start = stof(word.c_str());
	cout << "start: " << start << endl ;

	getline(infile, word, ';');
	end = stof(word.c_str());
	cout << "end: " << end << endl ;

	getline(infile, word, ';');
	info = word;
	cout << "info: " << info << endl ;

	getline(infile, word, ';');
	X1_access_count = stoi(word.c_str());
	cout << "X1_access_count: " << X1_access_count << endl ;

	getline(infile, word, ';');
	X1_access_size = stoi(word.c_str());
	cout << "X1_access_size: " << X1_access_size << endl ;

	getline(infile, word, ';');
	read_bytes = stoi(word.c_str());
	cout << "read_bytes: " << read_bytes << endl ;

	getline(infile, word);
	write_bytes = stoi(word.c_str());
	cout << "write_bytes: " << write_bytes << endl ;

}
// cout << "filename: " << filename << endl ; 
// getline(infile, filename, ';');
// cout << "filename: " << filename << endl ; 

    // getline(file, nome, ',') ;
    // cout << "User: " << nome << " " ;

    // getline(file, idade, ',') ;
    // cout << "Idade: " << idade << " "  ; 

    // getline(file, genero);
    // cout << "Sexo: " <<  genero<< " "  ;



		// if(fgetc(f) == 10){
		// 	//fprintf(h, "\n");
		// 	break;
		// }
		// else if(i != 0)
		// 	cout << "oi" << endl;
			//fprintf(h, ",");

		//mymap.insert(pair<string,int>(word, i));
	//cout <<  word << endl;
	

	return 0;
}