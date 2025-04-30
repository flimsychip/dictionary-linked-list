#ifndef LINKEDLISTH
#define LINKEDLISTH

#include "Node.h"

struct LinkedList {
   private:
      int listSize;
      Node* head;
      Node* tail;
      
      void setSize(int num);
      void setHead(Node* head);
      void setTail(Node* tail);
      
   public:
      LinkedList();
      LinkedList(std::string str);
      ~LinkedList();
      
      int size() const;
      Node* getHead() const;
      Node* getTail() const;
      
      void push_back(std::string str);
      void push_back(Node* node);
      void clear();
      Node* deleteWord(Node* node);
      Node* insert_before(std::string str, Node* node);
      void mergeDicts(LinkedList* list);
      void mergeSort();
      void mergeSort(LinkedList* list);
      
      void operator+=(LinkedList &list);
};

#endif
