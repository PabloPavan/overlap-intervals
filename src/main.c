#include "node.h"
#include "heap.h"
#include <iostream>

using namespace std;


int main(int argc, char const *argv[])
{
	/* code */
	char a = 'a';
	cout << a << endl;
	Heap h(5);
	Node n(a,2);

	h.insert(&n);

	Node n2('b',1);

	h.insert(&n2);

	Node* nx = h.extract();

	cout << nx->getCharacter() << endl;




	return 0;
}