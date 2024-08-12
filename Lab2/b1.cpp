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
    void removeX();
    void printArr();
};

int main(){
    Array<string> _arr;
    _arr.input();
    _arr.removeX();
    _arr.printArr();
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
void Array<DataType>::removeX(){
    DataType x;
    cout << "Nhap gia tri can xoa: "; 
    cin >> x;
    cout<<endl; 
    int i = 0, check = 0;
    while(check < _iSize){
        while (_arr[check] != x && check < _iSize) _arr[i++] = _arr[check++];
        check++;
    }
    _iSize = i;
}

template <class DataType>
void Array<DataType>::printArr(){
    cout << "Mang sau khi xoa: \n";
    for(int i = 0; i < _iSize; i++) cout << _arr[i] <<" ";
}
