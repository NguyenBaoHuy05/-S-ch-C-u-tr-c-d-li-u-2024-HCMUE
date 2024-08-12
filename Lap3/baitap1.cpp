#include<iostream>
#include<algorithm>
#include<cmath>
#include<set>
using namespace std;

class Dslk;
class Node{
private:
    int data;
    Node* next;
public:
    friend Dslk;

    Node(int data);
    void display();
};
Node::Node(int _data){
    data = _data;
    next = nullptr;
}
void Node::display(){
    cout << data << " ";
}
class Dslk{
private:
    Node* pHead;
    int _iSize;
public:
    Dslk();
    ~Dslk();

    void push(int);
    void print();
    void print_primes();
    void average();
    void current(int);
    void lastChinhPhuong();
    Node* findPosK(int);
    void findMin();
    void insertNode(Node*, int);
    void addNotIn(Node*);
    void deletepHeadK(int);
    void deleteX(int);
    void deleteAfterq(Node*);
    void deleteRepetitive();
    void InterchangeSort_inc();
    void add_element_listinc(Node*);
    void update_sohoanthien();
};
Dslk::Dslk() : pHead(nullptr), _iSize(0) {}
Dslk::~Dslk(){
    while (pHead != nullptr) {
        Node* temp = pHead;
        pHead = pHead->next;
        delete temp;
    }
}
//a) Nhập danh sách liên kết đơn các số nguyên bằng cách thêm từng phần tử vào cuối danh sách
void Dslk::push(int x){
    Node* node= new Node(x);
    if(pHead == nullptr){
        pHead = node;
    }
    else{
        Node *pTemp = pHead;
        while(pTemp -> next != nullptr){
            pTemp = pTemp -> next;
        }
        pTemp -> next = node;
    }
    _iSize++;
}
//b)Xuất danh sách ra màn hình
void Dslk::print(){
    Node *pTemp = pHead;
    while(pTemp != nullptr){
        pTemp -> display();
        pTemp = pTemp -> next;
    }
}
//c) Liệt kê các số nguyê tố có trong danh sách
void Dslk::print_primes(){
    Node *pTemp = pHead;
    while(pTemp != nullptr){
        bool check = true;
        if(pTemp -> data >= 2){
            for(int i = 2; i <= sqrt(pTemp -> data); i++){
                if(pTemp -> data % i == 0) {
                    check = false;
                    break;
                }
            }
            if(check) pTemp -> display();
        }
        pTemp = pTemp -> next;
    }
}
//d) Tính trung bình cộng của các phần tử trong danh sách
void Dslk::average(){
    Node *pTemp = pHead;
    double sum = 0;
    while(pTemp != nullptr){
        sum += pTemp -> data;
        pTemp = pTemp -> next;
    }
    cout << sum / _iSize << endl;
}
//e)đếm số lần xuất hiện của một số nguyên nhập từ bàn phím có trong danh sách
void Dslk::current(int x){
    Node *pTemp = pHead;
    int cur = 0;
    while(pTemp != nullptr){
        if(pTemp -> data == x) cur++;
        pTemp = pTemp -> next;
    }
    cout << cur << endl;
}
//f) Tìm số chính phương cuối cùng trong danh sách 
void Dslk::lastChinhPhuong(){
    Node *pTemp = pHead;
    int cur = -1;
    while(pTemp != nullptr){
        int tam = sqrt(pTemp -> data);
        if(tam*tam == pTemp -> data) cur = pTemp -> data;
        pTemp = pTemp -> next;
    }
    cout << cur << endl;  
}
//g) Tìm và trả về phần tử thứ k trong danh sách tính từ đầu danh sách
Node* Dslk::findPosK(int k){
    Node *pTemp = pHead;
    int cur = 1;
    while(pTemp != nullptr && cur != k){
        pTemp = pTemp -> next;
        cur++;
    }       
    if(pTemp == nullptr) {
        cout << "Khong co phan tu thu k\n";
        return nullptr;
    }
    else return pTemp; 
}
//h) Tìm phần tửu có giá trị nhỏ nhất trong danh sách
void Dslk::findMin(){
    Node *pTemp = pHead;
    int mi = INT_MAX;
    while(pTemp != nullptr){
        mi = min(mi, pTemp -> data);
        pTemp = pTemp -> next;
    }
    cout << mi << endl;
}
//i) Thêm một phần tử vào sau phần tử q trong danh sách
void Dslk::insertNode(Node* node,int x){
    Node* pAdd = new Node(x);
    if(node != nullptr){
        pAdd -> next = node -> next;
        node -> next = pAdd;
    }
    else push(x);
    _iSize++;

}
//j) Thêm một phần tử vào danh sách sao cho phần tử thêm vào không trùng với các phần tử đã có trong danh sách
void Dslk::addNotIn(Node* node){
    Node *pTemp = pHead;
    while(pTemp != nullptr && pTemp != node){
        pTemp = pTemp -> next;
    }
    if(pTemp != nullptr){
        cout << "Da co trong danh sach\n";
        return;
    }
    pTemp = node;
    _iSize++;
}
//k) Xóa k phần tửu ở đầu danh sách (k nhập từ bàn phím)
void Dslk::deletepHeadK(int k) {
    int cur = 0;
    while (pHead != nullptr && cur < k) {
        Node *temp = pHead;
        pHead = pHead->next;
        delete temp;
        cur++;
        _iSize--;
    }
}
//l) Xóa phần tử có giá trị bằng x có trong danh sách
void Dslk::deleteX(int x) {
    Node *pTemp = pHead;
    Node *pPrev = nullptr;
    while (pTemp != nullptr && pTemp->data != x) {
        pPrev = pTemp;
        pTemp = pTemp->next;
    }
    if (pTemp == nullptr) {
        cout << "Khong co gia tri x trong danh sach\n";
        return;
    }
    if (pPrev == nullptr) {
        pHead = pHead->next;
    } else {
        pPrev->next = pTemp->next;
    }
    delete pTemp;
    _iSize--;
}
//m) Xóa một phần tử sau phần tử q trong danh sách
void Dslk::deleteAfterq(Node* q){
    Node *pTemp = q;
    pTemp = pTemp -> next;
    if(pTemp != nullptr){
        q -> next = pTemp -> next;
        delete pTemp;
        _iSize--;
    }
}

//n) Xóa tất cả các phần tử lặp lại trong danh sách(chỉ giữ lại duy nhất 1 phần tử)
void Dslk::deleteRepetitive(){
    Node* pTemp = pHead;
    Node* pPre = nullptr;
    set<int> d;
    while(pTemp != nullptr) {
        if(d.find(pTemp -> data) == d.end()){
            d.insert(pTemp -> data);
            pPre = pTemp;
        }
        else{
            pPre -> next = pTemp -> next;
            delete pTemp;
            _iSize--;
        }
        pTemp = pPre -> next;
    }
}

//o) Sắp xếp danh sách theo thứ tự tăng dần dùng Interchange Sort
void Dslk::InterchangeSort_inc(){
    Node* p1;
    Node* p2;
    for(p1 = pHead; p1 -> next != nullptr; p1 = p1 -> next ){
        for(p2 = p1 -> next; p2 != nullptr; p2 = p2 -> next ){
            if(p1 -> data > p2 -> data) swap(p1 -> data, p2 -> data);
        }
    }
}
//p) Thêm một phần tử vào danh sách tăng dần ( quá trình thêm không làm mất tính tăng dần của danh sách)
void Dslk::add_element_listinc(Node* node){
    InterchangeSort_inc();
    Node* pTemp = pHead;
    if(node -> data < pTemp -> data){
        node -> next = pTemp ;
        pHead = node;
    } else {
        Node *pTemp2 = pHead;
        while(pTemp ->data < node -> data && pTemp != nullptr){
            pTemp2 = pTemp;
            pTemp = pTemp->next;
        }
        node->next = pTemp2->next;
        pTemp2->next = node;
    }
    _iSize++;
}
//q) Cập nhật các số hoàn thiện trong danh sách thành số 0
void Dslk::update_sohoanthien(){
    Node *pTemp = pHead;
    while(pTemp != nullptr){
        int sum = 1;
        for (int i = 2; i <= sqrt(pTemp->data); i++) {
            if (pTemp->data % i == 0) {
                sum += i;
                if (i != pTemp->data / i) {
                    sum += pTemp->data / i;
                }
            }
        }
        if (sum == pTemp->data && pTemp->data != 1) {
            pTemp->data = 0;
        }
        pTemp = pTemp -> next;
    } 
}

int main(){
    Dslk _dslk;
    return 0;
}