#include <iostream>
#include <list>

using namespace std;

template <class T >
class Queue {
private:
    list<T> q;
public:
    void enqueue(T elem) {
        q.push_back(elem);
    }

    T dequeue() {
        if (!q.empty()) {
            T temp = q.front();
            q.pop_front();
            return temp;
        } else {
            cout << "Can't dequeue from an empty queue" << endl;
        }
    }

    T first() {
        T firstElem = q.front();
        return firstElem;
    }

    bool isEmpty() {
        if (q.empty()) {
            return true;
        } else {
            return false;
        }
    }

    int queueSize() {
        return q.size();
    }

    void clear() {
        q.clear();
    }

    void print() {
        if (!q.empty()) {
            for (auto e: q) {
                cout << e << " ";
            }
        }
        else {
            cout << "Queue is Empty" << endl;
        }
    }


};



int main(){
    Queue<int> test;
    test.enqueue(1);
    test.enqueue(2);
    test.enqueue(3);
    cout << "Testing first() function : " << endl;
    cout << test.first() << endl;
    cout << "Testing the enqueue and print function: " << endl;
    test.print();
    cout << endl << "Testing the dequeue function: " << endl;
    cout << "Element that get removed is : " << test.dequeue() << endl;
    test.print();
    cout << endl << "Enqueue isEmpyt()? : " << std::boolalpha << test.isEmpty() << endl;
    cout << "Testing the size() function : " << endl;
    cout << test.queueSize() << endl;
    cout << "Testing the clear() function: " << endl;
    test.clear();
    test.print();

    return 0;
}