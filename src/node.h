#ifndef NODE_H
#define	NODE_H

/* Binary tree node */

class Node {
private:
    int phase;
    int job;
    int day;
    long int start;
    long int end;
    
public:
    
    Node(int phase, int job, int day, long int start, long int end);
    
    void destroy();
    int getPhase();
    int getJob();
    int getDay();
    long int getStart();
    long int getEnd();


};
#endif	/* NODE_H */