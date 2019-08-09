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
    Node(vector <Node*> nexts, vector <Node*> nodes, long int start, long int end);
    Node(vector <Node*> nodes, long int start, long int end);
    Node(Node* nexts, Node* nodes, long int start, long int end);
    Node(Node* nodes, long int start, long int end);
    Node(vector <int> phase, vector <int> job, vector <int> day, long int start, long int end);
    
    void destroy();
    vector<int> getPhase();
    vector<int> getJob();
    vector<int> getDay();
    long int getStart();
    long int getEnd();


};
#endif	/* NODE_H */