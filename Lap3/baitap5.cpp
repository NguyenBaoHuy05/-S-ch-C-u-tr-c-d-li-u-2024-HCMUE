#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

class Dslk;
class Node;
class SinhVien{
    friend Node;
    friend Dslk;
private:
    string _sMsv;
    string _sTen;
    string _sLop;
    string _sNgaysinh;
    float _dtb;
public:
    SinhVien(){};

    void nhap();
    void xuat();
};
void SinhVien::nhap(){
    cout << "\nNhap thong tin sinh vien: \n";
    cout << "Nhap ma sinh vien: ";
    cin >> _sMsv;
    cout << "Nhap ho ten sinh vien: ";
    cin.ignore();
    getline(cin,_sTen);
    cout << "Nhap lop: ";
    cin >> _sLop;
    cout << "Nhap ngay sinh: "; 
    cin >>_sNgaysinh;
    cout << "Nhap diem trung binh: ";
    cin >> _dtb;
    cout << endl;
}
void SinhVien::xuat(){
    cout << "Thong tin sinh vien: \n";
    cout << "Ma sinh vien: " << _sMsv << endl;
    cout << "Ho ten sinh vien: " << _sTen << endl;
    cout << "Lop: " << _sLop << endl;
    cout << "Ngay sinh: " << _sNgaysinh << endl;
    cout << "Diem trung binh: " << _dtb << "\n\n";
}

class Node{
    friend Dslk;
private:
    SinhVien data;
    Node* pNext;
public:
    friend Dslk;

    Node(SinhVien);

    void nhap();
    void xuat();
};

Node::Node(SinhVien a){
    data = a;
    pNext = nullptr;
}

void Node::nhap(){
    data.nhap();
}
void Node::xuat(){
    data.xuat();
}
class Dslk{
private:
    Node* pHead;
    int _iSize;
public:
    Dslk();
    ~Dslk();

    void display();

    void push();
    void print();
    void print_diem();
    void findMsv();
    void Sort();
    void BinarySearch();
    void deleteMsvX();
    void updateDtb();
};
Dslk::Dslk() : pHead(nullptr), _iSize(0) {}
Dslk::~Dslk(){
    while (pHead != nullptr) {
        Node* temp = pHead;
        pHead = pHead->pNext;
        delete temp;
    }
}

void Dslk::display() {
    cout << "\t\t\tCHUONG TRINH QUAN LY DANH SACH SINH VIEN CUA MOT LOP\n";
    system("pause");
    char _cLuaChon;
    do {
        cout << "\n";
        cout << "1. Nhap danh sach lien ket cac sinh vien\n";
        cout << "2. Xuat danh sach ra man hinh\n";
        cout << "3. In ra danh sach cac sinh vien co diem trung binh lon hon hoac bang 5\n";
        cout << "4. Tim tuan tu thong tin cua mot sinh vien theo ma sinh vien\n";
        cout << "5. Sap xep danh sach sinh vien tang dan theo ma sinh vien dùng giai thuat chon truc tiep\n";
        cout << "6. Tim nhi phan thong tin cua mot sinh vien theo ma sinh vien\n";
        cout << "7. Tim va xoa sinh vien co ma sinh vien la x, voi x nhap tu ban phim\n";
        cout << "8. Cap nhat lai diem trung binh cua sinh vien co ma sinh vien la x\n";
        cout << "Nhan 'e' de thoat khoi ung dung\n";
        cout << "\n";
        cout << "Chuc nang ban chon la: ";
        cin >> _cLuaChon;
        cout << "\n\n";

        system("cls");
        switch (_cLuaChon) {
        case '1':
            cout << "\n[+]. Nhap danh sach lien ket cac sinh vien\n";    
            push();
            cout << "Hoan tat!\n";
            break;
        case '2':
            cout << "\n[+]. Xuat danh sach ra man hinh\n";
            print();
            cout << "Hoan tat!\n";
            break;
        case '3':
            cout << "\n[+]. In ra danh sach cac sinh vien co diem trung binh lon hon hoac bang 5\n";
            print_diem();
            cout << "Hoan tat!\n";
            break;
        case '4':
            cout << "\n[+]. Tim tuan tu thong tin cua mot sinh vien theo ma sinh vien\n";
            findMsv();
            cout << "Hoan tat!\n";
            break;
        case '5':
            cout << "\n[+]. Sap xep danh sach sinh vien tang dan theo ma sinh vien dung giai thuat chon truc tiep\n";
            Sort();
            cout << "Hoan tat!\n";
            break;
        case '6':
            cout << "\n[+]. Tim nhi phan thong tin cua mot sinh vien theo ma sinh vien\n";
            BinarySearch();
            cout << "Hoan tat!\n";
            break;
        case '7':
            cout << "\n[+]. Tim va xoa sinh vien co ma sinh vien la x, voi x nhap tu ban phim\n";
            deleteMsvX();
            cout << "Hoan tat!\n";
            break;
        case '8':
            cout << "\n[+]. Cap nhat lai diem trung binh cua sinh vien co ma sinh vien la x\n";
            updateDtb();
            cout << "Hoan tat!\n";
            break;
        default:
            cout << "Cam on ban da su dung ung dung!\nThanks";
            break;
        }
        system("pause");
        system("cls");
    } while (_cLuaChon != 'e');
}


void Dslk::push(){
        int n;
        cout << "Nhap so luong sinh vien: ";
        cin >> n;
        SinhVien _sv;
        while(n--){
            _sv.nhap();
            Node* node= new Node(_sv);
            if(pHead == nullptr){
                pHead = node;
            }
            else{
                Node *pTemp = pHead;
                while(pTemp -> pNext != nullptr){
                    pTemp = pTemp -> pNext;
                }
                pTemp -> pNext = node;
            }
            _iSize++;
        }
}

void Dslk::print(){
    Node *pTemp = pHead;
    while(pTemp != nullptr){
        pTemp -> xuat();
        pTemp = pTemp -> pNext;
    }
}

void Dslk::print_diem(){
    Node* ptemp = pHead;
    while(ptemp != nullptr){
        if(ptemp->data._dtb >= 5)  ptemp->data.xuat();
        ptemp = ptemp->pNext;
    }
}

void Dslk::findMsv(){
    string _masv;
    cout << "Nhap ma sinh vien can tim: ";
    cin >> _masv;
    Node* pTemp = pHead;
    while(pTemp != nullptr && pTemp->data._sMsv != _masv) {
        pTemp = pTemp->pNext;
    }
    if(pTemp == nullptr) cout << "Ma sinh vien khong hop le!\n";
    else pTemp->data.xuat();
}

void Dslk::Sort(){
    Node* p1;
    Node* p2;
    for(p1 = pHead; p1 -> pNext != nullptr; p1 = p1 -> pNext ){
        Node* p = p1;
        for(p2 = p1 -> pNext; p2 != nullptr; p2 = p2 -> pNext ){
            if(p1 -> data._sMsv > p2 -> data._sMsv) swap(p1 -> data, p2 -> data);
        }
        swap(p1 -> data, p -> data);
    }
}

void Dslk::BinarySearch(){
    Sort();

    string _masv;
    cout << "Nhap ma sinh vien can tim: ";
    cin >> _masv;

    Node* p1 = pHead;
    Node* p2 = pHead;
    Node* pd = pHead;
    Node* pc = nullptr;

    while(pd != pc){
        p1 = pd;
        p2 = pd;

        while(p2 != nullptr && p2->pNext != nullptr){
            p1 = p1->pNext;
            p2 = p2->pNext->pNext;
        }

        if(p1->data._sMsv == _masv) {
            p1->data.xuat();
            return ;
        }

        if(p1->data._sMsv < _masv){
            pd = p1->pNext;
        }
        else pc = p1;
    }
    cout << "Khong tim thay!\n";
}

void Dslk::deleteMsvX(){
    string _masv;
    cout << "Nhap ma sinh vien can xoa: ";
    cin >> _masv;
    Node* pTemp = pHead;
    Node* pPre = nullptr;
    while(pTemp != nullptr && pTemp->data._sMsv != _masv) {
        pPre = pTemp;
        pTemp = pTemp->pNext;
    }
    if(pTemp == nullptr) cout << "Ma sinh vien khong hop le!\n";
    else {
        if(pPre == nullptr) {
            pHead = pTemp->pNext;
            delete pTemp;
        }
        else{
            pPre->pNext = pTemp->pNext;
            delete pTemp;
        } 
    };
}

void Dslk::updateDtb(){
    string _masv;
    cout << "Nhap ma sinh vien can cap nhat diem trung binh: ";
    cin >> _masv;
    Node* pTemp = pHead;
    while(pTemp != nullptr && pTemp->data._sMsv != _masv) {
        pTemp = pTemp->pNext;
    }
    if(pTemp == nullptr) cout << "Ma sinh vien khong hop le!\n";
    else {
        cout << "Nhap diem moi: ";
        cin >> pTemp->data._dtb;
    };
}

int main(){
    Dslk _dslk;
    _dslk.display();
    return 0;
}