#ifndef HEAP_H
#define	HEAP_H

/* Min-Heap */

class Heap {
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
    Heap(unsigned int max);
    ~Heap();
    /* Extract-min*/
    Node* extract();
    unsigned int getSize();
    bool insert(Node *no);
    bool isEmpty();
};

#endif	/* HEAP_H */