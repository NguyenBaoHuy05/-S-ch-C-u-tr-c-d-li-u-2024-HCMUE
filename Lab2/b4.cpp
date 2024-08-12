#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAX_MASV = 11;
const float DHB = 7.0;
const float DAT_YCHB = 5.0;
const string NG_TH_NAM_SINH = "01/01/1990";
const int NAM = 1900;


typedef struct MON {
    string _strMaMon;
    string _strTenMon;
    int _iSotc;
    float _fDiem;

    friend istream& operator>>(istream& in, MON& p) {
        cout << "Nhap ma mon: ";
        in >> p._strMaMon;
        cout << "Nhap ten mon: ";
        in.ignore();
        getline(in, p._strTenMon);
        cout << "Nhap so tin chi: ";
        in >> p._iSotc;
        p._iSotc = p._iSotc < 1 ? 1 : (p._iSotc > 5 ? 5 : p._iSotc); 
        cout << "Nhap diem: ";
        in >> p._fDiem;
        p._fDiem = p._fDiem < 0 ? 0 : (p._fDiem > 10 ? 10 : p._fDiem); 
        return in;
    }

    friend ostream& operator<<(ostream& os, MON& p) {
        os << "Ma mon: " << p._strMaMon << "\n";
        os << "Ten mon: " << p._strTenMon << "\n";
        os << "So tin chi: " << p._iSotc << "\n";
        os << "Diem: " << p._fDiem << "\n";
        return os;
    }
}  MON;

class SinhVien {
private:
    string _strMsv;
    string _strHoTen;
    string _strNgaySinh;
    int _strSoMon;
    MON* _pMon;
public:
    SinhVien();
    ~SinhVien();
    SinhVien& operator=(const SinhVien& other);

    string getMsv();
    void setTen(string);
    string getTen();

    void nhap();
    void xuat() const;
    float getDtb();
    bool ycHb();
    int getNs();

    ///Bổ trợ
    void doicho(SinhVien& b);
};

class Qlsv {
private:
    int _iSv;
    SinhVien* _pSv;
public:
    Qlsv();
    ~Qlsv();

    void nhap();
    void xuat() const;
    void linearchangeInfo();
    void insertionsortHoten();
    void binarydeleteSv();
    void selectionsortDiemtb();
    void printHb();
    void quicksortNs(int, int);
    ///
    int getiSv();
};

class App {
private:
    Qlsv* _qlsv;
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

SinhVien::SinhVien() : _strMsv(MAX_MASV, ' ') {
    _strMsv = "00000000000";
    _strHoTen = "NNN";
    _strNgaySinh = "01/01/1990";
    _strSoMon = 0;
    _pMon = nullptr;
}

SinhVien::~SinhVien() {
    delete[] _pMon;
}
SinhVien& SinhVien::operator=(const SinhVien& other) {
    if (this != &other) {
        delete[] _pMon;
        _strMsv = other._strMsv;
        _strHoTen = other._strHoTen;
        _strNgaySinh = other._strNgaySinh;
        _strSoMon = other._strSoMon;
        if (other._pMon) {
            _pMon = new MON[_strSoMon];
            for (int i = 0; i < _strSoMon; ++i) {
                _pMon[i] = other._pMon[i];
            }
        }
        else {
            _pMon = nullptr;
        }
    }
    return *this;
}
string SinhVien::getMsv() { return _strMsv; }
void SinhVien::setTen(string s) { _strHoTen = s; }
string SinhVien::getTen() { return _strHoTen; }

void SinhVien::nhap() {
    cout << "Nhap mssv: ";
    cin >> _strMsv;
    while(_strMsv.length() < MAX_MASV) _strMsv += '0';
    if(_strMsv.length() > MAX_MASV) _strMsv = _strMsv.substr(0,11);
    cout << "Nhap ho va ten sinh vien: ";
    cin.ignore();
    getline(cin, _strHoTen);
    cout << "Nhap ngay sinh: ";
    cin >> _strNgaySinh;
    _strNgaySinh = (stoi(_strNgaySinh.substr(6)) < NAM || _strNgaySinh.length() != 10) ? NG_TH_NAM_SINH : _strNgaySinh;
    cout << "Nhap so mon: ";
    cin >> _strSoMon;
    delete[] _pMon;
    _pMon = new MON[_strSoMon];
    for (int i = 0; i < _strSoMon; i++) {
        printf("Mon %d:\n", i + 1);
        cin >> _pMon[i];
    }
}

void SinhVien::xuat() const {
    cout << "Mssv: " << _strMsv << "\n";
    cout << "Ho va ten sinh vien: " << _strHoTen << "\n";
    cout << "Ngay sinh: " << _strNgaySinh << "\n";
    cout << "So mon: " << _strSoMon << "\n";
    cout << "Cac mon da hoc: \n";
    for (int i = 0; i < _strSoMon; i++) {
        cout << _pMon[i];
    }
}

float SinhVien::getDtb() {
    float diemtong = 0;
    int stctong = 0;
    for (int i = 0; i < _strSoMon; i++) {
        diemtong += _pMon[i]._fDiem * _pMon[i]._iSotc;
        stctong += _pMon[i]._iSotc;
    }
    if (stctong == 0) return 0; // Avoid division by zero
    diemtong /= stctong;
    return diemtong;
}

bool SinhVien::ycHb() {
    for (int i = 0; i < _strSoMon; i++) {
        if (_pMon[i]._fDiem < DAT_YCHB) return false;
    }
    return true;
}

int SinhVien::getNs() {
    return stoi(_strNgaySinh.substr(6));
}

void SinhVien::doicho(SinhVien& b) {
    swap(_strMsv, b._strMsv);
    swap(_strHoTen, b._strHoTen);
    swap(_strNgaySinh, b._strNgaySinh);
    swap(_strSoMon, b._strSoMon);

    // Hoán đổi con trỏ
    swap(_pMon, b._pMon);
}
/**************************************** */

Qlsv::Qlsv() {
    _iSv = 0;
    _pSv = nullptr;
}

Qlsv::~Qlsv() {
    delete[] _pSv;
}

void Qlsv::nhap() {
    cout << "Nhap so luong sinh vien can nhap: ";
    cin >> _iSv;
    delete[] _pSv;
    _pSv = new SinhVien[_iSv];
    int i = 0;
    while (i < _iSv) {
        printf("\n%d. \n", i + 1);
        _pSv[i].nhap();
        i++;
    }
    cout << "\n\n Nhap hoan tat!\n\n";
}

void Qlsv::xuat() const {
    cout << "Danh sach sinh vien: \n";
    for (int i = 0; i < _iSv; i++) {
        printf("%d . \n", i + 1);
        _pSv[i].xuat();
        cout << "\n";
    }
}

void Qlsv::linearchangeInfo() {
    string _sMSSuaten(MAX_MASV, ' ');
    cout << "Nhap mssv cua hoc sinh can sua ten: ";
    cin >> _sMSSuaten;
    int i;
    for (i = 0; i < _iSv && _pSv[i].getMsv() != _sMSSuaten; i++);
    if (i == _iSv) cout << "Khong tim thay mssv trung khop\n";
    else {
        string s;
        cout << "Nhap ten thay doi: ";
        cin.ignore();
        getline(cin, s);
        _pSv[i].setTen(s);
        cout << "Thay doi hoan tat!\n\n";
    }
}

void Qlsv::insertionsortHoten() {
    int pos, i;
    SinhVien x;
    for (i = 1; i < _iSv; i++) {
        x = _pSv[i];
        for (pos = i; pos > 0 && _pSv[pos - 1].getTen() < x.getTen(); pos--) {
            _pSv[pos] = _pSv[pos - 1];
        }
        _pSv[pos] = x;
    }
    cout << "Hoan tat!\n\n";
    xuat();
}

void Qlsv::binarydeleteSv() {
    sort(_pSv, _pSv + _iSv, [](SinhVien a, SinhVien b) {
        return a.getTen() < b.getTen();
        });

    string s;
    cout << "Nhap ten sinh vien can xoa: ";
    cin.ignore();
    getline(cin, s);

    int l = 0, r = _iSv - 1;
    int vt = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (_pSv[mid].getTen() == s) {
            vt = mid;
            break;
        }
        else if (_pSv[mid].getTen() < s) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }

    if (vt == -1) {
        cout << "Khong co ten trong co so du lieu!\n";
    }
    else {
        for (int i = vt; i < _iSv - 1; ++i) {
            _pSv[i] = _pSv[i + 1];
        }
        --_iSv;
        SinhVien* newSv = new SinhVien[_iSv];
        for (int i = 0; i < _iSv; ++i) {
            newSv[i] = _pSv[i];
        }
        delete[] _pSv;
        for (int i = 0; i < _iSv; ++i) {
            _pSv[i] = newSv[i];
        }
        delete[] newSv;
        cout << "Xoa thanh cong!\n\n";
    }
}

void Qlsv::selectionsortDiemtb() {
    for (int i = 0; i < _iSv - 1; i++) {
        int min = i;
        for (int j = i + 1; j < _iSv; j++) {
            if (_pSv[j].getDtb() < _pSv[min].getDtb()) min = j;
        }
        if (min != i) _pSv[i].doicho(_pSv[min]);
    }
    cout << "Hoan tat!\n";
}

void Qlsv::printHb() {
    selectionsortDiemtb();
    bool found = false;
    for (int i = _iSv - 1; i >= 0; i--) {
        if (_pSv[i].getDtb() < 7.0) break;
        else if (_pSv[i].ycHb()) {
            cout << _pSv[i].getTen() << "\n" << _pSv[i].getDtb() << "\n";
            found = true;
        }
    }
    if (!found) cout << "\nKhong co sinh vien nao nhan duoc hoc bong!\n";
    cout << "Hoan tat!\n";
}

void Qlsv::quicksortNs(int left, int right) {
    int x = _pSv[left].getNs();
    int i,j;
    if(left >= right) return ;
    i = left;
    j = right;
    while(i < j) {
        while(_pSv[i].getNs() < x) i++;
        while(_pSv[i].getNs() > x) j--;
        if( i <= j) {
            _pSv[i].doicho(_pSv[j]);
            i++;j--;
        }
    }
    quicksortNs(left, j);
    quicksortNs(i, right);
}

int Qlsv::getiSv() {
    return _iSv;
}
/**************************************** */

App::App(){_qlsv = new Qlsv;}
App::~App(){delete _qlsv;}

void App::display() {
    cout << "\t\t\tAPP QUAN LY SINH VIEN TRUONG ABC\n";
    system("pause");
    do {
        cout << "\n";
        cout << "1. Nhap danh sach sinh vien\n";
        cout << "2. Tim kiem va sua doi ho ten sinh vien\n";
        cout << "3. Sap xep ho ten sinh vien giam dan\n";
        cout << "4. Tim kiem va xoa sinh vien\n";
        cout << "5. Sap xep sinh vien theo diem trung binh tang dan\n";
        cout << "6. In danh sach ten cac sinh vien duoc hoc bong\n";
        cout << "7. Sap xep sinh vien theo nam sinh tang dan\n";
        cout << "8. Xuat thong tin sinh vien\n";
        cout << "Nhan 'e' de thoat khoi ung dung\n";
        cout << "\n";
        cout << "Chuc nang ban chon la: ";
        cin >> _cLuaChon;
        cout << "\n\n";

        system("cls");
        switch (_cLuaChon) {
        case '1':
            cout << "\n[+] Nhap danh sach sinh vien:\n";
            _qlsv->nhap();
            break;
        case '2':
            cout << "\n[+] Tim kiem va sua doi ho ten sinh vien\n";
            _qlsv->linearchangeInfo();
            break;
        case '3':
            cout << "\n[+] Sap xep ho ten sinh vien giam dan\n";
            _qlsv->insertionsortHoten();
            break;
        case '4':
            cout << "\n[+] Tim kiem va xoa sinh vien\n";
            _qlsv->binarydeleteSv();
            break;
        case '5':
            cout << "\n[+] Sap xep sinh vien theo diem trung binh tang dan\n";
            _qlsv->selectionsortDiemtb();
            break;
        case '6':
            cout << "\n[+] In danh sach ten cac sinh vien duoc hoc bong \n";
            _qlsv->printHb();
            break;
        case '7':
            cout << "\n[+] Sap xep sinh vien theo nam sinh tang dan\n";
            _qlsv->quicksortNs(0, _qlsv->getiSv());
             cout << "Hoan tat!\n\n";
            break;
        case '8':
            cout << "\n[+] Xuat thong tin sinh vien\n";
             _qlsv->xuat();
            break;
        default:
            cout << "Cam on ban da su dung ung dung!\nThanks";
            break;
        }
        system("pause");
        system("cls");
    } while (_cLuaChon != 'e');
}

/**************************************** */
