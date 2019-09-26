#include "../include/heap_min.h"


/* Private */

void Heap_min::heapifydown(unsigned int index = 0) { /* O(lg n) */
	// while (((left(index) < size && get<0>(this->heap[index]) < get<0>(this->heap[left(index)])) ||
		// (right(index) < size && get<0>(this->heap[index]) < get<0>(this->heap[right(index)])) ||
		// (left(index) < size && get<1>(this->heap[index])->getStart() < get<1>(this->heap[left(index)])->getStart()) || 
		// (right(index) < size && get<1>(this->heap[index])->getStart() < get<1>(this->heap[right(index)])->getStart())) || 
		// (((left(index) < size && get<1>(this->heap[index])->getStart() == get<1>(this->heap[left(index)])->getStart()) && (get<1>(this->heap[index])->getEnd() > get<1>(this->heap[left(index)])->getEnd())) || 
		// ((right(index) < size && get<1>(this->heap[index])->getStart() == get<1>(this->heap[right(index)])->getStart()) && (get<1>(this->heap[index])->getEnd() > get<1>(this->heap[right(index)])->getEnd())))) {

	while(left(index) < size){

		if (right(index) < size && get<0>(this->heap[right(index)]) < get<0>(this->heap[left(index)])){
			swap(index, right(index));
			index = right(index);
		}else if(right(index) < size && get<1>(this->heap[right(index)])->getStart() < get<1>(this->heap[left(index)])->getStart()){
			swap(index, right(index));
			index = right(index);
		}else if(right(index) < size && get<1>(this->heap[right(index)])->getStart() == get<1>(this->heap[left(index)])->getStart() && get<1>(this->heap[right(index)])->getEnd() < get<1>(this->heap[left(index)])->getEnd()){
			swap(index, right(index));
			index = right(index);
		}else{
			swap(index, left(index));
			index = left(index);
		}

	}
}

void Heap_min::heapifyup(unsigned int index) { /* O(lg n) */
	while (((index > 0) && get<0>(this->heap[index]) < get<0>(this->heap[parent(index)]) ||
		((index > 0) && get<0>(this->heap[index]) == get<0>(this->heap[parent(index)]) &&
		(index > 0) && get<1>(this->heap[index])->getStart() < get<1>(this->heap[parent(index)])->getStart())) ||
		((index > 0) && get<0>(this->heap[index]) == get<0>(this->heap[parent(index)]) &&
		(index > 0) && (get<1>(this->heap[index])->getStart() == get<1>(this->heap[parent(index)])->getStart()) && 
		(get<1>(this->heap[index])->getEnd() < get<1>(this->heap[parent(index)])->getEnd()))) {
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
	tuple<long int, Node*> swap = this->heap[i];
	this->heap[i] = this->heap[j];
	this->heap[j] = swap;
}

/* Public */

Heap_min::Heap_min() { /* O(1) */
	this->size = 0;
	// this->max = max;
	// this->heap = new Node*[max];
}

Heap_min::~Heap_min() { /* O(1) */
	//delete[] this->heap;
}

/* Extract-min*/
tuple<long int, Node*> Heap_min::extract() { /* O(lg n) */
	if (isEmpty() == false) {
		tuple<long int, Node*> min = this->heap[0];
		this->heap[0] = this->heap[this->size - 1];
		this->size = this->size - 1;
		heapifydown();
		return min;
	}
	#ifdef LOG
		L_(lerror) << "In extract function on Heap_min class - the heap is empty";
	#endif

	return make_tuple(0,(Node*)0);
}

tuple<long int, Node*> Heap_min::top(){ /* O(1) */
	if (isEmpty() == false) {
		return this->heap[0];
	}
	#ifdef LOG
		L_(lerror) << "In top function on Heap_min class - the heap is empty";
	#endif
	return make_tuple(0,(Node*)0);
}

tuple<long int, Node*> Heap_min::print(int index){ /* O(1) */
	if (isEmpty() == false) {
		return this->heap[index];
	}
	#ifdef LOG
		L_(lerror) << "In top function on Heap_min class - the heap is empty";
	#endif
	return make_tuple(0,(Node*)0);
}


unsigned int Heap_min::getSize() { /* O(1) */
	return this->size;
}

bool Heap_min::insert(tuple<long int,Node*> _tuble){ /* O(lg n) */
 	
 	cout << "I " << get<0>(_tuble) << endl;
	this->heap.emplace_back(_tuble);
	//this->heap[this->size] = no;
	heapifyup(this->size);
	this->size++;
	return true;
	
	// #ifdef LOG
	// 	L_(lerror) << "In insert function on Heap_min class - the heap is full";
	// #endif
	// return false;
}

bool Heap_min::isEmpty() { /* O(1) */
	return this->size == 0;
}