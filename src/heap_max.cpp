#include "../include/heap_max.h"


/* Private */

void Heap_max::heapifydown(unsigned int index = 0) { /* O(lg n) */
	while ((left(index) < size && this->heap[index]->getStart() < this->heap[left(index)]->getStart()) || (right(index) < size && this->heap[index]->getStart() < this->heap[right(index)]->getStart())) {
		if (right(index) < size && this->heap[right(index)]->getStart() > this->heap[left(index)]->getStart()) {
			swap(index, right(index));
			index = right(index);
		} else {
			swap(index, left(index));
			index = left(index);
		}
	}
}

void Heap_max::heapifyup(unsigned int index) { /* O(lg n) */
	while (index > 0 && this->heap[index]->getStart() > this->heap[parent(index)]->getStart()) {
		swap(index, parent(index));
		index = parent(index);
	}
}

unsigned int Heap_max::left(unsigned int parent) { /* O(1) */
	return 2 * parent + 1;
}

unsigned int Heap_max::parent(unsigned int child) { /* O(1) */
	return (child - 1) / 2;
}

unsigned int Heap_max::right(unsigned int parent) { /* O(1) */
	return 2 * parent + 2;
}

void Heap_max::swap(unsigned int i, unsigned int j) { /* O(1) */
	Node *swap = this->heap[i];
	this->heap[i] = this->heap[j];
	this->heap[j] = swap;
}

/* Public */

Heap_max::Heap_max(unsigned int max) { /* O(1) */
	this->size = 0;
	this->max = max;
	this->heap = new Node*[max];
}

Heap_max::~Heap_max() { /* O(1) */
	for (int i = 0; i < this->max; ++i)
		delete this->heap[i];
}

/* Extract-min*/
Node* Heap_max::extract() { /* O(lg n) */
	if (isEmpty() == false) {
		Node *min = this->heap[0];
		this->heap[0] = this->heap[this->size - 1];
		this->size = this->size - 1;
		heapifydown();
		return min;
	}
	#ifdef LOG
		L_(lerror) << "In extract function on Heap_max class - the heap is empty";
	#endif
	return (Node*) 0;
}

Node* Heap_max::top(){ /* O(1) */
	if (isEmpty() == false) {
		return this->heap[0];
	}
	#ifdef LOG
		L_(lerror) << "In top function on Heap_max class - the heap is empty";
	#endif
	return (Node*) 0;
}


unsigned int Heap_max::getSize() { /* O(1) */
	return this->size;
}

bool Heap_max::insert(Node *no) { /* O(lg n) */
	if (this->size < this->max) {
		this->heap[this->size] = no;
		heapifyup(this->size);
		this->size++;
		return true;
	}
	#ifdef LOG
		L_(lerror) << "In insert function on Heap_max class - the heap is full";
	#endif
	return false;
}

bool Heap_max::isEmpty() { /* O(1) */
	return this->size == 0;
}