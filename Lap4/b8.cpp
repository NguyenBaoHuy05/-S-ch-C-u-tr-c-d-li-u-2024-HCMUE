#include <iostream>
#include <string>
#include <utility>
using namespace std;

template<class DataType>
class Queue;

template<class DataType>
class Dslk;

template<class DataType>
class Node {
    friend Queue<DataType>;
    friend Dslk<DataType>;
private:
    DataType data;
    Node* pNext;
public:
    Node(DataType _data) : data(_data), pNext(nullptr) {}
};

template<class DataType>
class Queue {
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
Queue<DataType>::Queue() : _iSize(0), pHead(nullptr), pRear(nullptr) {}

template<class DataType>
Queue<DataType>::~Queue() {
    clear();
}

template<class DataType>
int Queue<DataType>::getSize() {
    return _iSize;
}

template<class DataType>
bool Queue<DataType>::isEmpty() {
    return pHead == nullptr;
}

template<class DataType>
void Queue<DataType>::enqueue(DataType data) {
    Node<DataType>* pTemp = new Node<DataType>(data);
    if (pHead == nullptr) {
        pHead = pTemp;
        pRear = pTemp;
    } else {
        pRear->pNext = pTemp;
        pRear = pTemp;
    }
    _iSize++;
}

template<class DataType>
DataType Queue<DataType>::dequeue() {
    if (isEmpty()) {
        cout << "Queue rong\n";
        return DataType(); 
    } else {
        DataType temp = pHead->data;
        Node<DataType>* pTemp = pHead;
        pHead = pHead->pNext;
        delete pTemp;
        _iSize--;
        if (pHead == nullptr) pRear = nullptr;
        return temp;
    }
}

template<class DataType>
DataType Queue<DataType>::peek() {
    if (isEmpty()) {
        cout << "Queue rong\n";
        return DataType(); 
    } else {
        return pHead->data;
    }
}

template<class DataType>
void Queue<DataType>::display() {
    if (pHead == nullptr) {
        cout << "Queue trong!";
        return;
    }
    Node<DataType>* pTemp = pHead;
    while (pTemp != nullptr) {
        pTemp->display(pTemp->data);
        cout << endl << endl;
        pTemp = pTemp->pNext;
    }
}

template<class DataType>
void Queue<DataType>::clear() {
    while (pHead != nullptr) {
        Node<DataType>* pTemp = pHead;
        pHead = pHead->pNext;
        delete pTemp;
    }
    _iSize = 0;
    pRear = nullptr;
}


template<class DataType>
class Dslk {
private:
    Node<DataType>* pHead;
    int _iSize;
public:
    Dslk();
    ~Dslk();

    void push(DataType);
    void display() const;

    bool findX(DataType);
    void deleteX(DataType);
    bool isEmpty();
};

template<class DataType>
Dslk<DataType>::Dslk() : pHead(nullptr), _iSize(0) {}

template<class DataType>
Dslk<DataType>::~Dslk() {
    while (pHead != nullptr) {
        Node<DataType>* pTemp = pHead;
        pHead = pHead->pNext;
        delete pTemp;
    }
}

template<class DataType>
void Dslk<DataType>::push(DataType x) {
    Node<DataType>* node = new Node<DataType>(x);
    if (pHead == nullptr) {
        pHead = node;
    } else {
        Node<DataType>* pTemp = pHead;
        while (pTemp->pNext != nullptr) {
            pTemp = pTemp->pNext;
        }
        pTemp->pNext = node;
    }
    _iSize++;
}

template<class DataType>
void Dslk<DataType>::display() const {
    Node<DataType>* pTemp = pHead;
        int n = 0;
        while(n <= 100) {
            if(pTemp != nullptr && pTemp->data == n) {
                cout << n << " ";
                pTemp = pTemp->pNext;
            }
            else cout <<"__ ";
            if(n % 10 == 0) cout << endl;
            n++;
        }
}

template<class DataType>
bool Dslk<DataType>::findX(DataType x) {
    Node<DataType>* pTemp = pHead;
    while (pTemp != nullptr && pTemp->data != x) {
        pTemp = pTemp->pNext;
    }
    return pTemp != nullptr;
}

template<class DataType>
void Dslk<DataType>::deleteX(DataType x) {
    Node<DataType>* pTemp = pHead;
    Node<DataType>* pPre = nullptr;
    while (pTemp != nullptr && pTemp->data != x) {
        pPre = pTemp;
        pTemp = pTemp->pNext;
    }
    if (pTemp == nullptr) return;
    if (pPre == nullptr) { 
        pHead = pTemp->pNext;
    } else {
        pPre->pNext = pTemp->pNext;
    }
    delete pTemp;
    _iSize--;
}

template<class DataType>
bool Dslk<DataType>::isEmpty() {
    return _iSize == 0;
}


class Dslk1;
class Node1 {
    friend Dslk1;
private:
    pair<string, int> info;
    Node1* pNext;
public:
    Node1(pair<string,int> x) : info(x), pNext(nullptr) {}
};

class Dslk1 {
private:
    Node1* pHead;
    int _iSize;
public:
    Dslk1();
    ~Dslk1();

    void push(pair<string,int>);
    void display() const;

    bool findX(pair<string,int>);
    void deleteX(pair<string,int>);
    bool isEmpty();
};

Dslk1::Dslk1() : pHead(nullptr), _iSize(0) {}

Dslk1::~Dslk1() {
    while (pHead != nullptr) {
        Node1* pTemp = pHead;
        pHead = pHead->pNext;
        delete pTemp;
    }
}

void Dslk1::push(pair<string,int> x) {
    Node1* node = new Node1(x);
    if (pHead == nullptr) {
        pHead = node;
    } else {
        Node1* pTemp = pHead;
        while (pTemp->pNext != nullptr) {
            pTemp = pTemp->pNext;
        }
        pTemp->pNext = node;
    }
    _iSize++;
}

void Dslk1::display() const {
    Node1* pTemp = pHead;
    while (pTemp->pNext != nullptr) {
        cout << "Ten khach hang: " << pTemp->info.first << endl;
        cout << "Ten ghe: " << pTemp->info.second << endl << endl;
        pTemp = pTemp->pNext;
    }
}

bool Dslk1::findX(pair<string,int> x) {
    Node1* pTemp = pHead;
    while (pTemp != nullptr && pTemp->info != x) {
        pTemp = pTemp->pNext;
    }
    return pTemp != nullptr;
}

void Dslk1::deleteX(pair<string,int> x) {
    Node1* pTemp = pHead;
    Node1* pPre = nullptr;
    while (pTemp != nullptr && pTemp->info != x) {
        pPre = pTemp;
        pTemp = pTemp->pNext;
    }
    if (pTemp == nullptr) return;
    if (pPre == nullptr) { 
        pHead = pTemp->pNext;
    } else {
        pPre->pNext = pTemp->pNext;
    }
    delete pTemp;
    _iSize--;
}

bool Dslk1::isEmpty() {
    return _iSize == 0;
}

int main() {
    Dslk<int> A;
    Queue<int> B;
    int so = 0;
    Dslk1 C;
    int n = 101;
    for (int i = 0; i < n; i++) A.push(i);
    int iLuachon;
    do {
        cout << "\t\t\tCHUONG TRINH MO PHONG QUY TRINH DAT VE XEM PHIM\n";
        cout << "1. Lay so xep hang\n";
        cout << "2. Mua ve\n";
        cout << "3. Huy ve\n";
        cout << "4. Hien thi ve da ban\n";
        cout << "5. Thoat chuong trinh\n";
        cout << "\n";
        cout << "[***] Lua chon cua ban la: ";
        cin >> iLuachon;
        system("cls");
        int soghe;
        string ten;
        cin.ignore(); 
        switch (iLuachon) {
        case 1:
            cout <<"\n[+] Lay so xep hang.\n"; 
            cout << "Lay xong!\n";
            B.enqueue(so);
            so++;         
            break;
        case 2:
            cout <<"\n[+] Mua ve.\n"; 
            if (A.isEmpty()) {
                cout << "Het ghe!\n";
            } else if(!B.isEmpty()){
                B.dequeue();
                cout << "Cac ghe con trong:\n";
                A.display();
                cout << "\n\n Ten khach hang: ";
                getline(cin, ten);
                cout << "So ghe khach chon: ";
                cin >> soghe;
                while (!A.findX(soghe)) {
                    cout << "Ghe da co nguoi dat! Chon ghe khac: ";
                    cin >> soghe;
                }
                A.deleteX(soghe);
                C.push({ten, soghe });
            }
            else cout << "Hay lay so\n";
            break;
        case 3:
            if(!C.isEmpty()) {
                cout <<"\n[+] Xoa ve.\n"; 
                cout << "\n\n Ten khach hang: ";
                getline(cin, ten);
                cout << "Nhap so ghe cua ve can huy: ";
                cin >> soghe;
                while (A.findX(soghe)) {
                    cout << "Ghe chua duoc dat!\nNhap lai: ";
                    cin >> soghe;
                }
                C.deleteX({ten, soghe });
            }
            else cout << "Chua ai mua ve\n";
            break;
        case 4:
            cout <<"\n[+]Hien thi ve da ban.\n"; 
            if(C.isEmpty()) cout << "Chua ai mua ve\n";
            else C.display();
            break;
        default:
            cout << "***Cam on da su dung!!***\n";
            break;
        }
        system("pause");
        system("cls");
    } while (iLuachon > 0 && iLuachon < 5);
    return 0;
}
