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

template <class DataType>
void quickSort(DataType a[], int left, int right) {
    DataType x;
    int i,j;
    Stack<int> ds;
    ds.push(left);
    ds.push(right); 
    while(!ds.isEmpty()) {
        right = ds.pop();
        left = ds.pop();
        x = a[(left + right) / 2];
        i = left, j = right;
        while(i < j) {
            while (a[i] < x) i++;
            while (a[j] > x) j--;
            if (i <= j) {
                swap(a[i], a[j]);
                i++;
                j--;
            }
        }
        if(left < j) {
            ds.push(left);
            ds.push(j);
        }
        if(i < right) {
            ds.push(i);
            ds.push(right);
        }
    }
}
int main(){
    int a[8] = {6,8,7,4,1,5,3,2};
    quickSort(a, 0, 7);
    for(int i = 0; i < 8; i++) cout << a[i] << " ";
    return 0;
}