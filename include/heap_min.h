#ifndef HEAP_MIN_H
#define	HEAP_MIN_H

#include "node.h"
#include "logger.h"
#include <iostream>

using namespace std;

/* Min-Heap */

class Heap_min {
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
    Heap_min(unsigned int max);
    ~Heap_min();
    /* Extract-min*/
    Node* extract();
    Node* top();
    unsigned int getSize();
    bool insert(Node *no);
    bool isEmpty();
};

#endif	/* HEAP_H */