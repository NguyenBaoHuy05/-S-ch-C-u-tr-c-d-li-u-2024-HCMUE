#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAX_strMs = 6; 
const int MAX_strTua = 30;
const int NAM = 1900;
const int GIA = 6;
const int GIA_MD = 999999;

class Sach {
private:
    string _strMs;
    string _strTua;
    int _iNxb;
    int _iGia;
public:
    Sach();
    ~Sach();
    Sach& operator=(const Sach& other);

    string getTua() const;
    string getMs() const;
    int getNxb() const;
    int getGia() const;
    void setGia(int);

    void nhap();
    void xuat() const;

    ///Bổ trợ
    void doicho(Sach& b);
};

class Qls {
private:
    int _iCount;
    Sach* _pSach;
public:
    Qls();
    ~Qls();

    void nhap();
    void xuat() const;
    void searchTuaX();
    void searchdeleteMsX();
    void selectionsortMs();
    void insertionsortNxb();
    void bubblesortTua();
    void quicksortGia(int, int);

    ///Ham bo tro
    int getiCount();
};

class App {
private:
    Qls* _pQls;
    char _cLuaChon;
public:
    App();
    ~App();

    void display();
};

int main() {
    App app;
    app.display();
    return 0;
}

/**************************************** */

Sach::Sach() {
    _strMs = "000000";
    _strTua = "NNN";
    _iNxb = 1900;
    _iGia = 0;
}

Sach::~Sach() {}
Sach& Sach::operator=(const Sach& other) {
    _strMs = other._strMs;
    _strTua = other._strTua;
    _iNxb = other._iNxb;
    _iGia = other._iGia;
    return *this;
}
string Sach::getTua() const {return _strTua;}
string Sach::getMs() const {return _strMs;}
int Sach::getNxb() const {return _iNxb;}
int Sach::getGia() const {return _iGia;}
void Sach::setGia(int giamoi){_iGia = giamoi;}

void Sach::nhap() {
    cout << "Nhap ma sach: ";
    cin >> _strMs;
    if (_strMs.length() > MAX_strMs) _strMs = _strMs.substr(0, MAX_strMs);
    cout << "Nhap tua sach: ";
    cin >> _strTua;
    if (_strTua.length() > MAX_strTua) _strMs = _strMs.substr(0, MAX_strTua);
    cout << "Nhap nam xuat ban: ";
    cin >> _iNxb;
    if (_iNxb < 1900) _iNxb = NAM + 1;
    cout << "Nhap gia: ";
    cin >> _iGia;
    if(_iGia > pow(10,GIA + 1)) _iGia = GIA_MD;
}

void Sach::xuat() const {
    cout << "Ma sach: " << _strMs << "\n";
    cout << "Tua sach: " << _strTua << "\n";
    cout << "Nam xuat ban: " << _iNxb << "\n";
    cout << "Gia: " << _iGia << "\n";
}

void Sach::doicho(Sach& b) {
    swap(_strMs, b._strMs);
    swap(_strTua, b._strTua);
    swap(_iNxb, b._iNxb);
    swap(_iGia, b._iGia);
}
// /**************************************** */

Qls::Qls() {
    _iCount = 0;
    _pSach = nullptr;
}

Qls::~Qls() {
    delete[] _pSach;
}

void Qls::nhap() {
    cout << "Nhap so luong sach co trong thu vien: ";
    cin >> _iCount;
    _pSach = new Sach[_iCount];
    cout << "\n";
    for(int i = 0; i < _iCount; i++) {
        printf("Cuon %d:\n",i + 1);
        _pSach[i].nhap();
        cout << "\n";
    }
    cout << "\n\n Nhap hoan tat!\n\n";
}

void Qls::xuat() const {
    cout << "\nDanh sach cac cuon sach co trong thu vien: \n\n";
    for (int i = 0; i < _iCount; i++) {
        printf("Cuon %d . \n", i + 1);
        _pSach[i].xuat();
        cout << "\n";
    }
}

void Qls::searchTuaX() {
    string _sTuaX;
    cout << "Nhap tua sach can tim: ";
    cin >> _sTuaX;
    int i;
    for (i = 0; i < _iCount && _pSach[i].getTua() != _sTuaX; i++);
    if (i == _iCount) cout << "Khong tim thay tua sach trung khop\n";
    else {
        int giamoi;
        cout << "Nhap gia moi: ";
        cin >> giamoi;
        _pSach[i].setGia(giamoi);
        cout << "Thay doi hoan tat!\n\n";
    }
}

void Qls::searchdeleteMsX() {
    sort(_pSach, _pSach + _iCount, [](Sach a, Sach b) {
    return a.getMs() < b.getMs();
    });

    string s;
    cout << "Nhap ma sach can xoa: ";
    cin >> s;

    int l = 0, r = _iCount - 1;
    int vt = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (_pSach[mid].getMs() == s) {
            vt = mid;
            break;
        }
        else if (_pSach[mid].getMs() < s) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }

    if (vt == -1) {
        cout << "Khong co cuon sach co ma " << s <<"!\n";
    }
    else {
        for (int i = vt; i < _iCount - 1; ++i) {
            _pSach[i] = _pSach[i + 1];
        }
        --_iCount;
        Sach* newSach = new Sach[_iCount];
        for (int i = 0; i < _iCount; ++i) {
            newSach[i] = _pSach[i];
        }
        delete[] _pSach;
        for (int i = 0; i < _iCount; ++i) {
            _pSach[i] = newSach[i];
        }
        delete[] newSach;
        cout << "Xoa thanh cong!\n\n";
    }
}

void Qls::selectionsortMs() {
    for (int i = 0; i < _iCount - 1; i++) {
        int min = i;
        for (int j = i + 1; j < _iCount; j++) {
            if (_pSach[j].getMs() < _pSach[min].getMs()) min = j;
        }
        if (min != i) _pSach[i].doicho(_pSach[min]);
    }
    cout << "Hoan tat!\n";
}

void Qls::insertionsortNxb() {
    int pos, i;
    Sach x;
    for (i = 1; i < _iCount; i++) {
        x = _pSach[i];
        for (pos = i; pos > 0 && _pSach[pos - 1].getNxb() < x.getNxb(); pos--) {
            _pSach[pos] = _pSach[pos - 1];
        }
        _pSach[pos] = x;
    }
    cout << "Hoan tat!\n";
}

void Qls::bubblesortTua(){
    for(int i = 0; i < _iCount - 1; i++){
        for(int j = _iCount - 1; j > i; j--){
            if(_pSach[j].getGia() > _pSach[j - 1].getGia()) _pSach[j].doicho(_pSach[j - 1]);
        }
    }
    cout << "Hoan tat!\n";
}

void Qls::quicksortGia(int left, int right) {
    int x = _pSach[left].getGia();
    int i,j;
    if(left >= right) return ;
    i = left;
    j = right;
    while(i < j) {
        while(_pSach[i].getGia() < x) i++;
        while(_pSach[i].getGia() > x) j--;
        if( i <= j) {
            _pSach[i].doicho(_pSach[j]);
            i++;j--;
        }
    }
    quicksortGia(left, j);
    quicksortGia(i, right);
}

int Qls::getiCount(){return _iCount;}

// /**************************************** */

App::App(){_pQls = new Qls;}
App::~App(){delete _pQls;}

void App::display() {
    cout << "\t\t\tAPP QUAN LY SACH THU VIEN\n";
    system("pause");
    do {
        cout << "\n";
        cout << "1. Nhap danh sach cac cuon sach\n";
        cout << "2. Xuat thong tin cac cuon sach\n";
        cout << "3. Tim kiem cuon sach co tua la X co ton tai khong va sua gia\n";
        cout << "4. Tim kiem va xoa cuon sach co ma la X\n";
        cout << "5. Sap xep cuon sach tang dan theo ma sach\n";
        cout << "6. Sap xep cuon sach giam dan theo nam xuat ban\n";
        cout << "7. Sap xep cuon sach tang dan theo tua sach\n";
        cout << "8. Sap xep cuon sach giam dan theo gia sach\n";
        cout << "Nhan 'e' de thoat khoi ung dung\n";
        cout << "\n";
        cout << "Chuc nang ban chon la: ";
        cin >> _cLuaChon;
        cout << "\n\n";

        system("cls");
        switch (_cLuaChon) {
        case '1':
            cout << "\n[+]. Nhap danh sach cac cuon sach\n";    
            _pQls->nhap();
            break;
        case '2':
            cout << "\n[+]. Xuat thong tin cac cuon sach\n";
            _pQls->xuat();
            break;
        case '3':
            cout << "\n[+]. Tim kiem cuon sach co tua la X co ton tai khong\n";
            _pQls->searchTuaX();
            break;
        case '4':
            cout << "\n[+]. Tim kiem va xoa cuon sach co ma la X\n";
            _pQls->searchdeleteMsX();
            break;
        case '5':
            cout << "\n[+]. Sap xep cuon sach tang dan theo ma sach\n";
            _pQls->selectionsortMs();
            break;
        case '6':
            cout << "\n[+]. Sap xep cuon sach giam dan theo nam xuat ban\n";
            _pQls->insertionsortNxb();
            break;
        case '7':
            cout << "\n[+]. Sap xep cuon sach tang dan theo tua sach\n";
            _pQls->bubblesortTua();
            break;
        case '8':
            cout << "\n[+]. Sap xep cuon sach giam dan theo gia sach\n";
            _pQls->quicksortGia(0, _pQls->getiCount());
            cout << "Hoan tat!\n\n";
            break;
        default:
            cout << "Cam on ban da su dung ung dung!\nThanks";
            break;
        }
        system("pause");
        system("cls");
    } while (_cLuaChon != 'e');
}
