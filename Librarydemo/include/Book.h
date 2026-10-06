#ifndef BOOK_H
#define BOOK_H

#include <string>
class Book {//基类声明
protected:
    std::string isbn;
    std::string title;
    std::string author;
    int total;
    int available;
 public:
    void setIsbn(const std::string& isbn);
    void setTitle(const std::string& title);  
    void setAuthor(const std::string& author); 
    void setTotal(int total);
    void setAvailable(int available);

    std::string getIsbn()const;
    std::string getTitle()const;
    std::string getAuthor()const;
    int getTotal()const;
    int getAvailable()const;
//显示函数,声明类型的虚函数
    virtual void showinfo() const;
    virtual std::string getType() const = 0; //纯虚函数，获取图书类型


//构造,析构函数声明
     Book();
     Book(int total, int available, const std::string& isbn, const std::string& title, const std::string& author);
    virtual ~Book();
};
class Magazine: public Book {
public:
    Magazine(int total, int available, const std::string& isbn, const std::string& title, const std::string& author);
    void showinfo() const override;//虚函数重写
    std::string getType() const override;//获取图书类型
    //析构函数
    ~Magazine();

};
class Novel: public Book {
public:
    Novel(int total, int available, const std::string& isbn, const std::string& title, const std::string& author);
    void showinfo() const override;//虚函数重写
    std::string getType() const override;//获取图书类型
    //析构函数
    ~Novel();
};
class Science: public Book {
public:
    Science(int total, int available, const std::string& isbn, const std::string& title, const std::string& author);
    void showinfo() const override;//虚函数重写
    std::string getType() const override;//获取图书类型
    //析构函数
    ~Science();
};

#endif
