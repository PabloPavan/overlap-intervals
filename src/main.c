#include "node.h"
#include "heap.h"
#include <iostream>

using namespace std;


int main(int argc, char const *argv[])
{
	/* code */

	Heap h(5);
	cout << "size " << h.getSize() << endl;
	// phase, job, day, start, end
	Node n(1,1,1,2,100);

	h.insert(&n);
    
    cout << "size " << h.getSize() << endl;

	Node n2(2,2,1,1,120);

	h.insert(&n2);

	cout << "size " << h.getSize() << endl;

	Node* nx = h.extract();

	cout << "phase " << nx->getPhase() << endl;
	cout << "job " << nx->getJob() << endl;
	cout << "day " << nx->getDay() << endl;
	cout << "start " << nx->getStart() << endl;
	cout << "end " << nx->getEnd() << endl;

	cout << "size " << h.getSize() << endl;




	return 0;
}