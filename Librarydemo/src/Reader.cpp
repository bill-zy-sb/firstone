#include<vector>
#include<string>
#include<iostream>
using namespace std;
#include "Reader.h"

//带参构造
 Reader::Reader(const string& name, const string& identity, int id)
        : name(name), identity(identity), id(id) {}
//无参构造
   Reader::Reader():name(""),identity("") ,id(0){}

//成员函数
void Reader::setName(const string& n) { name = n; }
void Reader::setId(int i) { id = i; }   
void Reader::setIdentity(const string& iden) { identity = iden; }
string Reader::getName() const { return name; }
int Reader::getId() const { return id; }
string Reader::getIdentity() const { return identity; }
//展示借出人借出图书
void Reader::showBorrowedBooks() const {
    if (borrowedBooks.empty()) {
        cout << name << "（学号：" << id << "）没有借出任何图书。\n";
    } else {
        cout << name << "（学号：" << id << "）借出的图书列表：\n";
        for (const auto& book : borrowedBooks) {
            cout << "- " << book << '\n';
        }
    }
}


//析构函数
Reader:: ~Reader(){}
