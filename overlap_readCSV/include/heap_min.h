#ifndef HEAP_MIN_H
#define	HEAP_MIN_H

#include "node.h"
#include "logger.h"
#include <iostream>
#include<tuple>

using namespace std;

#define SIZE_HEAP 100E6
/* Min-Heap */

class Heap_min {
private:
    /* Vector of pointers to Node */
   tuple<long int,Node*> *heap;
    unsigned int max, size = 0;
    bool compare(const tuple<int64_t, Node*>& A, const tuple<int64_t, Node*>& B);
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
    tuple<int64_t, Node*> extract();
    tuple<int64_t, Node*> getTop();
    unsigned int getSize();
    bool insert(tuple<int64_t, Node*>);
    bool isEmpty();
};

#endif	/* HEAP_H */
