#ifndef NODE_H
#define	NODE_H
#include <vector>
#include <iostream>
##include <string>
using namespace std;
/* Binary tree node */

class Node {
private:
    string phase;
    string job;
    string day;
    int64_t start;
    int64_t end;
    
public:
    Node(string phase, string job, string day, int64_t start, int64_t end);

    ~Node();
    string getPhase();
    string getJob();
    string getDay();
    int64_t getStart();
    int64_t getEnd();

};
#endif	/* NODE_H */
