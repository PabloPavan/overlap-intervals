#include "heap.h"
#include "node.h"

/* Private */

void Heap::heapifydown(unsigned int index = 0) { /* O(lg n) */
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

void Heap::heapifyup(unsigned int index) { /* O(lg n) */
    while (index > 0 && this->heap[index]->getStart() < this->heap[parent(index)]->getStart()) {
        swap(index, parent(index));
        index = parent(index);
    }
}

unsigned int Heap::left(unsigned int parent) { /* O(1) */
    return 2 * parent + 1;
}

unsigned int Heap::parent(unsigned int child) { /* O(1) */
    return (child - 1) / 2;
}

unsigned int Heap::right(unsigned int parent) { /* O(1) */
    return 2 * parent + 2;
}

void Heap::swap(unsigned int i, unsigned int j) { /* O(1) */
    Node *swap = this->heap[i];
    this->heap[i] = this->heap[j];
    this->heap[j] = swap;
}

/* Public */

Heap::Heap(unsigned int max) { /* O(1) */
    this->size = 0;
    this->max = max;
    this->heap = new Node*[max];
}

Heap::~Heap() { /* O(1) */
    delete this->heap;
}

/* Extract-min*/
Node* Heap::extract() { /* O(lg n) */
    if (isEmpty() == false) {
        Node *min = this->heap[0];
        this->heap[0] = this->heap[this->size - 1];
        this->size = this->size - 1;
        heapifydown();
        return min;
    }
    return (Node*) 0;
}

unsigned int Heap::getSize() { /* O(1) */
    return this->size;
}

bool Heap::insert(Node *no) { /* O(lg n) */
    if (this->size < this->max) {
        this->heap[this->size] = no;
        heapifyup(this->size);
        this->size++;
        return true;
    }
    return false;
}

bool Heap::isEmpty() { /* O(1) */
    return this->size == 0;
}