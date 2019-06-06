#include "node.h"
/* Private */


/* Public */

Node::Node(int phase, int job, int day, long int start, long int end) { /* O(1) */
    this->phase = phase;
    this->job = job;
    this->day = day;
    this->start = start;
    this->end = end;
}

void Node::destroy() { /* O(n lg n) */
    delete this;
}

int Node::getPhase() { /* O(1) */
    return this->phase;
}

int Node::getJob() { /* O(1) */
    return this->job;
}

int Node::getDay() { /* O(1) */
    return this->day;
}

long int Node::getStart() { /* O(1) */
    return this->start;
}

long int Node::getEnd() { /* O(1) */
    return this->end;
}

