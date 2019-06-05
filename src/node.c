#include "node.h"
/* Private */

/* Post-order destroy */
void Node::destroy(Node* node) { /* O(n lg n) */
    if (node->left != 0)
        destroy(node->left);

    if (node->right != 0)
        destroy(node->right);

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

    this->leaf = true;
    this->left = (Node *) 0;
    this->right = (Node *) 0;
}

/* For inner nodes */
// Node::Node(Node* left, Node* right) { /* O(1) */
//     this->phase = '\0';
//     this->start = left->start + right->start;
//     this->leaf = false;
//     this->left = left;
//     this->right = right;
// }

/* Called by root */
void Node::destroy() { /* O(n lg n) */
    if (this->left != 0)
        destroy(this->left);
    if (this->right != 0)
        destroy(this->right);
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


Node* Node::getLeft() { /* O(1) */
    return this->left;
}

Node* Node::getRight() { /* O(1) */
    return this->right;
}

bool Node::isLeaf() { /* O(1) */
    return this->leaf;
}