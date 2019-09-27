#include "../include/node.h"
/* Private */


/* Public */

Node::Node(int phase, int job, int day, long int start, long int end) { /* O(1) */

	this->phase.push_back(phase);
	this->job.push_back(job);
	this->day.push_back(day);
	this->start = start;
	this->end = end;
}

Node::~Node() { /* O(n lg n) */
   // delete this;
   // cout << "matei o node" << endl;
}

const vector <int>& Node::getPhase()  { /* O(1) */
	return this->phase;
}

const vector <int>& Node::getJob()  { /* O(1) */
	return this->job;
}

const vector <int>& Node::getDay()  { /* O(1) */
	return this->day;
}

long int Node::getStart() { /* O(1) */
	return this->start;
}

long int Node::getEnd() { /* O(1) */
	return this->end;
}

