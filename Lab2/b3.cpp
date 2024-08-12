#include<iostream>
#include<vector>
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
    void fibydivideX();
    void printArr();
};

int main(){
    Array<int> _arr;
    _arr.input();
    _arr.fibydivideX();
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
void Array<DataType>::fibydivideX() {
    DataType x;
    cout <<"Nhap gia tri cua x: ";
    cin >> x;
    cout << endl;
    vector< pair<int,int> > sav;

    int l = 0;
    int r = _iSize - 1;
    int count = 0;

    while(l <= r){
        int mid = (l + r)/2;
        if(_arr[mid] > x) {
            r = mid - 1;
        }
        else if(_arr[mid] < x) {
            l = mid + 1;
        }
        if(_arr[mid] == x) break;
        sav.push_back({l,r});
        count++;
    }

    cout << "So lan chia doi mang la: ";
    if(!count) cout << 0;
    else {
        cout << count <<endl;
        for(int i = 0; i < count; i++){
            printf("Lan %d: x=%d nam trong doan [%d..%d] \n",i+1,x,sav[i].first,sav[i].second);
        }
    }


}

template <class DataType>
void Array<DataType>::printArr() {
    for (int i = 0; i < _iSize; i++) cout << _arr[i] << " ";
}
