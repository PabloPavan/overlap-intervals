#ifndef HEAP_MIN_H
#define	HEAP_MIN_H

#include "node.h"
#include "logger.h"
#include <iostream>
#include<tuple>

using namespace std;

/* Min-Heap */

class Heap_min {
private:
    /* Vector of pointers to Node */
    vector<tuple<long int,Node*>> heap;
    unsigned int size = 0;
    void heapifydown(unsigned int index);
    void heapifyup(unsigned int index);
    unsigned int left(unsigned int parent);
    unsigned int parent(unsigned int child);
    unsigned int right(unsigned int parent);
    void swap(unsigned int i, unsigned int j);
public:
    Heap_min();
    ~Heap_min();
    /* Extract-min*/
    tuple<long int, Node*> extract();
    tuple<long int, Node*> top();
    tuple<long int, Node*>  print(int index);
    unsigned int getSize();
    bool insert(tuple<long int, Node*>);
    bool isEmpty();
};

#endif	/* HEAP_H */