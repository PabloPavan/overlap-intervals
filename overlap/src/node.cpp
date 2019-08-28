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

Node::Node(const vector <Node*>& nexts, const vector <Node*>& nodes, long int start, long int end) { /* O(1) */
	

	for(int i = 0; i < nodes.size(); ++i){

		vector<int> p = nodes[i]->getPhase();
		phase.reserve(p.size());
		phase.insert(phase.end(), p.begin(), p.end());

		vector<int> j = nodes[i]->getJob();
		job.reserve(j.size());
		job.insert(job.end(), j.begin(), j.end());

		vector<int> d = nodes[i]->getDay();
		day.reserve(d.size());
		day.insert(day.end(), d.begin(), d.end());

	}


	for(int i = 0; i < nexts.size(); ++i){

		vector<int> p = nexts[i]->getPhase();
		phase.reserve(p.size());
		phase.insert(phase.end(), p.begin(), p.end());

		vector<int> j = nexts[i]->getJob();
		job.reserve(j.size());
		job.insert(job.end(), j.begin(), j.end());

		vector<int> d = nexts[i]->getDay();
		day.reserve(d.size());
		day.insert(day.end(), d.begin(), d.end());

	}


	this->start = start;
	this->end = end;
}

Node::Node(const vector <Node*>& nodes, long int start, long int end) { /* O(1) */
	

	for(int i = 0; i < nodes.size(); ++i){

		vector<int> p = nodes[i]->getPhase();
		phase.reserve(p.size());
		phase.insert(phase.end(), p.begin(), p.end());

		vector<int> j = nodes[i]->getJob();
		job.reserve(j.size());
		job.insert(job.end(), j.begin(), j.end());

		vector<int> d = nodes[i]->getDay();
		day.reserve(d.size());
		day.insert(day.end(), d.begin(), d.end());

	}


	this->start = start;
	this->end = end;
}



Node::Node(Node* nexts, Node* nodes, long int start, long int end) { /* O(1) */
	

		this->phase = nodes->getPhase();
		this->job = nodes->getJob();
		this->day = nodes->getDay();


		vector<int> p = nexts->getPhase();
		vector<int> j = nexts->getJob();
		vector<int> d = nexts->getDay();

		phase.reserve(p.size());
		phase.insert(phase.end(), p.begin(), p.end());

		job.reserve(j.size());
		job.insert(job.end(), j.begin(), j.end());

		day.reserve(d.size());
		day.insert(day.end(), d.begin(), d.end());


	this->start = start;
	this->end = end;
}

Node::Node(Node* nodes, long int start, long int end) { /* O(1) */

	this->phase = nodes->getPhase();
	this->job = nodes->getJob();
	this->day = nodes->getDay();

	this->start = start;
	this->end = end;
}


Node::~Node() { /* O(n lg n) */
   // delete this;
   // cout << "matei o node" << endl;
}

vector <int> Node::getPhase() { /* O(1) */
	return this->phase;
}

vector <int> Node::getJob() { /* O(1) */
	return this->job;
}

vector <int> Node::getDay() { /* O(1) */
	return this->day;
}

long int Node::getStart() { /* O(1) */
	return this->start;
}

long int Node::getEnd() { /* O(1) */
	return this->end;
}

