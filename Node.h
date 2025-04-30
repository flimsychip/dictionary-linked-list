#ifndef NODEH
#define NODEH

#include <string>

struct Node {
   private:
      std::string word;
      Node* prev;
      Node* next;
      
   public:
      Node();
      Node(std::string str);
      
      std::string getWord() const;
      Node* getPrev() const;
      Node* getNext() const;
      
      void setWord(std::string str);
      void setPrev(Node* prevPtr);
      void setNext(Node* nextPtr);
};

bool operator==(const Node &left, const Node &right);
bool operator==(const Node &node, const std::string str);
bool operator==(const std::string str, const Node &node);

bool operator!=(const Node &left, const Node &right);
bool operator!=(const Node &node, const std::string str);
bool operator!=(const std::string str, const Node &node);

bool operator<(const Node &left, const Node &right);
bool operator<(const Node &node, const std::string str);
bool operator<(const std::string str, const Node &node);

bool operator>(const Node &left, const Node &right);
bool operator>(const Node &node, const std::string str);
bool operator>(const std::string str, const Node &node);

bool operator<=(const Node &left, const Node &right);
bool operator<=(const Node &node, const std::string str);
bool operator<=(const std::string str, const Node &node);

bool operator>=(const Node &left, const Node &right);
bool operator>=(const Node &node, const std::string str);
bool operator>=(const std::string str, const Node &node);

#endif
