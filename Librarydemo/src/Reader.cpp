#include<vector>
#include<string>
using namespace std;
class Reader{
private:    
    string name;//借出人
    int id;//借出学号
    vector<string> borrowedBooks;//借出的书籍列表
public:
//带参构造
  Reader(const string& name, int id)
        : name(name), id(id) {}
//无参构造
Reader():name(""),id(0){}

//成员函数
void setName(const string& n) { name = n; }
void setId(int i) { id = i; }   
string getName() const { return name; }
int getId() const { return id; }






//析构函数
~Reader(){}
}