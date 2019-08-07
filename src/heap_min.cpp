#include "heap_min.h"


/* Private */

void Heap_min::heapifydown(unsigned int index = 0) { /* O(lg n) */
    while ((left(index) < size && this->heap[index]->getStart() > this->heap[left(index)]->getStart()) || (right(index) < size && this->heap[index]->getStart() > this->heap[right(index)]->getStart())) {
        if (right(index) < size && this->heap[right(index)]->getStart() < this->heap[left(index)]->getStart()) {
            swap(index, right(index));
            index = right(index);
        } else {
            swap(index, left(index));
            index = left(index);
        }
    }
}

void Heap_min::heapifyup(unsigned int index) { /* O(lg n) */
    while (index > 0 && this->heap[index]->getStart() < this->heap[parent(index)]->getStart()) {
        swap(index, parent(index));
        index = parent(index);
    }
}

unsigned int Heap_min::left(unsigned int parent) { /* O(1) */
    return 2 * parent + 1;
}

unsigned int Heap_min::parent(unsigned int child) { /* O(1) */
    return (child - 1) / 2;
}

unsigned int Heap_min::right(unsigned int parent) { /* O(1) */
    return 2 * parent + 2;
}

void Heap_min::swap(unsigned int i, unsigned int j) { /* O(1) */
    Node *swap = this->heap[i];
    this->heap[i] = this->heap[j];
    this->heap[j] = swap;
}

/* Public */

Heap_min::Heap_min(unsigned int max) { /* O(1) */
    this->size = 0;
    this->max = max;
    this->heap = new Node*[max];
}

Heap_min::~Heap_min() { /* O(1) */
    for (int i = 0; i < this->max; ++i)
        delete[] this->heap[i];
}

/* Extract-min*/
Node* Heap_min::extract() { /* O(lg n) */
    if (isEmpty() == false) {
        Node *min = this->heap[0];
        this->heap[0] = this->heap[this->size - 1];
        this->size = this->size - 1;
        heapifydown();
        return min;
    }
    cout << "!PANIC - the heap is empty" << endl;
    return (Node*) 0;
}

Node* Heap_min::top(){ /* O(1) */
    if (isEmpty() == false) {
        return this->heap[0];
    }
    cout << "!PANIC - the heap is empty" << endl;
    return (Node*) 0;
}


unsigned int Heap_min::getSize() { /* O(1) */
    return this->size;
}

bool Heap_min::insert(Node *no) { /* O(lg n) */
    if (this->size < this->max) {
        this->heap[this->size] = no;
        heapifyup(this->size);
        this->size++;
        return true;
    }
    cout << "!PANIC - the heap is full" << endl;
    return false;
}

bool Heap_min::isEmpty() { /* O(1) */
    return this->size == 0;
}