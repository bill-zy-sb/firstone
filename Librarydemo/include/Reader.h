#ifndef READER_H
#define READER_H    
#include <iostream>
#include <string>
#include <vector>
#include "Book.h"
class Reader{
private:    
    std::string name;//借出人
    std::string identity;//借出人身份
    int id;//借出学号
    

public:
    std::vector< Book*> borrowedBooks;//借出的书籍列表,这里包含另一个类是组合关系，这里别的类要去改变他   
//带参构造
    Reader(const std::string& name, const std::string& identity, int id);
    //无参构造
    Reader();
    //析构函数
    ~Reader();

    // Getter and setter methods
    std::string getName() const;
    std::string getIdentity() const;
    int getId() const;
    void setName(const std::string& n);
    void setIdentity(const std::string& iden);
    void setId(int i);

    // Other methods
    void showBorrowedBooks() const;
};
#endif
