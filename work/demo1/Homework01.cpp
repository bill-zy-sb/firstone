#include<iostream>
using namespace std ;
class Linknode {
private:
    int data;
    Linknode* next;
public:
    // 构造函数
    Linknode(int value = 0) : data(value), next(nullptr) {
        cout << "Linknode constructor called" << endl;//提示
    }

    // 析构函数
    ~Linknode() {
        cout << "Linknode destructor called" << endl;//提示
    }

    int GetData() {
        return data;
    }

    Linknode* GetNext() {
        return next;
    }

    void SetNext(Linknode* ptr) {
        next = ptr;
    }
//打印节点
 void PrintNode() {
        cout << "data是: " << data << endl;
    }
};



int main(){
Linknode node1(10);//构造
//输出 
node1.GetData() 
 


}
