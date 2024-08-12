#include <iostream>
#include <stdio.h>
#include <string>
#include <variant>
using namespace std;

enum DataType {
    INT,
    DOUBLE,
    CHAR,
    STRING
};
class Stack;

class Node{
    friend Stack;
private:
    DataType type;
    variant<int, double, char, string> data;
    Node* pNext;
public:
    Node(variant<int, double, char, string> _data, DataType _type):data(_data),type(_type),pNext(nullptr){}
    void display() {
        switch (type)
        {
        case INT:
            cout << "Int: " << get<int>(data);
            break;
        case DOUBLE:
            cout << "Double: " << get<double>(data);
            break;
        case CHAR:
            cout << "Char: " << get<char>(data);
            break;
        case STRING:
            cout << "String: " << get<string>(data);
            break;        
        default:
            break;
        }
    }
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
    void push(variant<int, double, char, string> data, DataType type);
    void pop();
    void peek();
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


void Stack::push(variant<int, double, char, string> data, DataType type){
    Node* pTemp = new Node(data, type);
    pTemp->pNext = pHead;
    pHead = pTemp;
    _iSize++;
}


void Stack::pop() {
    if(isEmpty()){
        cout << "Stack rong\n";
        return;
    }
    else {
        pHead->display();
        Node* pTemp = pHead;
        pHead = pHead->pNext;
        delete pTemp;
        _iSize--;
    }
}


void Stack::peek(){
    if(isEmpty()){
        cout << "Stack rong\n";
        return;
    }
    else pHead->display();
}


void Stack::display(){
    if(isEmpty()){
        cout << "Stack rong\n";
        exit;
    }
    Node* pTemp = pHead;
    while(pTemp != nullptr){
        pTemp->display();
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

int main() {
    Stack ds;
    int iLuachon, run;
    int i;
    double d;
    char c;
    string s;
    do
    {
        cout << "\t\t\tSTACK\n";
        cout << "1. Them 1 phan tu vao Stack\n";
        cout << "2. Xem phan tu cuoi\n";
        cout << "3. Xem va xoa phan tu cuoi\n";
        cout << "4. In Stack\n";
        cout << "5. Thoat chuong trinh\n";
        cout << "\n";
        cout << "[***] Lua chon cua ban la: ";
        cin >> run;
        switch (run)
        {
        case 1:
            cout << "Nhap kieu (0->int, 1->thuc, 2->kitu, 3->chuoi): ";
            cin >> iLuachon;
            cout << "Nhap gia tri: ";
            switch (iLuachon)
            {
            case 0:
                cin >> i;
                ds.push(i, INT);
                break;
            case 1:
                cin >> d;
                ds.push(d, DOUBLE);
                break;
            case 2:
                cin >> c;
                ds.push(c, CHAR);
                break;
            case 3:
                cin >> s;
                ds.push(s, STRING);
                break;       
            default:
                break;
            }
            cout << "\nHoan tat!\n";
            break;
        case 2:
            ds.peek();
            cout << "\nHoan tat!\n";
            break;
        case 3:
            ds.pop();
            cout << "\nHoan tat!\n";
            break;
        case 4:
            ds.display();
            cout << "\nHoan tat!\n";
            break;
        default:
            break;
        }
        system("pause");
        system("cls");
    } while (run > 0 && run < 5);
    
    return 0;
}