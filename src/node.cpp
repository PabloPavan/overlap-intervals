#include "node.h"
/* Private */


/* Public */

Node::Node(int phase, int job, int day, long int start, long int end) { /* O(1) */
    this->phase.push_back(phase);
    this->job.push_back(job);
    this->day.push_back(day);
    this->start = start;
    this->end = end;
}



Node::Node(vector <Node*> nexts, vector <Node*> nodes, long int start, long int end) { /* O(1) */
    

    for(int i = 0; i < nexts.size(); ++i){
        vector<int> p1 = nexts[i]->getPhase();
        for (int j = 0; j < p1.size(); ++j)
            this->phase.push_back(p1[j]);

        vector<int> j1 = nexts[i]->getJob();
        for (int j = 0; j < j1.size(); ++j)
            this->job.push_back(j1[j]);
        
        vector<int> d1 = nexts[i]->getDay();
        for (int j = 0; j < d1.size(); ++j)
            this->day.push_back(d1[j]);
    }


    for(int i = 0; i < nodes.size(); ++i){
        vector<int> p2 = nodes[i]->getPhase();
        for (int j = 0; j < p2.size(); ++j)
            this->phase.push_back(p2[j]);

        vector<int> j2 = nodes[i]->getJob();
        for (int j = 0; j < j2.size(); ++j)
            this->job.push_back(j2[j]);
        
        vector<int> d2 = nodes[i]->getDay();
        for (int j = 0; j < d2.size(); ++j)
            this->day.push_back(d2[j]);
    }


    this->start = start;
    this->end = end;
}

Node::Node(vector <Node*> nodes, long int start, long int end) { /* O(1) */
    
    for(int i = 0; i < nodes.size(); ++i){
        vector<int> p2 = nodes[i]->getPhase();
        for (int j = 0; j < p2.size(); ++j)
            this->phase.push_back(p2[j]);

        vector<int> j2 = nodes[i]->getJob();
        for (int j = 0; j < j2.size(); ++j)
            this->job.push_back(j2[j]);
        
        vector<int> d2 = nodes[i]->getDay();
        for (int j = 0; j < d2.size(); ++j)
            this->day.push_back(d2[j]);
    }


    this->start = start;
    this->end = end;
}

Node::Node(vector <int> phase, vector <int> job, vector <int> day, long int start, long int end) { /* O(1) */
    
  
    for (int j = 0; j < phase.size(); ++j)
        this->phase.push_back(phase[j]);

    for (int j = 0; j < job.size(); ++j)
        this->job.push_back(job[j]);
    
    for (int j = 0; j < day.size(); ++j)
        this->day.push_back(day[j]);
    


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

