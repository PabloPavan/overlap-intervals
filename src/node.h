#ifndef NODE_H
#define	NODE_H

/* Binary tree node */

class Node {
private:
    char character;
    unsigned int index;
    bool leaf;
    Node *left, *right;
    /* Post-order destroy */
    void destroy(Node *node);
public:
    /* For leaf nodes */
    Node(char character, unsigned int index);
    /* For inner nodes */
    Node(Node *left, Node *right);
    /* Called by root */
    void destroy();
    char getCharacter();
    unsigned int getindex();
    Node* getLeft();
    Node* getRight();
    bool isLeaf();
};
#endif	/* NODE_H */