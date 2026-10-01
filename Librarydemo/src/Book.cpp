#include<string>
#include<iostream>
#include "Book.h"

//Book
    
    void Book:: setIsbn(const std::string& isbn) { this->isbn = isbn; }
    void Book:: setTitle(const std::string& title) { this->title = title; }   
    void Book:: setAuthor(const std::string& author) { this->author = author; }
    void Book:: setTotal(int total) { this->total = total; }
    void Book:: setAvailable(int available) { this->available = available; }

    std::string Book::getIsbn() const { return isbn; }
    std::string Book::getTitle() const { return title; }
    std::string Book::getAuthor() const { return author; }
    int Book::getTotal() const { return total; }
    int Book::getAvailable() const { return available; }
    //构造，析构函数
   Book:: Book() : total(0), available(0),isbn(""), title(""), author(""){}
   Book:: Book(int total, int available, const std::string& isbn, const std::string& title, const std::string& author)
    : total(total), available(available), isbn(isbn), title(title), author(author) {} 
   Book::~Book() = default;
    //显示函数
    void Book::showinfo()const{ }

//Magazine,Novel,Science
    Magazine::Magazine(int total, int available, const std::string& isbn, const std::string& title, const std::string& author)
    :Book(total, available, isbn, title, author) {}
    void Magazine::showinfo() const {//每本书的总数和图书的总数要注意区分
        std::cout << "杂志信息：" << std::endl;
        std::cout << "ISBN: " << getIsbn() << std::endl;
        std::cout << "标题: " << getTitle() << std::endl;
        std::cout << "作者: " << getAuthor() << std::endl;
        std::cout << "总数: " << getTotal() << std::endl;
        std::cout << "可借数: " << getAvailable() << std::endl;
    }
    Magazine::~Magazine() {}

    Novel::Novel(int total, int available, const std::string& isbn, const std::string& title, const std::string& author)
    :Book(total, available, isbn, title, author) {}
    void Novel::showinfo() const {
        std::cout << "小说信息：" << std::endl;
        std::cout << "ISBN: " << getIsbn() << std::endl;
        std::cout << "标题: " << getTitle() << std::endl;
        std::cout << "作者: " << getAuthor() << std::endl;
        std::cout << "总数: " << getTotal() << std::endl;
        std::cout << "可借数: " << getAvailable() << std::endl;

    }
   Novel::~Novel() {}

    Science::Science(int total, int available, const std::string& isbn, const std::string& title, const std::string& author)
    :Book(total, available, isbn, title, author) {}
    void Science::showinfo() const {
        std::cout << "科技书信息：" << std::endl;
        std::cout << "ISBN: " << getIsbn() << std::endl;
        std::cout << "标题: " << getTitle() << std::endl;
        std::cout << "作者: " << getAuthor() << std::endl;
        std::cout << "总数: " << getTotal() << std::endl;
        std::cout << "可借数: " << getAvailable() << std::endl;
     }
     Science::~Science() {}
