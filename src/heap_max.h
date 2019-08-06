#ifndef HEAP_MAX_H
#define	HEAP_MAX_H

#include "node.h"
#include <iostream>

using namespace std;

/* Min-Heap */

class Heap_max {
private:
    /* Vector of pointers to Node */
    class Node **heap;
    unsigned int max, size;
    void heapifydown(unsigned int index);
    void heapifyup(unsigned int index);
    unsigned int left(unsigned int parent);
    unsigned int parent(unsigned int child);
    unsigned int right(unsigned int parent);
    void swap(unsigned int i, unsigned int j);
public:
    Heap_max(unsigned int max);
    ~Heap_max();
    /* Extract-min*/
    Node* extract();
    Node* top();
    unsigned int getSize();
    bool insert(Node *no);
    bool isEmpty();
};

#endif	/* HEAP_H */