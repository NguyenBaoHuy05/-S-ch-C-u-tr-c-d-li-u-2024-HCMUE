#include <iostream>
#include <string>
using namespace std;

enum DataType { INT, DOUBLE, CHAR, STRING };

class Node {
public:
    void* data;
    DataType type;
    Node* pNext;

    Node(void* _data, DataType _type) : data(_data), type(_type), pNext(nullptr) {}
};

class Dslk {
private:
    Node* pHead;
    int _iSize;
public:
    Dslk();
    ~Dslk();

    void push_pHead(void* data, DataType type);
    void delete_pHead();
    void push_tail(void* data, DataType type);
    void delete_tail();
    void push_mid(Node* ds, void* data, DataType type);
    void delete_mid(Node* ds);
    Node* findX(void* data, DataType type);

    void print() const;
};

Dslk::Dslk() : pHead(nullptr), _iSize(0) {}

Dslk::~Dslk() {
    while (pHead != nullptr) {
        Node* pTemp = pHead;
        pHead = pHead->pNext;
        delete pTemp;
    }
}

void Dslk::push_pHead(void* data, DataType type) {
    Node* node = new Node(data, type);
    if (pHead == nullptr) {
        pHead = node;
    } else {
        node->pNext = pHead;
        pHead = node;
    }
    _iSize++;
}

void Dslk::delete_pHead() {
    if (pHead != nullptr) {
        Node* pTemp = pHead;
        pHead = pHead->pNext;
        delete pTemp;
        _iSize--;
    }
}

void Dslk::push_tail(void* data, DataType type) {
    Node* node = new Node(data, type);
    if (pHead == nullptr) {
        pHead = node;
    } else {
        Node* pTemp = pHead;
        while (pTemp->pNext != nullptr) {
            pTemp = pTemp->pNext;
        }
        pTemp->pNext = node;
    }
    _iSize++;
}

void Dslk::delete_tail() {
    if (pHead != nullptr) {
        Node* pTemp = pHead;
        Node* pPre = nullptr;
        while (pTemp->pNext != nullptr) {
            pPre = pTemp;
            pTemp = pTemp->pNext;
        }
        if (pPre == nullptr) {
            pHead = nullptr;
        } else {
            pPre->pNext = nullptr;
        }
        delete pTemp;
        _iSize--;
    }
}

void Dslk::push_mid(Node* ds, void* data, DataType type) {
    if (ds == nullptr) return;

    Node* node = new Node(data, type);
    Node* pTemp = pHead;
    while (pTemp != ds && pTemp != nullptr) {
        pTemp = pTemp->pNext;
    }
    if (pTemp != nullptr) {
        node->pNext = pTemp->pNext;
        pTemp->pNext = node;
        _iSize++;
    }
}

void Dslk::delete_mid(Node* ds) {
    if (ds == nullptr || pHead == nullptr) return;

    if (ds == pHead) {
        delete_pHead();
        return;
    }

    Node* pTemp = pHead;
    while (pTemp->pNext != ds && pTemp->pNext != nullptr) {
        pTemp = pTemp->pNext;
    }
    if (pTemp->pNext == ds) {
        pTemp->pNext = ds->pNext;
        delete ds;
        _iSize--;
    }
}

Node* Dslk::findX(void* data, DataType type) {
    Node* pTemp = pHead;
    while (pTemp != nullptr) {
        if (pTemp->type == type) {
            switch (type) {
            case INT:
                if (*(int*)pTemp->data == *(int*)data) return pTemp;
                break;
            case DOUBLE:
                if (*(double*)pTemp->data == *(double*)data) return pTemp;
                break;
            case CHAR:
                if (*(char*)pTemp->data == *(char*)data) return pTemp;
                break;
            case STRING:
                if (*(string*)pTemp->data == *(string*)data) return pTemp;
                break;
            default:
                break;
            }
        }
        pTemp = pTemp->pNext;
    }
    return nullptr;
}

void Dslk::print() const {
    Node* pTemp = pHead;
    while (pTemp != nullptr) {
        switch (pTemp->type) {
        case INT:
            cout << *(int*)pTemp->data << " ";
            break;
        case DOUBLE:
            cout << *(double*)pTemp->data << " ";
            break;
        case CHAR:
            cout << *(char*)pTemp->data << " ";
            break;
        case STRING:
            cout << *(string*)pTemp->data << " ";
            break;
        default:
            break;
        }
        pTemp = pTemp->pNext;
    }
    cout << endl;
}

int main() {
    Dslk list;
    int a = 1;
    double b = 2.5;
    char c = 'g';
    string d = "hcmue";

    list.push_pHead(&a, INT);
    list.push_tail(&c, CHAR);
    list.push_pHead(&b, DOUBLE);
    list.push_tail(&d, STRING);
    list.print();
    list.delete_mid(list.findX(&a, INT));
    list.print();
    return 0;
}
