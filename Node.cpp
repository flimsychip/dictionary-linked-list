#include "Node.h"

Node::Node() {
   this->word = "";
   this->prev = nullptr;
   this->next = nullptr;
}

Node::Node(std::string str) {
   this->word = str;
   this->prev = nullptr;
   this->next = nullptr;
}

std::string Node::getWord() const {
   return this->word;   
}

Node* Node::getPrev() const {
   return this->prev;   
}

Node* Node::getNext() const {
   return this->next;   
}

void Node::setWord(std::string str) {
   this->word = str;
}

void Node::setPrev(Node* prevPtr) {
   this->prev = prevPtr;   
}

void Node::setNext(Node* nextPtr) {
   this->next = nextPtr;   
}

bool operator==(const Node &left, const Node &right) {
   return left.getWord() == right.getWord();
}

bool operator==(const Node &node, const std::string str) {
   return node.getWord() == str;
}

bool operator==(const std::string str, const Node &node) {
   return node.getWord() == str;
}

bool operator!=(const Node &left, const Node &right) {
   return !(left == right);
}

bool operator!=(const Node &node, const std::string str) {
   return !(node == str);
}

bool operator!=(const std::string str, const Node &node) {
   return !(node == str);
}

bool operator<(const Node &left, const Node &right) {
   return left.getWord() < right.getWord();   
}

bool operator<(const Node &node, const std::string str) {
   return node.getWord() < str;   
}

bool operator<(const std::string str, const Node &node) {
   return str < node.getWord();   
}

bool operator>(const Node &left, const Node &right) {
   return right < left;  
}

bool operator>(const Node &node, const std::string str) {
   return str < node.getWord();   
}

bool operator>(const std::string str, const Node &node) {
   return node.getWord() < str;   
}

bool operator<=(const Node &left, const Node &right) {
   return !(left > right);   
}

bool operator<=(const Node &node, const std::string str) {
   return !(node > str);   
}

bool operator<=(const std::string str, const Node &node) {
   return !(str > node);   
}

bool operator>=(const Node &left, const Node &right) {
   return !(left < right);   
}

bool operator>=(const Node &node, const std::string str) {
   return !(node < str);   
}

bool operator>=(const std::string str, const Node &node) {
   return !(str < node);   
}
