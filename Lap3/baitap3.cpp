#include <iostream>
#include <set>
#include <limits>
using namespace std;

template<class Datatype>
class Dslk;

template<class Datatype>
class Node{
private:
    Datatype data;
    Node<Datatype>* pNext;
public:
    friend class Dslk<Datatype>;

    Node(int data);
    void display() const;
};

template<class Datatype>
Node<Datatype>::Node(int _data) : data(_data), pNext(nullptr) {}

template<class Datatype>
void Node<Datatype>::display() const{
    cout << data << " ";
}

template<class Datatype>
class Dslk{
private:
    Node<Datatype>* pHead;
    int _iSize;
public:
    Dslk();
    ~Dslk();

    void push(int x);
    void print() const;

    void arrfirstL1inL2(const Dslk&, const Dslk&);
};

template<class Datatype>
Dslk<Datatype>::Dslk() : pHead(nullptr), _iSize(0) {}

template<class Datatype>
Dslk<Datatype>::~Dslk(){
    while(pHead != nullptr) {
        Node<Datatype>* pTemp = pHead;
        pHead = pHead->pNext;
        delete pTemp;
    }
}

template<class Datatype>
void Dslk<Datatype>::push(int x){
    Node<Datatype>* node = new Node<Datatype>(x);
    if(pHead == nullptr){
        pHead = node;
    }
    else{
        Node<Datatype>* pTemp = pHead;
        while(pTemp->pNext != nullptr){
            pTemp = pTemp->pNext;
        }
        pTemp->pNext = node;
    }
    _iSize++;
}

template<class Datatype>
void Dslk<Datatype>::print() const{
    Node<Datatype>* pTemp = pHead;
    while(pTemp != nullptr){
        pTemp->display();
        pTemp = pTemp->pNext;
    }
    cout << endl;
}
template<class Datatype>
void Dslk<Datatype>::arrfirstL1inL2(const Dslk& _ds1, const Dslk& _ds2){
        Node<Datatype>* pDs1 = _ds1.pHead;
        Node<Datatype>* pDs2;

        bool kt = true;
        while(pDs1 != nullptr && kt){
            pDs2 = _ds2.pHead;
            while(pDs2 != nullptr && kt){
                if(pDs2->data == pDs1->data){
                    this->push(pDs2->data);
                    kt = !kt;
                }
                pDs2 = pDs2->pNext;
            }
            pDs1 = pDs1->pNext;
        }
        if(pDs1 == nullptr){
            cout << "Khong co";
        }
        else{
            while(pDs2 != nullptr && pDs2->data == pDs1->data){
                this->push(pDs2->data);
                pDs2 = pDs2->pNext;
                pDs1 = pDs1->pNext;
            }
        }
}

int main(){
    int x;
    Dslk<int> _l1, _l2, _l3;
    cout << "Nhap danh sach L1 (nhap ky tu khong phai so de ket thuc):" << endl;
    while(cin >> x) _l1.push(x);
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "Nhap danh sach L2 (nhap ky tu khong phai so de ket thuc):" << endl;
    while(cin >> x) _l2.push(x);
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Danh sach L1:" << endl;
    _l1.print();
    cout << "Danh sach L2:" << endl;
    _l2.print();
    _l3.arrfirstL1inL2(_l1,_l2);
    cout << "Danh sach L3:" << endl;
    _l3.print();
    return 0;
}