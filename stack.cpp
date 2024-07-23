#include <iostream>
#include <list>

using namespace std;
template <class T>
 class Stack {
 private:
     list <T> s;
 public:
     void push (T elem){
         s.push_back(elem);
     }
     T pop(){
         if(s.empty()){
             cout << "Can't pop for empty stack" << endl;
         }
         else{
             T temp = s.back();
             s.pop_back();
             return temp;
         }
     }
     T top(){
         return s.back();
     }
     bool isEmpty(){
         if (s.empty()){
             return true;
         }
         else{
             return false;
         }
     }
     int stackSize(){
         return s.size();
     }

     void clear(){
         if(!s.empty()){
             s.clear();
         }
     }

     void print(){
         if(!s.empty()) {
             for (auto e : s) {
                 cout << e << ' ';
             }
         }
         else{
             cout << "Stack is empty"<< endl;
         }
     }

 };

int main() {

    Stack <int> test;
    test.push(1);
    test.push(2);
    test.push(3);
    cout << "Testing the push and print function: " << endl;
    test.print();
    cout << endl << "Testing the pop function: " << endl;
    test.pop();
    test.print();
    cout << endl << "Stack isEmpyt()? : " << std::boolalpha << test.isEmpty() << endl;
    cout << "Testing the size() function : " << endl;
    cout << test.stackSize() << endl;
    cout << "Testing the top() function: " << endl;
    cout << test.top() << endl;


    return 0;
}
