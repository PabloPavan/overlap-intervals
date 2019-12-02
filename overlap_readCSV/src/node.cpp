#include "../include/node.h"
/* Private */


/* Public */

Node::Node(string phase, string job, string day, int64_t start, int64_t end) { /* O(1) */

	this->phase = phase;
	this->job = job;
	this->day = day;
	this->start = start;
	this->end = end;
}

Node::~Node() { /* O(n lg n) */

}

string Node::getPhase()  { /* O(1) */
	return this->phase;
}

string Node::getJob()  { /* O(1) */
	return this->job;
}

string Node::getDay()  { /* O(1) */
	return this->day;
}

int64_t Node::getStart() { /* O(1) */
	return this->start;
}

int64_t Node::getEnd() { /* O(1) */
	return this->end;
}

