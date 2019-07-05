#ifndef NODE_H
#define	NODE_H
#include <vector>
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
    Node(int phase1, vector <Node*> phase2, int job1, vector <Node*> job2, int day1, vector <int> day2, long int start, long int end);
    
    void destroy();
    vector<int> getPhase();
    vector<int> getJob();
    vector<int> getDay();
    long int getStart();
    long int getEnd();


};
#endif	/* NODE_H */