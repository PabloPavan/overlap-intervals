#ifndef UTILS_H
#define	UTILS_H

#include "node.h"
#include "heap.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <set>
#include <stack>

using namespace std;

static bool first_write = false;
static long int last_end = 0;


struct  statistics_data{
	int  times;
	char *values;
};

int idx_find(char *word, vector<char*>&v);
int min_find(vector<Node*>&v);
Node* back_pop(vector<Node*>&v);
vector<int> remove_duplicates(vector<Node*>&v, vector<int> (Node::*functionPtr)());
void dump_file(int long new_end, vector<Node*>&v);
void dump_dict(const char path[], vector<char*>&v);
statistics_data extract_statistics(vector<int> &v);
//void dump_statistics(vector<Node*>&v);
void create_intervals_without_next(vector<Node*> nodes);

#endif