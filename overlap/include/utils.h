#ifndef UTILS_H
#define	UTILS_H

#include "logger.h"
#include "node.h"
#include "heap_min.h"
#include "heap_max.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <sys/stat.h>

#define BUFFER_SIZE 4096

using namespace std;

static bool first_write = false;
static long int last_end = 0;

extern string output_path;

struct statistics_data{
	int  times;
	char *values;
	statistics_data(int times, char *values) : times(times), values(values) {}
};

unsigned int read_file(Heap_min *h, string path, long int day, vector<string>&filename_v, vector<string>&info_v);
int idx_find(string word, vector<string>&v);
int min_find(const vector<Node*>&v);
string front_pop(list<string>&l);
inline void remove_duplicates(Node* node, const vector<int>& (Node::*functionPtr)(), vector<int>&v);
inline bool file_exists (const char filename[]);
void dump_file(int long new_end, Node* node);
void dump_dict(string path, const vector<string>&v);
statistics_data extract_statistics(const vector<int> &v);
void create_intervals_without_next(Heap_min *heap_min, const vector<Node*>& _nodes);

#endif