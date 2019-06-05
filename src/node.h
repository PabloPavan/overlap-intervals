#ifndef NODE_H
#define	NODE_H

/* Binary tree node */

class Node {
private:
    int phase;
    int job;
    int day;
    unsigned int start;
    unsigned int end;
    
    bool leaf;
    Node *left, *right;
    /* Post-order destroy */
    void destroy(Node *node);
public:
    /* For leaf nodes */
    Node(int phase, int job, int day, unsigned int start, unsigned int end);
    /* For inner nodes */
    Node(Node *left, Node *right);
    /* Called by root */
    void destroy();
    int getPhase();
    int getJob();
    int getDay();
    unsigned int getStart();
    unsigned int getEnd();
    Node* getLeft();
    Node* getRight();
    bool isLeaf();
};
#endif	/* NODE_H */