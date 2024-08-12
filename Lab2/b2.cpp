#include<iostream>
using namespace std;

template <class DataType>
class Array{
private:
    int _iSize;
    DataType* _arr;
public:
    Array();
    Array(DataType* arr, int n);
    ~Array();

    void input();
    void findallX();
    void printArr();
};

int main(){
    Array<int> _arr;
    _arr.input();
    _arr.findallX();
    return 0;
}

template <class DataType>
Array<DataType>::Array(){
    _iSize = 0;
    _arr = new DataType[10];
}

template <class DataType>
Array<DataType>::Array(DataType* arr, int n){
    _iSize = n;
    _arr = new DataType[n];
    for(int i = 0; i < n;i++) _arr[i] = arr[i];
}

template <class DataType>
Array<DataType>::~Array(){
    _iSize = 0;
    delete[] _arr;    
}

template <class DataType>
void Array<DataType>::input(){
    while(true){
        cout << "Nhap so luong phan tu: ";
        cin >> _iSize;
        cout << endl;
        if(_iSize < 1) cout << "Nhap sai!\n";
        else {
            break;
        }
    }
    _arr = new DataType[_iSize];
    cout << "Nhap cac phan tu cua mang:\n";
    for(int i = 0; i < _iSize; i++) cin >> _arr[i];
    cout << endl;
}

template < class DataType>
void Array<DataType>::findallX() {
    DataType x;
    cout << "Nhap phan tu can tim: ";
    cin >> x;
    cout<< "\nCac vi tri cua phan tu do la: \n";
    for (int i = 0; i < _iSize; i++) {
        if(_arr[i] == x) cout << i << " ";
    }
}

template <class DataType>
void Array<DataType>::printArr() {
    for (int i = 0; i < _iSize; i++) cout << _arr[i] << " ";
}
