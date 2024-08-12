#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

class Film {
public:
    string _tenFilm;
    string _type;
    string _tenDaodien;
    string _tenMainMale;
    string _tenMainFemale;
    int _nsx;

    Film() {};
    Film(string _tenFilm, string _type, string _tenDaodien, string _tenMainMale, string _tenMainFemale, int _nsx) {
        this->_tenFilm = _tenFilm;
        this->_type = _type;
        this->_tenDaodien = _tenDaodien;
        this->_tenMainMale = _tenMainMale;
        this->_tenMainFemale = _tenMainFemale;
        this->_nsx = _nsx;
    }

    friend ostream& operator<<(ostream& cout, const Film& film) {
        cout << film._tenFilm << "#" << film._type << "#" << film._tenDaodien << "#";
        cout << film._tenMainMale << "#" << film._tenMainFemale << "#" << film._nsx;
        return cout;
    }

    void xuat() const {
        cout << "Phim: " << _tenFilm << "\n"
             << "The loai: " << _type << "\n"
             << "Dao dien: " << _tenDaodien << "\n"
             << "Nam chinh: " << _tenMainMale << "\n"
             << "Nu chinh: " << _tenMainFemale << "\n"
             << "Nam xuat ban: " << _nsx << "\n\n";
    }
};

class Dslk;

class Node {
private:
    Film data;
    Node* pNext;

public:
    friend Dslk;

    Node(Film data);
};

Node::Node(Film _data) : data(_data), pNext(nullptr) {}

class Dslk {
private:
    Node* pHead;
    int _iSize;

public:
    Dslk();
    ~Dslk();

    void push(Film);
    void Sort();

    void readFile();
    void update();
    void print() const;
    void filmMainMale();
    void listedDaodien();
    void moiNhat();
};

Dslk::Dslk() : pHead(nullptr), _iSize(0) {}

Dslk::~Dslk() {
    while (pHead != nullptr) {
        Node* temp = pHead;
        pHead = pHead->pNext;
        delete temp;
    }
}

void Dslk::push(Film film) {
    Node* node = new Node(film);
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

void Dslk::Sort() {
    for (Node* p1 = pHead; p1 != nullptr; p1 = p1->pNext) {
        for (Node* p2 = p1->pNext; p2 != nullptr; p2 = p2->pNext) {
            if (p1->data._nsx < p2->data._nsx) {
                swap(p1->data, p2->data);
            }
        }
    }
}

void Dslk::readFile() {
    ifstream FileIN("input.txt");
    if (!FileIN.is_open()) {
        cerr << "Could not open the file!" << endl;
        return;
    }

    string _tenFilm, _type, _tenDaodien, _tenMainMale, _tenMainFemale;
    int _nsx;

    while (getline(FileIN, _tenFilm, '#')) {
        getline(FileIN, _type, '#');
        getline(FileIN, _tenDaodien, '#');
        getline(FileIN, _tenMainMale, '#');
        getline(FileIN, _tenMainFemale, '#');
        FileIN >> _nsx;
        FileIN.ignore(); // Ignore the newline character
        push(Film(_tenFilm, _type, _tenDaodien, _tenMainMale, _tenMainFemale, _nsx));
    }

    FileIN.close();
}

void Dslk::update() {
    string _filmX, type;
    cout << "Nhap ten film: ";
    getline(cin, _filmX);
    cout << "Nhap 1 trong 3 the loai (hinhsu, tinhcam, hai): ";
    getline(cin, type);

    Node* pTemp = pHead;
    while (pTemp != nullptr && pTemp->data._tenFilm != _filmX) {
        pTemp = pTemp->pNext;
    }

    if (pTemp == nullptr) {
        cout << "Khong co film!\n";
    } else {
        pTemp->data._type = type;

        vector<Film> fi;
        ifstream FileIN("input.txt");
        string _tenFilm, _type, _tenDaodien, _tenMainMale, _tenMainFemale;
        int _nsx;

        while (getline(FileIN, _tenFilm, '#')) {
            getline(FileIN, _type, '#');
            getline(FileIN, _tenDaodien, '#');
            getline(FileIN, _tenMainMale, '#');
            getline(FileIN, _tenMainFemale, '#');
            FileIN >> _nsx;
            FileIN.ignore(); // Ignore the newline character

            if (pTemp->data._tenFilm == _tenFilm) {
                fi.push_back(Film(_tenFilm, type, _tenDaodien, _tenMainMale, _tenMainFemale, _nsx));
            } else {
                fi.push_back(Film(_tenFilm, _type, _tenDaodien, _tenMainMale, _tenMainFemale, _nsx));
            }
        }

        FileIN.close();

        ofstream FileOUT("input.txt");
        for (Film s : fi) {
            FileOUT << s << "\n";
        }
        FileOUT.close();
    }
}

void Dslk::print() const {
    Node* pTemp = pHead;
    while (pTemp != nullptr) {
        pTemp->data.xuat();
        pTemp = pTemp->pNext;
    }
}

void Dslk::filmMainMale() {
    string _nameMain;
    cout << "Nhap ten dien vien: ";
    getline(cin, _nameMain);

    ofstream FileOUT(_nameMain + ".txt");
    Node* pTemp = pHead;
    while (pTemp != nullptr) {
        if (pTemp->data._tenMainMale == _nameMain) {
            FileOUT << pTemp->data._tenFilm << "\n";
        }
        pTemp = pTemp->pNext;
    }
    FileOUT.close();
}

void Dslk::listedDaodien() {
    map<string, vector<Film>> _filmDaodien;
    Node* pTemp = pHead;
    while (pTemp != nullptr) {
        _filmDaodien[pTemp->data._tenDaodien].push_back(pTemp->data);
        pTemp = pTemp->pNext;
    }

    for (auto& x : _filmDaodien) {
        ofstream FileOUT(x.first + ".txt");
        FileOUT << "Tong so bo film: " << x.second.size() << "\n\n";
        for (Film k : x.second) {
            FileOUT << k << "\n";
        }
        FileOUT.close();
    }
}

void Dslk::moiNhat() {
    Sort();
    ofstream FileOUT("PhimMoi.txt");
    int n = 3;
    Node* pTemp = pHead;
    while (pTemp != nullptr && n--) {
        FileOUT << pTemp->data << "\n";
        pTemp = pTemp->pNext;
    }
    FileOUT.close();
}

int main() {
    Dslk _ds;
    _ds.readFile();
    _ds.print();
    _ds.update();
    _ds.print();
    _ds.filmMainMale();
    _ds.listedDaodien();
    _ds.moiNhat();
    return 0;
}
