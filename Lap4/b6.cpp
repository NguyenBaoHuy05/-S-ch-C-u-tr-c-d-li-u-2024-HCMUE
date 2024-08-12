#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

class HangHoa{
private:
    string _sMaHang;
    string _sTenHang;
    int _iSl;
    int _iDonGia;
public:
    HangHoa(){};
    void nhap(){
        cout << "Nhap ma hang: ";
        cin >> _sMaHang;
        cout << "Nhap ten hang: ";
        cin.ignore();
        getline(cin, _sTenHang);
        cout << "Nhap so luong: ";
        cin >> _iSl;
        cout << "Nhap don gia: ";
        cin >> _iDonGia;
    }
    void xuat(){
        cout << "Ma hang: " << _sMaHang << endl;
        cout << "Ten hang: " << _sTenHang << endl;
        cout << "So luong: " << _iSl << endl;
        cout << "Don gia: " << _iDonGia << endl;       
    }
};
template<class DataType>
class Queue;
template<class DataType>
class Node{
    friend Queue<DataType>;
private:
    DataType data;
    Node* pNext;
public:
    Node(DataType _data):data(_data), pNext(nullptr){};
};
template<class DataType>
class Queue{
private:
    int _iSize;
    Node<DataType>* pHead;
    Node<DataType>* pRear;
public:
    Queue();
    ~Queue();

    int getSize();
    bool isEmpty();
    void enqueue(DataType);
    DataType dequeue();
    DataType peek();
    void display();
    void clear();
};
template<class DataType>
Queue<DataType>::Queue():_iSize(0), pHead(nullptr), pRear(nullptr){}

template<class DataType>
Queue<DataType>::~Queue(){
    clear();
}

template<class DataType>
int Queue<DataType>::getSize(){
    return _iSize;
}

template<class DataType>
bool Queue<DataType>::isEmpty(){
    return pHead == nullptr;
}

template<class DataType>
void Queue<DataType>::enqueue(DataType data){
    Node<DataType>* pTemp = new Node<DataType>(data);
    if(pHead == nullptr) {
        pHead = pTemp;
        pRear = pTemp;
    }
    else {
        pRear->pNext = pTemp;
        pRear = pTemp;
    }
    _iSize++;
}

template<class DataType>
DataType Queue<DataType>::dequeue() {
    if(isEmpty()){
        cout << "Queue rong\n";
        exit;
    }
    else {
        DataType temp = pHead->data;
        Node<DataType>* pTemp = pHead;
        pHead = pHead->pNext;
        delete pTemp;
        _iSize--;
        if(pHead == nullptr) pRear = nullptr;
        return temp;
    }
}

template<class DataType>
DataType Queue<DataType>::peek(){
    if(isEmpty()){
        cout << "Queue rong\n";
        exit;
    }
    else return pHead->data;
}

template<class DataType>
void Queue<DataType>::display(){
    if(pHead == nullptr) {
        cout << "Trong!";
        return;
    }
    Node<DataType>* pTemp = pHead;
    while(pTemp != nullptr){
        pTemp->data.xuat();
        cout << endl << endl;
        pTemp = pTemp->pNext;
    }
}

template<class DataType>
void Queue<DataType>::clear(){
    while(pHead != nullptr){
        Node<DataType>* pTemp = pHead;
        pHead = pHead->pNext;
        delete pTemp;
    }
    _iSize = 0;
    pRear = nullptr;
}

int main() {
    int iLuachon;
    Queue<HangHoa> ds;
    do{
        cout << "\t\t\tQUAN LY HANG HOA\n";
        cout << "1. Xem tat ca cac mat hang trong kho\n";
        cout << "2. Xem mat hang sap duoc sap xuat kho\n";
        cout << "3. Them mot mat hang vao kho\n";
        cout << "4. Xuat mot mat hang ra khoi kho\n";
        cout << "5. Thoat chuong trinh\n";
        cout << "\n";
        cout << "[***] Lua chon cua ban la: ";
        cin >> iLuachon;

        HangHoa hh = HangHoa();
        switch (iLuachon)
        {
        case 1:
            ds.display();
            cout << "\n\nHoan tat!\n";
            break;
        case 2:
            ds.peek().xuat();
            cout << "\n\nHoan tat!\n";
            break;
        case 3:
            hh.nhap();
            ds.enqueue(hh);
            cout << "\n\nHoan tat!\n";
            break;
        case 4:
            ds.dequeue().xuat();
            cout << "\n\nHoan tat!\n";
            break;        
        default:
            cout << "***Cam on da su dung!!***\n";
            break;
        }
        system("pause");
        system("cls");
    }
    while(iLuachon > 0 && iLuachon < 5);
    return 0;
}