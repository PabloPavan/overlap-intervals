#ifndef NODE_H
#define	NODE_H
#include <vector>
#include <iostream>
using namespace std;
/* Binary tree node */

class Node {
private:
    vector<int> phase;
    vector<int> job;
    vector<int> day;
    long int start;
    long int end;
    
public:
    Node(int phase, int job, int day, long int start, long int end);

    ~Node();
    const vector<int>& getPhase();
    const vector<int>& getJob();
    const vector<int>& getDay();
    long int getStart();
    long int getEnd();

};
#endif	/* NODE_H */