#include "node.h"

/* Private */

/* Post-order destroy */
void Node::destroy(Node* node) { /* O(n lg n) */
    if (node->left != 0)
        destroy(node->left);

    if (node->right != 0)
        destroy(node->right);

    delete node;
}

/* Public */

/* For leaf nodes */
Node::Node(char character, unsigned int frequency) { /* O(1) */
    this->character = character;
    this->frequency = frequency;
    this->leaf = true;
    this->left = (Node *) 0;
    this->right = (Node *) 0;
}

/* For inner nodes */
Node::Node(Node* left, Node* right) { /* O(1) */
    this->character = '\0';
    this->frequency = left->frequency + right->frequency;
    this->leaf = false;
    this->left = left;
    this->right = right;
}

/* Called by root */
void Node::destroy() { /* O(n lg n) */
    if (this->left != 0)
        destroy(this->left);
    if (this->right != 0)
        destroy(this->right);
}

char Node::getCharacter() { /* O(1) */
    return this->character;
}

unsigned int Node::getFrequency() { /* O(1) */
    return this->frequency;
}

Node* Node::getLeft() { /* O(1) */
    return this->left;
}

Node* Node::getRight() { /* O(1) */
    return this->right;
}

bool Node::isLeaf() { /* O(1) */
    return this->leaf;
}