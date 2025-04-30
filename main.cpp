#include <iostream> 
#include <fstream>
#include <string>
#include "LinkedList.h"
#include "testll.h"

#define DEFAULT_DICT "dictionary1.txt"
#define DEFAULT_OUTPUT_FILE "dict-updated.txt"

using namespace std;

enum Actions { QUIT, COUNT, PRINT, PRINT_REVERSE, ADD, LINEAR_SEARCH, DELETE, INSERT, SWAP, MERGE, MERGE_SORT, LOAD, WRITE_TO_FILE, TEST }; 

const int min_menu_option = 1;   // not including Quit, which is zero
const int max_menu_option = TEST;
const int min_dict_option = 1;
const int max_dict_option = 12;

// helper
int getMenuChoice();
int getDictChoice(const int curr);
string clean(const string word);
void promptFind(LinkedList* list, const string word, const Actions mode); // handles search, add, delete, insert
// actions
int count(const LinkedList* list);
void print(const LinkedList* list);
void printRev(const LinkedList* list);
Node* findWord(LinkedList* list, string word);
bool load(LinkedList* list, const string filename);
void write(const LinkedList* list);

int main() { 
   int choice;
   int temp;
   int dictOption = min_dict_option;
   string choiceStr;
   LinkedList* dict = new LinkedList;
   LinkedList* dict2 = new LinkedList;
   load(dict, DEFAULT_DICT);
   
   do {
      choice = getMenuChoice();
      switch(choice) {
         case COUNT:
            cout << "There are " << count(dict) << " words in dictionary #" << dictOption << "." << endl;
            break;
         case PRINT:
            print(dict);
            break;
         case PRINT_REVERSE:
            printRev(dict);
            break;
         case ADD:
            cout << "Enter a word to add to the end of the chosen Dictionary: ";
            cin >> choiceStr;
            promptFind(dict, choiceStr, ADD);
            break;
         case LINEAR_SEARCH:
            cout << "Enter a word to find: ";
            cin >> choiceStr;
            promptFind(dict, choiceStr, LINEAR_SEARCH);
            break;
         case DELETE:
            cout << "Enter a word to delete from the chosen Dictionary: ";
            cin >> choiceStr;
            promptFind(dict, choiceStr, DELETE);
            break;
         case INSERT:
            cout << "Enter a word to insert in order in the chosen Dictionary: ";
            cin >> choiceStr;
            promptFind(dict, choiceStr, INSERT);
            break;
         case SWAP:
            cout << "Coming soon!" << endl;
            break;
         case MERGE:
            cout << "Reminder: for merge to work properly, dictionaries must already be sorted." << endl;
            load(dict2, "dictionary" + to_string(getDictChoice(dictOption)) + ".txt");
            cout << "Merging..." << endl;
            dict->mergeDicts(dict2);
            dictOption = max_dict_option + 1;
            cout << "           ...Done!" << endl;
            break;
         case MERGE_SORT:
            cout << "sorting..." << endl;
            dict->mergeSort();
            cout << "           ...Done!" << endl;
            break;
         case LOAD:
            temp = getDictChoice(dictOption);
            if(load(dict, "dictionary" + to_string(temp) + ".txt")) { 
               dictOption = temp;
               cout << "Dictionary " << dictOption << " is now open." << endl; 
            } else {
               cout << "Dictionary " << dictOption << " remains open." << endl;
            }
            break;
         case WRITE_TO_FILE:
            write(dict);
            break;
         case TEST:
            promptUnitTest();
            break;
         default:
            cout << "Thank you! Bye!" << endl;
            break;
      }
   } while(choice != QUIT);
   
   delete dict;
   delete dict2;
   return 0; 
} 
 
int getMenuChoice() {
   int choice;
   do {
      cout << "--------------------------------------------" << endl;
      cout << "Options menu:" << endl;
      cout << "(" << COUNT << ") Count - get number of words in dictionary list" << endl;
      cout << "(" << PRINT << ") Print words to screen" << endl;
      cout << "(" << PRINT_REVERSE << ") Print words to screen in reverse order" << endl;
      cout << "(" << ADD << ") Add a word (to end of dictionary list)" << endl;
      cout << "(" << LINEAR_SEARCH << ") Find a word (Linear Search)" << endl;
      cout << "(" << DELETE << ") Find word, delete if found" << endl;
      cout << "(" << INSERT << ") Find word, insert if not found (assumes words are sorted alphabetically)" << endl;
      cout << "(" << SWAP << ") Swap two words" << endl;
      cout << "(" << MERGE << ") Merge two dictionaries (assumes words are sorted alphabetically)" << endl;
      cout << "(" << MERGE_SORT << ") Sort words (Merge Sort)" << endl;
      cout << "(" << LOAD << ") Load a dictionary (closes current dictionary)" << endl;
      cout << "(" << WRITE_TO_FILE << ") Write current dictionary to file" << endl;
      cout << "(" << TEST << ") Unit test of data structure" << endl;
      cout << "Enter a number from " << min_menu_option << " to " << max_menu_option << ", or " << QUIT << " to exit: ";
      
      cin >> choice;
      if(choice < QUIT || choice > max_menu_option) {
         cout << "Error! Input must be a number between " << min_menu_option << " and " << max_menu_option << ", or " << QUIT << " to exit." << endl;
      }
   } while(choice < QUIT || choice > max_menu_option);
   return choice;
}

int getDictChoice(const int curr) {
   int choice;
   do {
      cout << "Which Dictionary should be opened? Enter a number from \"" << min_dict_option << "\" to \"" << max_dict_option << "\": ";
      cin >> choice;
      if(choice == curr) { cout << "That dictionary is already open! Pick another." << endl; }
      if(choice < min_dict_option || choice > max_dict_option) { cout << "That number is not in the available range! Pick another." << endl; }
   } while(choice < min_dict_option || choice > max_dict_option || choice == curr);
   return choice;
}

string clean(const string word) {
   string temp;
   for(unsigned int i = 0; i < word.size(); i++) {
      if(word.at(i) >= 'a' && word.at(i) <= 'z') {
         temp.push_back(word.at(i));   
      } else if(word.at(i) >= 'A' && word.at(i) <= 'Z') {
         temp.push_back(word.at(i) + 32);   
      }
   }
   return temp;
}

void promptFind(LinkedList* list, const string word, const Actions mode) {
   string cleanWord = clean(word);
   cout << "Your word was '" << cleanWord << "'." << endl;
   Node* temp = findWord(list, cleanWord);
   
   if(temp == nullptr) {
      cout << " We did not find your word." << endl;
      if(mode == ADD || mode == INSERT) {
         cout << " Adding word to dictionary..." << endl;
         if(mode == ADD) {
            list->push_back(cleanWord);
            temp = list->getTail();
            cout << "        Added!" << endl;
         } else {
            temp = list->getHead();
            while(temp != nullptr && *temp <= cleanWord) {
               temp = temp->getNext();
            }
            if(temp == nullptr) {
               list->push_back(cleanWord); 
               temp = list->getTail();
            } else {
               temp = list->insert_before(cleanWord, temp);
            }
            cout << "Inserted!" << endl;
         }
      } else {
         return;
      }
   }
   
   if(temp == list->getHead()) {
      cout << " There is no word before " << cleanWord << ". It is the first word." << endl;
   } else {
      cout << " The previous word would be '" << (temp->getPrev())->getWord() << "'." << endl;
   }
   if(temp == list->getTail()) {
      cout << " There is no word after " << cleanWord << ". It is the last word." << endl;
   } else {
      cout << " The next word would be '" << (temp->getNext())->getWord() << "'." << endl;
   }
   
   if(mode == DELETE) {
      list->deleteWord(temp);
      cout << " The word '" << cleanWord << "' has been deleted." << endl;
   }
}

int count(const LinkedList* list) {
   int count = 0;
   Node* temp = list->getHead();
   while(temp != nullptr) {
      count++;
      temp = temp->getNext();
   }
   return count;
}

void print(const LinkedList* list) {
   Node* temp = list->getHead();
   while(temp != nullptr) {
      cout << temp->getWord() << endl;
      temp = temp->getNext();
   }
}

void printRev(const LinkedList* list) {
   Node* temp = list->getTail();
   while(temp != nullptr) {
      cout << temp->getWord() << endl;
      temp = temp->getPrev();
   }
}

Node* findWord(LinkedList* list, string word) {
   Node* temp = list->getHead();
   while(temp != nullptr) {
      if(temp->getWord() == word) {
         return temp;   
      }
      temp = temp->getNext();
   }
   return nullptr;
}

bool load(LinkedList* list, const string filename) {
   string str;
   ifstream inFS(filename);
   if(!inFS.is_open()) {
      cout << "ERROR! Cannot read chosen dictionary " << filename << "." << endl;
      return false;
   }
   
   list->clear();
   while(inFS >> str) {
      list->push_back(str);
   }
   inFS.close();
   return true;
}

void write(const LinkedList* list) {
   string filename;
   cout << "Enter name of file (.txt will be appended automatically), or enter 'd' to use default filename: ";
   cin >> filename;
   if(filename == "d") {
      filename = DEFAULT_OUTPUT_FILE;   
   } else {
      filename.append(".txt");
   }
   
   ifstream tempFS(filename);
   if(tempFS.is_open()) {
      cout << "Error! The file " << filename << " already exists. No data was written to file." << endl;
      return;
   }
   
   cout << "Writing to file..." << endl;
   ofstream outFS(filename);
   Node* temp = list->getHead();
   while(temp != nullptr) {
      outFS << temp->getWord();
      temp = temp->getNext();
   }
   outFS.close();
   cout << "                   ...Done!" << endl;
}
