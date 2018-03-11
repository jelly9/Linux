#include <iostream>
#include <unordered_set>
#include <algorithm>
using namespace std;

typedef struct Node{
    Node(int d):_data(d){}
    int _data;
    struct Node *_next;
}Node;

int main()
{
    Node n1(1);
    Node n2(2);
    Node n3(3);
    Node n4(4);
    n1._next = &n2;
    n2._next = &n3;
    n3._next = NULL;
    unordered_set<Node*> s;
    s.insert(&n1);
    s.insert(&n3);
    s.insert(&n2);

    std::unordered_set<struct Node*>::iterator it = s.begin();
    while(it != s.end()){
        cout << *it << ": " << (*it)->_data << endl;;
        ++it;
    }

    it = s.begin();
    std::unordered_set<struct Node*>::iterator it1;
    while(it != s.end()){
        it1 = s.find(&n4);
        if(*it1 == &n4){
            cout << "found!" << endl;
            break;
        }
        ++it;
    }
    //find(s.begin, s.end(), &n1);

    return 0;
}
