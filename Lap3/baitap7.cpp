#include<iostream>
#include<algorithm>
#include<cmath>
#include<set>
#include<limits>
using namespace std;

class Dslk;
class Node{
private:
    int hang;
    int mu;
    Node* pNext;
public:
    friend Dslk;

    Node(int,int);
    void display();
};
Node::Node(int _hang, int _mu){
    hang = _hang;
    mu = _mu;
    pNext = NULL;
}
void Node::display(){
    if(hang != 0){
        if(mu == 0) {
            if(hang != 0){
                cout << abs(hang) << " ";
            }
        }
        else if(mu == 1){
            if(abs(hang) == 1){
                cout << "x" <<" ";
            }
            else cout << abs(hang) << "x " << " ";
        }
        else {
            if(abs(hang) != 1){
                cout << abs(hang);
            }
            cout << "x^" << mu << " ";
        }
    }

}
class Dslk{
private:
    Node* pHead;
    int _iSize;
public:
    Dslk();
    ~Dslk();

    void copy(Dslk&);

    void push(int, int);
    void print();
    void daoham();
    int giatri(int);
    void tong(Dslk&,Dslk&);
    void tich(Dslk&,Dslk&);
};
Dslk::Dslk() : pHead(NULL), _iSize(0) {}
Dslk::~Dslk(){
    while (pHead != NULL) {
        Node* temp = pHead;
        pHead = pHead->pNext;
        delete temp;
    }
}

void Dslk::copy(Dslk& ds){
    Node* pTemp = ds.pHead;
    while(pTemp != nullptr){
        this->push(pTemp->hang, pTemp->mu);
        pTemp = pTemp->pNext;
    }
}

void Dslk::push(int a, int x){
    Node* node= new Node(a, x);
    if(pHead == NULL){
        pHead = node;
    }
    else{
        Node *pTemp = pHead;
        while(pTemp -> pNext != NULL){
            pTemp = pTemp -> pNext;
        }
        pTemp -> pNext = node;
    }
    _iSize++;
}

void Dslk::print(){
    Node *pTemp = pHead;
    if(pTemp != NULL) if(pTemp->hang < 0) cout << "- ";
    while(pTemp != NULL){
        pTemp -> display();
        if(pTemp->pNext != NULL) {
            if(pTemp->hang != 0){
                if((pTemp->pNext)->hang < 0) cout << "- ";
                else if ((pTemp->pNext)->hang > 0) cout << "+ ";
            }
        }        
        pTemp = pTemp -> pNext;
    }
}

void Dslk::daoham(){
    Node* pTemp = pHead;
    Node* pPre = NULL;
    while(pTemp != NULL) {
        if(pTemp->mu != 0){
            pTemp->hang *= pTemp->mu;
            pTemp->mu--;
            pPre = pTemp;
            pTemp = pTemp->pNext;
        }
        else{
            pPre->pNext = NULL;
            break;
        }
    }
}
int Dslk::giatri(int x){
    Node* pTemp = pHead;
    int ans = 0;
    while(pTemp != NULL) {
        ans += pTemp->hang * pow(x,pTemp->mu);
        pTemp = pTemp->pNext;
    }
    return ans;
}

void Dslk::tong(Dslk& _ds1,Dslk& _ds2){
    Node* pTemp1 = _ds1.pHead;
    Node* pTemp2 = _ds2.pHead;
    while(pTemp1 != NULL || pTemp2 != NULL) {
        if(pTemp1 != NULL && pTemp2 != NULL){
            if(pTemp1->mu == pTemp2->mu){
                this->push(pTemp1->hang + pTemp2->hang, pTemp1->mu);
                pTemp1 = pTemp1->pNext;
                pTemp2 = pTemp2->pNext;
            }
            else if(pTemp1->mu > pTemp2->mu){
                this->push(pTemp1->hang, pTemp1->mu); 
                pTemp1 = pTemp1->pNext;           
            }
            else {
                this->push(pTemp2->hang, pTemp2->mu); 
                pTemp2 = pTemp2->pNext;
            } 
        }
        else if(pTemp1 == NULL){
                this->push(pTemp2->hang, pTemp2->mu); 
                pTemp2 = pTemp2->pNext;            
        }
        else if(pTemp2 == NULL){
                this->push(pTemp1->hang, pTemp1->mu); 
                pTemp1 = pTemp1->pNext;            
        }
       
    }   
}
void Dslk::tich(Dslk& _ds1,Dslk& _ds2){
    int mu1 = 0, mu2 = 0;
    Node* pTemp = _ds1.pHead;
    while(pTemp != NULL) {
        mu1 = max(mu1, pTemp->mu);
        pTemp = pTemp->pNext;
    }
    pTemp = _ds2.pHead;
    while(pTemp != NULL) {
        mu2 = max(mu2, pTemp->mu);
        pTemp = pTemp->pNext;
    }
    int max_mu = mu1 + mu2;
    while(max_mu >= 0) {
        this->push(0, max_mu);
        max_mu--;
    }   
    for(Node* pTemp1 = _ds1.pHead; pTemp1 != nullptr;  pTemp1 = pTemp1->pNext){
        for(Node* pTemp2 = _ds2.pHead; pTemp2 != nullptr;  pTemp2 = pTemp2->pNext){
        Node* pTemp = pHead;
            while(pTemp->mu != pTemp1->mu + pTemp2->mu){
                pTemp = pTemp->pNext;
            }
            pTemp->hang += pTemp1->hang * pTemp2->hang; 
        }
    }
}
int main(){
    int x, a;
    Dslk _l1, _l2, _l3, _l4;
    int _iLuaChon;
    do {
        _l3 = Dslk();
        _l4 = Dslk();
        cout << "\n";
        cout << "1. Nhap 2 danh sach lien ket da thuc L1 L2\n";
        cout << "2. In 2 da thuc\n";
        cout << "3. Dao ham cua da thuc\n";
        cout << "4. Gia tri cua da thuc theo x nhap vao tu ban phim\n";
        cout << "5. Tao da thuc L3 la tong cua L1 va L2\n";
        cout << "6. Tao da thuc L3 la tich cua L1 va L2\n";
        cout << "7. Thoat khoi chuong trinh\n";
        cout << "\n";
        cout << "Chuc nang ban chon la: ";
        cin >> _iLuaChon;
        cout << "\n\n";

        system("cls");
        switch (_iLuaChon) {
        case 1:
            cout << "Nhap danh sach da thuc L1 (nhap ky tu khong phai so de ket thuc):" << endl;
            while(cin >> x) {
                cin >> a;
                _l1.push(x,a);
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Nhap danh sach da thuc L2 (nhap ky tu khong phai so de ket thuc):" << endl;
            while(cin >> x) {
                cin >> a;
                _l2.push(x,a);
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        case 2:
            cout << "\n[+]. In 2 da thuc\n";
            cout << "Bieu thuc L1:" << endl;
            _l1.print();

            cout << "\nBieu thuc L2:" << endl;
            _l2.print();
            cout << "\nHoan tat!\n";
            break;
        case 3:
            cout << "\n[+]. Dao ham cua da thuc\n";
            _l3.copy(_l1);
            cout << "Bieu thuc dao ham cua da thuc L1:" << endl;
            _l3.daoham();
            _l3.print();
            _l4.copy(_l2);
            cout << "\nBieu thuc dao ham cua da thuc L2:" << endl;
            _l4.daoham();
            _l4.print();
            cout << "\nHoan tat!\n";
            break;
        case 4:
            cout << "\n[+]. Gia tri cua da thuc theo x nhap vao tu ban phim\n";
            cout << "Nhap x: ";
            int x;
            cin >> x;
            _l3.copy(_l1);
            cout << "Bieu thuc gia tri cua da thuc L1(" << x <<"):" << _l3.giatri(x) << endl;
            _l4.copy(_l2);
            cout << "\nBieu thuc gia tri cua da thuc L2(" << x <<"):" << _l4.giatri(x) << endl;
            cout << "\nHoan tat!\n";
            break;
        case 5:
            cout << "\n[+]. Tao da thuc L3 la tong cua L1 va L2\n";
            _l3.tong(_l1,_l2);
            cout << "Danh sach L3:" << endl;
            _l3.print();
            cout << "\nHoan tat!\n";
            break;
        case 6:
            cout << "\n[+]. Tao da thuc L3 la tich cua L1 va L2\n";
            _l3.tich(_l1,_l2);
            cout << "Danh sach L3:" << endl;
            _l3.print();
            cout << "\nHoan tat!\n";
            break;
        default:
            cout << "Cam on ban da su dung ung dung!\nThanks";
            break;
        }
        system("pause");
        system("cls");
    } while (_iLuaChon > 0 && _iLuaChon <= 6);
    return 0;
}