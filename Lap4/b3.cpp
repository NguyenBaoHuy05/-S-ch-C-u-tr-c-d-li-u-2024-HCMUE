#include <iostream>
#include <stdio.h>
using namespace std;

template<class DataType>
class Stack;
template<class DataType>
class Node{
    friend Stack<DataType>;
private:
    DataType data;
    Node* pNext;
public:
    Node(DataType _data):data(_data), pNext(nullptr){};
};
template<class DataType>
class Stack{
private:
    int _iSize;
    Node<DataType>* pHead;
public:
    Stack();
    ~Stack();

    int getSize();
    bool isEmpty();
    void push(DataType);
    DataType pop();
    DataType peek();
    void display();
    void clear();
};
template<class DataType>
Stack<DataType>::Stack():_iSize(0), pHead(nullptr){}

template<class DataType>
Stack<DataType>::~Stack(){
    clear();
}

template<class DataType>
int Stack<DataType>::getSize(){
    return _iSize;
}

template<class DataType>
bool Stack<DataType>::isEmpty(){
    return pHead == nullptr;
}

template<class DataType>
void Stack<DataType>::push(DataType data){
    Node<DataType>* pTemp = new Node<DataType>(data);
    pTemp->pNext = pHead;
    pHead = pTemp;
    _iSize++;
}

template<class DataType>
DataType Stack<DataType>::pop() {
    if(isEmpty()){
        cout << "Stack rong\n";
        exit;
    }
    else {
        DataType temp = pHead->data;
        Node<DataType>* pTemp = pHead;
        pHead = pHead->pNext;
        delete pTemp;
        _iSize--;
        return temp;
    }
}

template<class DataType>
DataType Stack<DataType>::peek(){
    if(isEmpty()){
        cout << "Stack rong\n";
        exit;
    }
    else return pHead->data;
}

template<class DataType>
void Stack<DataType>::display(){
    Node<DataType>* pTemp = pHead;
    while(pTemp != nullptr){
        cout << pTemp->data << " ";
        pTemp = pTemp->pNext;
    }
}

template<class DataType>
void Stack<DataType>::clear(){
    while(pHead != nullptr){
        Node<DataType>* pTemp = pHead;
        pHead = pHead->pNext;
        delete pTemp;
    }
    _iSize = 0;
}

int pos(char a){
    return a == '/' ||  a == '*' ? 1 : 0;
}

int main(){
    Stack<char> ds;
    string n, s, z = "";
    cout << " Bieu thuc trung to: ";
    cin >> n;
    cout << " Bieu thuc hau to: ";
    for(char c:n){
        if(isdigit(c)) {
            z += c;          
        }
        else if(isalpha(c)) {
            if(z != "") s += z, s += ' ', z = "";
            s += c, s += ' ';
        }
        else {
            if(z != "") s += z, s += ' ', z = "";
            if(ds.isEmpty()) ds.push(c);
            else if(c == '(') ds.push(c);
            else if(c == ')') {
                while(ds.peek() != '('){
                    s += ds.pop();
                    s += ' ';
                }
                ds.pop();
            }
            else {
                while(!ds.isEmpty() && pos(ds.peek()) >= pos(c) && ds.peek() != '(') s += ds.pop(), s += ' ';
                ds.push(c);
            }
        }
    }
    while(!ds.isEmpty()) s += ds.pop(), s += ' ';
    cout << s;
    return 0;
}