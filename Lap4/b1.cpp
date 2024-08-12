#include <iostream>
using namespace std;

class Stack;
class Node{
    friend Stack;
private:
    int data;
    Node* pNext;
public:
    Node(int _data):data(_data), pNext(nullptr){};
};
class Stack{
private:
    int _iSize;
    Node* pHead;
public:
    Stack();
    ~Stack();

    int getSize();
    bool isEmpty();
    void push(int);
    int pop();
    int peek();
    void display();
    void clear();
};
Stack::Stack():_iSize(0), pHead(nullptr){}

Stack::~Stack(){
    clear();
}
int Stack::getSize(){
    return _iSize;
}
bool Stack::isEmpty(){
    return pHead == nullptr;
}
void Stack::push(int data){
    Node* pTemp = new Node(data);
    pTemp->pNext = pHead;
    pHead = pTemp;
    _iSize++;
}
int Stack::pop() {
    if(isEmpty()){
        cout << "Stack rong\n";
        return INT_MIN;
    }
    else {
        int temp = pHead->data;
        Node* pTemp = pHead;
        pHead = pHead->pNext;
        delete pTemp;
        _iSize--;
        return temp;
    }
}
int Stack::peek(){
    if(isEmpty()){
        cout << "Stack rong\n";
        return INT_MIN;
    }
    else return pHead->data;
}

void Stack::display(){
    Node* pTemp = pHead;
    while(pTemp != nullptr){
        cout << pTemp->data << " ";
        pTemp = pTemp->pNext;
    }
}
void Stack::clear(){
    while(pHead != nullptr){
        Node* pTemp = pHead;
        pHead = pHead->pNext;
        delete pTemp;
    }
    _iSize = 0;
}
int main(){
    Stack ds;
    int n;
    cout << "Nhap co so n: ";
    cin >> n;
    while(n){
        ds.push(n % 2);
        n /= 2;
    }
    cout << "Dang nhi phan: ";
    while(!ds.isEmpty()){
        cout << ds.pop();
    } 
    return 0;
}