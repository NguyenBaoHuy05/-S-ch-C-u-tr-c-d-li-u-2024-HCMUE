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
    void Sort();

    void inL1notL2(const Dslk&, const Dslk&);
    void inL1inL2(const Dslk&, const Dslk&);
    void L1orL2(const Dslk&, const Dslk&);
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
void Dslk<Datatype>::Sort(){
    if(this->pHead == nullptr) {
        cout << "Khong co!\n";
        return ;
    }
    Node<Datatype>* p1;
    Node<Datatype>* p2;
    for(p1 = pHead; p1 -> pNext != nullptr; p1 = p1 -> pNext ){
        for(p2 = p1 -> pNext; p2 != nullptr; p2 = p2 -> pNext ){
            if(p1 -> data > p2 -> data) swap(p1 -> data, p2 -> data);
        }
    }
}

template<class Datatype>
void Dslk<Datatype>::inL1notL2(const Dslk& _ds1, const Dslk& _ds2){
    Node<Datatype>* pDs1 = _ds1.pHead;
    Node<Datatype>* pDs2 = _ds2.pHead;

    while(pDs1 != nullptr) {
        bool found = false;
        pDs2 = _ds2.pHead;
        while(pDs2 != nullptr){
            if(pDs1->data == pDs2->data){
                found = true;
                break;
            }
            pDs2 = pDs2->pNext;
        }
        if(!found) this->push(pDs1->data);
        pDs1 = pDs1->pNext;
    }
    Sort();
}

template<class Datatype>
void Dslk<Datatype>::inL1inL2(const Dslk& _ds1, const Dslk& _ds2){
    Node<Datatype>* pDs1;
    Node<Datatype>* pDs2;
    for(pDs1 = _ds1.pHead; pDs1 != nullptr; pDs1 = pDs1->pNext){
        for(pDs2 = _ds2.pHead; pDs2 != nullptr; pDs2 = pDs2->pNext){
            if(pDs1->data == pDs2->data) {
                this->push(pDs1->data);
                break;
            }
        }
    }
    Sort();
}

template<class Datatype>
void Dslk<Datatype>::L1orL2(const Dslk& _ds1, const Dslk& _ds2){
    Node<Datatype>* pDs1 = _ds1.pHead;
    Node<Datatype>* pDs2 = _ds2.pHead;
    set<Datatype> d;

    while(pDs1 != nullptr) {
        this->push(pDs1->data);
        d.insert(pDs1->data);
        pDs1 = pDs1->pNext;
    }
    while (pDs2 != nullptr) {
        if (d.find(pDs2->data) == d.end()) {
            this->push(pDs2->data);
        }
        pDs2 = pDs2->pNext;
    }
    Sort();
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

    _l3 = Dslk<int>();
    cout << "Danh sach L3 la hieu L2 va L1:" << endl;
    _l3.inL1notL2(_l1,_l2);
    _l3.print();

    _l3 = Dslk<int>();
    cout << "Danh sach L3 la giao L2 va L1:" << endl;
    _l3.inL1inL2(_l1,_l2);
    _l3.print();

    _l3 = Dslk<int>();
    cout << "Danh sach L3 la hop L2 va L1:" << endl;
    _l3.L1orL2(_l1,_l2);
    _l3.print();
    return 0;
}
