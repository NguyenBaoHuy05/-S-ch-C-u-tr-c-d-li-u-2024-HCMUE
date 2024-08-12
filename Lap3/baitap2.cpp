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

    void connectL1andL2(const Dslk&, const Dslk&);
    void inL1notL2(const Dslk&, const Dslk&);
    void inL1inL2(const Dslk&, const Dslk&);
    void L1orL2(const Dslk&, const Dslk&);
    void L1addL2(const Dslk&, const Dslk&);
    void L1duplicateL2(const Dslk&, const Dslk&);
    void deletefirstL1sumL2(Dslk&, const Dslk&);
    void deleteallinL1maxL2(Dslk&, const Dslk&);
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

// Tạo danh sách L3 bằng cách nối L2 vào sau L1
template<class Datatype>
void Dslk<Datatype>::connectL1andL2(const Dslk& _ds1, const Dslk& _ds2){
    Node<Datatype>* pDs1 = _ds1.pHead;
    Node<Datatype>* pDs2 = _ds2.pHead;

    while(pDs1 != nullptr) {
        this->push(pDs1->data);
        pDs1 = pDs1->pNext;
    }
    while(pDs2 != nullptr) {
        this->push(pDs2->data);
        pDs2 = pDs2->pNext;
    }
}

// b) Tạo danh sách L3 bao gồm các phần tử chỉ có trong L1 mà không có trong L2 (L3 là hiệu của L1 và L2)
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
}

// c) Tạo danh sách L3 bao gồm các phần tử vừa có trong L1 vừa có trong L2 (L3 là giao của L1 và L2)
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
}

// d) Tạo danh sách L3 bao gồm các phần tử hoặc có trong L1 hoặc có trong L2 (L3 là hợp của L1 và L2)
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

}

// e) Tạo danh sách tổng L3 sao cho:
// - Có độ dài là độ dài lớn nhất của L1 và L2
// - Có giá trị là tổng giá trị các phần tử tương ứng của L1 và L2 (các phần tử bị thiếu trong danh sách ngắn hơn xem như có giá trị 0)
template<class Datatype>
void Dslk<Datatype>::L1addL2(const Dslk& _ds1, const Dslk& _ds2){
    Node<Datatype>* pDs1 = _ds1.pHead;
    Node<Datatype>* pDs2 = _ds2.pHead;

    while(pDs1 != nullptr || pDs2 != nullptr){
        int sav = 0;
        if(pDs1 != nullptr) {
            sav += pDs1->data;
            pDs1 = pDs1->pNext;
        }
        if(pDs2 != nullptr) {
            sav += pDs2->data;
            pDs2 = pDs2->pNext;
        }
        this->push(sav);
    }
}

// f) Kiểm tra 2 danh sách L1 và L2 có trùng giá trị hay không
template<class Datatype>
void Dslk<Datatype>::L1duplicateL2(const Dslk& _ds1, const Dslk& _ds2){
    Node<Datatype>* pDs1;
    Node<Datatype>* pDs2;
    for(pDs1 = _ds1.pHead; pDs1 != nullptr; pDs1 = pDs1->pNext){
        for(pDs2 = _ds2.pHead; pDs2 != nullptr; pDs2 = pDs2->pNext){
            if(pDs1->data == pDs2->data) {
                cout << "Trung!\n";
                return;
            }
        }
    }
    cout << "Ko trùng!\n";
    return;
}

// g) Xóa một phần tử đầu tiên được tìm thấy trong L1 thỏa mãn điều kiện: giá trị của nó lớn hơn tổng giá trị phần tử của L2
template<class Datatype>
void Dslk<Datatype>::deletefirstL1sumL2(Dslk& _ds1, const Dslk& _ds2){
    Node<Datatype>* pDs1 = _ds1.pHead;
    Node<Datatype>* pDs2 = _ds2.pHead;
    int sum = 0;
    while(pDs2 != nullptr){
        sum += pDs2->data;
        pDs2 = pDs2->pNext;
    }
    Node<Datatype>* pPre = nullptr;
    while(pDs1 != nullptr){
        if(sum < pDs1->data){
            if(pPre == nullptr){
                _ds1.pHead = pDs1->pNext;
                delete pDs1;
                _ds1._iSize--;
                break;
            }
            else{
                pPre->pNext = pDs1->pNext;
                delete pDs1;
                 _ds1._iSize--;
                break;              
            }
        }else{
            pPre = pDs1;
            pDs1 = pDs1->pNext;
        }
    }
}

// h) Xóa tất cả các phần tử trong L1 có giá trị bằng giá trị lớn nhất trong L2
template<class Datatype>
void Dslk<Datatype>::deleteallinL1maxL2(Dslk& _ds1, const Dslk& _ds2){
    Datatype ma = numeric_limits<Datatype>::min();
    Node<Datatype>* pDs2 = _ds2.pHead;
    while(pDs2 != nullptr){
        ma = max(pDs2->data, ma);
        pDs2 = pDs2->pNext;
    }
    Node<Datatype>* pDs1 = _ds1.pHead;
    Node<Datatype>* pPre = nullptr;
    while (pDs1 != nullptr) {
        if (pDs1->data == ma) {
            if (pPre == nullptr) {
                _ds1.pHead = pDs1->pNext;
                pDs1 = _ds1.pHead;
            } else {
                pPre->pNext = pDs1->pNext;
                pDs1 = pPre->pNext;
            }
            _ds1._iSize--;
        } else {
            pPre = pDs1;
            pDs1 = pDs1->pNext;
        }
    }
}

int main(){
    int x;
    Dslk<int> _l1, _l2, _l3;
    int _iLuaChon;
    do {
        _l3 = Dslk<int>();
        cout << "\n";
        cout << "1. Nhap 2 danh sach lien ket L1 L2\n";
        cout << "2. Tao danh sach bang cach noi L1 va L2\n";
        cout << "3. Tao L3 la hieu cua L1 va L2\n";
        cout << "4. Tao L3 la giao cua L1 va L2\n";
        cout << "5. Tao L3 la hop cua L1 va L2\n";
        cout << "6. Tao L3 la tong cua L1 va L2\n";
        cout << "7. L1 va L2 co trung nhau khong?\n";
        cout << "8. Xoa gia tri dau tien trong L1 lon hon tong tat ca gia tri L2\n";
        cout << "9. Xoa tat ca gia tri trong L1 bang gia tri lon nhat cua L2\n";
        cout << "10.Thoat khoi chuong trinh\n";
        cout << "\n";
        cout << "Chuc nang ban chon la: ";
        cin >> _iLuaChon;
        cout << "\n\n";

        system("cls");
        switch (_iLuaChon) {
        case 1:
            _l1 = Dslk<int>();
            cout << "Nhap danh sach L1 (nhap ky tu khong phai so de ket thuc):" << endl;
            while(cin >> x) _l1.push(x);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
            _l2 = Dslk<int>();
            cout << "Nhap danh sach L2 (nhap ky tu khong phai so de ket thuc):" << endl;
            while(cin >> x) _l2.push(x);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Danh sach L1:" << endl;
            _l1.print();
            cout << "Danh sach L2:" << endl;
            _l2.print();
            cout << "Hoan tat!\n";
            break;
        case 2:
            cout << "\n[+]. Tao danh sach bang cach noi L1 va L2\n";
            _l3.connectL1andL2(_l1,_l2);
             cout << "Danh sach L3:" << endl;
            _l3.print();
            cout << "Hoan tat!\n";
            break;
        case 3:
            cout << "\n[+]. Tao L3 la hieu cua L1 va L2\n";
            _l3.inL1notL2(_l1,_l2);
            cout << "Danh sach L3:" << endl;
            _l3.print();
            cout << "Hoan tat!\n";
            break;
        case 4:
            cout << "\n[+]. Tao L3 la giao cua L1 va L2\n";
            _l3.inL1inL2(_l1,_l2);
            cout << "Danh sach L3:" << endl;
            _l3.print();
            cout << "Hoan tat!\n";
            break;
        case 5:
            cout << "\n[+]. Tao L3 la hop cua L1 va L2\n";
            _l3.L1orL2(_l1,_l2);
            cout << "Danh sach L3:" << endl;
            _l3.print();
            cout << "Hoan tat!\n";
            break;
        case 6:
            cout << "\n[+]. Tao L3 la tong cua L1 va L2\n";
            _l3.L1addL2(_l1,_l2);
            cout << "Danh sach L3:" << endl;
            _l3.print();
            cout << "Hoan tat!\n";
            break;
        case 7:
            cout << "\n[+]. L1 va L2 co trung nhau khong?\n";
            _l1.L1duplicateL2(_l1,_l2);
            cout << "Hoan tat!\n";
            break;
        case 8:
            cout << "\n[+]. Xoa gia tri dau tien trong L1 lon hon tong tat ca gia tri L2\n";
            _l1.deletefirstL1sumL2(_l1,_l2);
            cout << "Danh sach L1 sau khi xoa:" << endl;
            _l1.print();
            cout << "Hoan tat!\n";
            break;
        case 9:
            cout << "\n[+]. Xoa tat ca gia tri trong L1 bang gia tri lon nhat cua L2\n";
            _l1.deleteallinL1maxL2(_l1,_l2);
            cout << "Danh sach L1 sau khi xoa:" << endl;
            _l1.print();
            cout << "Hoan tat!\n";
            break;
        default:
            cout << "Cam on ban da su dung ung dung!\nThanks";
            break;
        }
        system("pause");
        system("cls");
    } while (_iLuaChon > 0 && _iLuaChon <= 9);
    return 0;
}
