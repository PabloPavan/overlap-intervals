#include "node.h"
#include <vector>
/* Private */


/* Public */

Node::Node(int phase, int job, int day, long int start, long int end) { /* O(1) */
    this->phase.push_back(phase);
    this->job.push_back(job);
    this->day.push_back(day);
    this->start = start;
    this->end = end;
}

Node::Node(int phase1, vector <int> phase2, int job1, vector <int> job2, int day1, vector <int> day2, long int start, long int end) { /* O(1) */
    this->phase.push_back(phase1);
    for(int i = 0; i < phase2.size(); ++i)
        this->phase.push_back(phase2[i]);

    this->job.push_back(job1);
    for(int i = 0; i < job2.size(); ++i)
        this->job.push_back(job2[i]);

    this->day.push_back(day1);
    for(int i = 0; i < day2.size(); ++i)
        this->day.push_back(day2[i]);

    this->start = start;
    this->end = end;
}


void Node::destroy() { /* O(n lg n) */
    delete this;
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

