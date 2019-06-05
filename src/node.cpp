#include "node.h"
/* Private */

/* Post-order destroy */
void Node::destroy(Node* node) { /* O(n lg n) */
    delete node;
}

/* Public */

/* For leaf nodes */
Node::Node(int phase, int job, int day, unsigned int start, unsigned int end) { /* O(1) */
    this->phase = phase;
    this->job = job;
    this->day = day;
    this->start = start;
    this->end = end;
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

unsigned int Node::getStart() { /* O(1) */
    return this->start;
}

unsigned int Node::getEnd() { /* O(1) */
    return this->end;
}

