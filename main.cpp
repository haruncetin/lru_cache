#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache : public Cache {
private:
    int _probe(int key) {
        try
        {
            return mp.at(key)->value;
        }
        catch(const std::exception&)
        {
            return -1;
        }
    }
public:
    LRUCache(int capacity) {
        this->cp = capacity;
    }

    void set(int key, int val) {
        if(!mp.empty()) {
            if(_probe(key)>=0) {
                if(mp[key]->next == nullptr) {
                    tail = mp[key]->prev;
                }
                if(mp[key]->prev != nullptr) {
                    mp[key]->prev->next = mp[key]->next;                    
                }
                mp[key]->key = key;
                mp[key]->value = val;
                mp[key]->prev = nullptr;
                mp[key]->next = head->next;
                head = mp[key];
            } else {
                mp[key] = new Node(key, val);
                mp[key]->prev = nullptr;
                mp[key]->next = head;
                head = mp[key];
            }        
            if(mp.size() >= cp) {
                //mp.erase(tail->key);
                mp[tail->key] = nullptr;
                tail->prev->next = nullptr;
                delete tail->prev->next;
                tail = tail->prev;
            }
        } else {
            head = tail = new Node(key, val);
            head->next = tail;
            head->prev = nullptr;
            tail->prev = head;
            tail->next = nullptr;
            mp[key] = head;
        }
    }

    int get(int key) {
        return _probe(key);
    }
};

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
