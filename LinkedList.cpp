#include "LinkedList.h"

void LinkedList::setSize(int num) {
   this->listSize = num;   
}

void LinkedList::setHead(Node* head) {
   this->head = head;   
}

void LinkedList::setTail(Node* tail) {
   this->tail = tail;
}

LinkedList::LinkedList() {
   this->setSize(0);
   this->setHead(nullptr);
   this->setTail(nullptr);
}

LinkedList::LinkedList(std::string str) {
   Node* temp = new Node(str);
   this->setSize(1);
   this->setHead(temp);
   this->setTail(temp);
}

LinkedList::~LinkedList() {
   this->clear();   
}

int LinkedList::size() const {
   return this->listSize;   
}

Node* LinkedList::getHead() const {
   return this->head;   
}

Node* LinkedList::getTail() const {
   return this->tail;   
}

void LinkedList::push_back(std::string str) {
   Node* temp = new Node(str);
   temp->setPrev(this->getTail());
   if(this->getTail() != nullptr) {   // list not empty
      this->getTail()->setNext(temp);
   } else {                           // list empty
      this->setHead(temp);
   }
   this->setTail(temp);
   this->listSize++;
}

void LinkedList::push_back(Node* node) {
   if(this->getTail() != nullptr) {    // list not empty
      node->setPrev(this->getTail());
      this->getTail()->setNext(node);
   } else {                            // list empty
      this->setHead(node);
   }
   node->setNext(nullptr);
   this->setTail(node);
   this->listSize++;
}

void LinkedList::clear() {
   Node* temp = this->getHead();
   Node* tempNext = nullptr;
   while(temp != nullptr) {
      tempNext = temp->getNext();
      delete temp;
      temp = tempNext;
   }
   this->setHead(nullptr);
   this->setTail(nullptr);
   this->setSize(0);
}

Node* LinkedList::deleteWord(Node* node) {
   if(node == this->getHead() || node == this->getTail()) {
      if(node == this->getHead()) {
         this->setHead(node->getNext()); 
         if(node->getNext()) { // in case list only contains 1 item
            (node->getNext())->setPrev(nullptr);
         }
      }
      if(node == this->getTail()) {
         this->setTail(node->getPrev());
         if(node->getPrev()) { // in case list only contains 1 item
            (node->getPrev())->setNext(nullptr);
         }
      }
   } else {
      (node->getPrev())->setNext(node->getNext());
      (node->getNext())->setPrev(node->getPrev());
   }
   
   this->listSize--;
   Node* temp = node->getNext();
   delete node;
   return temp;
}

Node* LinkedList::insert_before(std::string str, Node* node) {
   Node* temp = new Node(str);
   if(node == this->getHead()) {
      this->setHead(temp);
   } else {
      temp->setPrev(node->getPrev());
      (node->getPrev())->setNext(temp);
   }
   temp->setNext(node);
   node->setPrev(temp);
   this->listSize++;
   return temp;
}   

// NEEDS TO BE FIXED WHEN IM NOT BURNT OUT

void LinkedList::mergeDicts(LinkedList* list) {
   if(list->size() == 0) {
      return;   
   }
   
   int moveCount = 0;                                 // can't figure out a better way to do this :( note: still did not work
   Node* temp = list->getHead();
   Node* tempInner = this->getHead();
   
   for(int i = 0; i < list->size(); i++) {
      Node* temp2 = temp->getNext();
      for(int j = 0; j < this->size(); j++) {
         if(*temp == *tempInner) {                    // skips if word already in dict A
            list->setHead(temp2);
            delete temp;
            break;
         }
         
         if(*tempInner > *temp) {
            if(tempInner == this->getHead()) {        // basically insert_before() w/o creating a new node
               this->setHead(temp);   
               temp->setPrev(nullptr);
            } else {
               temp->setPrev(tempInner->getPrev());
               (tempInner->getPrev())->setNext(temp);
            }
            temp->setNext(tempInner);
            tempInner->setPrev(temp);
            list->setHead(temp2);
            moveCount++;
            break;
         }    
         tempInner = tempInner->getNext();
      }
      temp = temp2;
   }
   list->setSize(list->size() - moveCount);
   *this += *list;                                    // appends rest of dict B
}

void LinkedList::mergeSort() {
   this->mergeSort(this);
}

void LinkedList::mergeSort(LinkedList* list) {
   if(list->size() <= 1) {                            // base case
      return;
   }
   
   Node* temp = list->getHead();
   for(int i = 0; i < (list->size() / 2) - 1; i++) {
      temp = temp->getNext();
   }
   
   LinkedList* tempListA = new LinkedList;
   tempListA->setHead(list->getHead());
   tempListA->setTail(temp);
   tempListA->setSize(list->size() / 2);
   
   tempListA->getTail()->setNext(nullptr);
   
   LinkedList* tempListB = new LinkedList;
   tempListB->setHead(temp->getNext());
   tempListB->setTail(list->getTail());
   tempListB->setSize(list->size() - (list->size() / 2));
   
   tempListB->getHead()->setPrev(nullptr);
   
   this->mergeSort(tempListA);
   this->mergeSort(tempListB);
   
   list->setHead(nullptr);
   list->setTail(nullptr);
   list->setSize(0);
   list->mergeDicts(tempListA);
   list->mergeDicts(tempListB);
   
   delete tempListA;
   delete tempListB;
}

void LinkedList::operator+=(LinkedList &list) {
   if(list.getHead() == nullptr) {              // dict B empty
      return;
   }
      
   if(this->getTail() != nullptr) {             // make sure dict A not empty
      this->getTail()->setNext(list.getHead());
   } else {
      this->setHead(list.getHead());   
   }
   list.getHead()->setPrev(this->getTail());
   this->setTail(list.getTail());
   this->setSize(this->size() + list.size());
   
   list.setSize(0);
   list.setHead(nullptr);
   list.setTail(nullptr);
}

// --- BELOW FOR TESTING ONLY

// void LinkedList::mergeDicts(LinkedList* list) {
//    if(list->size() == 0) {
//       return;   
//    }
      
//    Node* temp = list->getHead();
//    Node* tempInner = this->getHead();
//    std::cout << temp->getWord() << " is B/list head" << std::endl;
   
//    for(int i = 0; i < list->size(); i++) {
//       Node* temp2 = temp->getNext();
//       for(int j = 0; j < this->size(); j++) {
//          std::cout << "in inner while" << std::endl;
//          if(*temp == *tempInner) {                    // skips if word already in dict A
//             list->setHead(temp2);
//             list->setSize(list->size() - 1);
//             delete temp;
//             break;
//          }
         
//          if(*tempInner > *temp) {
//             if(tempInner == this->getHead()) {        // basically insert_before() w/o creating a new node
//                this->setHead(temp);   
//                temp->setPrev(nullptr);
//             } else {
//                temp->setPrev(tempInner->getPrev());
//                (tempInner->getPrev())->setNext(temp);
//             }
//             temp->setNext(tempInner);
//             tempInner->setPrev(temp);
//             list->setHead(temp2);
//             list->setSize(list->size() - 1);
//             this->listSize++;
//             break;
//          }    
//          tempInner = tempInner->getNext();
//       }
//       std::cout << "after inner while" << std::endl;
//       temp = temp2;
//    }
//    std::cout << "after while" << std::endl;
//    *this += *list;                                    // appends rest of dict B
//    std::cout << "done merge" << std::endl;
// }

// void LinkedList::mergeSort(LinkedList* list) {
//    if(list->size() <= 1) {                            // base case
//       return;
//    }
   
//    Node* temp = list->getHead();
//    for(int i = 0; i < (list->size() / 2) - 1; i++) {
//       temp = temp->getNext();
//    }
   
//    LinkedList* tempListA = new LinkedList;
//    tempListA->setHead(list->getHead());
//    tempListA->setTail(temp);
//    std::cout << tempListA->getHead()->getWord() << " " << tempListA->getTail()->getWord() << " is left h/t" << std::endl;
//    tempListA->setSize(list->size() / 2);
   
//    LinkedList* tempListB = new LinkedList;
//    tempListB->setHead(temp->getNext());
//    tempListB->setTail(list->getTail());
//    std::cout << tempListB->getHead()->getWord() << " " << tempListB->getTail()->getWord() << " is right h/t" << std::endl;
//    tempListB->setSize(list->size() - (list->size() / 2));
   
//    this->mergeSort(tempListA);
//    std::cout << "before sort b\n" << tempListA->getHead()->getWord() << " " << tempListA->getTail()->getWord() << " is left h/t after sort" << std::endl;
//    this->mergeSort(tempListB);
//    std::cout << "after sort b\n" << tempListB->getHead()->getWord() << " " << tempListB->getTail()->getWord() << " is right h/t after sort" << std::endl;
   
//    list->setHead(nullptr);
//    list->setTail(nullptr);
//    list->setSize(0);
//    list->mergeDicts(tempListA);
//    std::cout << "done merge a" << std::endl;
//    std::cout << list->getHead()->getWord() << " " << list->getTail()->getWord() << " is list h/t after merge a" << std::endl;
//    list->mergeDicts(tempListB);
//    std::cout << "done merge b" << std::endl;
//    std::cout << list->getHead()->getWord() << " " << list->getTail()->getWord() << " is list h/t after merge b" << std::endl;
   
//    delete tempListA;
//    delete tempListB;
// }

// --- BELOW IS ORIGINAL MERGEDICTS WITH WHILES INSTEAD OF FORLOOPS. 49/68

// void LinkedList::mergeDicts(LinkedList* list) {
//    Node* temp = list->getHead();
//    Node* tempInner = this->getHead();
   
//    while(temp != nullptr) {
//       Node* temp2 = temp->getNext();
//       while(tempInner != nullptr) {
//          if(*temp == *tempInner) {                    // skips if word already in dict A
//             list->setHead(temp2);
//             list->setSize(list->size() - 1);
//             delete temp;
//             break;
//          }
            
//          if(*tempInner > *temp) {
//             if(tempInner == this->getHead()) {        // basically insert_before() w/o creating a new node
//                this->setHead(temp);   
//                temp->setPrev(nullptr);
//             } else {
//                temp->setPrev(tempInner->getPrev());
//                (tempInner->getPrev())->setNext(temp);
//             }
//             temp->setNext(tempInner);
//             tempInner->setPrev(temp);
//             list->setHead(temp2);
//             list->setSize(list->size() - 1);
//             this->listSize++;
//             break;
//          }    
//          tempInner = tempInner->getNext();
//       }
//       temp = temp2;
//    }
//    *this += *list;                                    // appends rest of dict B
// }
