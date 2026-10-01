#include<iostream>
#include<string>
#include<vector>
#include<fstream>//输入输出流
#include<sstream>//字符串流
using namespace std;
#include "Book.h"
#include "Reader.h"
#include "LibraryManager.h"
//数据
  vector<Book*>Books;//图书数据,用子类指针放在一起,因为放到实际上都是地址所以可以放在一起,这里不同类的图书对象是混在一起的
  vector<Reader> readerhead;//读者数据，这个字节放在一起就行，因为没有子类

 
 LibraryManager::LibraryManager(){
 }
 void LibraryManager::ShowMenu(void){
  cout<<"请选择功能："<<endl;
  cout<<"1. 显示图书"<<endl;
  cout<<"2. 添加图书"<<endl;
  cout<<"3. 删除图书"<<endl;
  cout<<"4. 修改图书信息"<<endl;
  cout<<"5. 查找图书"<<endl;
  cout<<"6. 借书"<<endl;
  cout<<"7. 还书"<<endl;
  cout<<"0. 退出"<<endl;
  }
  void LibraryManager::AddData(void){//加载图书数据,和读者数据
  ifstream file("book.txt");
  string line;
   while(getline(file,line, '|')){//按|分割读取图书数据
   istringstream iss;//每次新建流，每次读取的流的结束位不相互影响
    iss.str(line);
    string type;//图书类型
    iss>>type;//读取图书类型
    string isbn, title, author;
      int total, available;
      if(type=="Magazine"){//如果是杂志       
      iss >> isbn >> title >> author >> total >> available;
       Magazine *mag=new Magazine(total,available,isbn,title,author);
      Books.push_back(mag);
      }else if(type=="Novel"){//如果是小说
       
      iss >> isbn >> title >> author >> total >> available;
       Novel  *Nov=new Novel (total,available,isbn,title,author);//total和available这个代表这本书的总数和可借数
      Books.push_back(Nov);
      }else if(type=="Science"){//如果是科技书
      iss >> isbn >> title >> author >> total >> available;
       Science *sci=new Science(total,available,isbn,title,author);
      Books.push_back(sci);
      }
    }file.close();//关闭文件
   
    ifstream file2("reader.txt");
   while(getline(file2,line, '|')){//按|分割读取作者数据
    istringstream iss;//每次新建流，每次读取的流的结束位不相互影响
    iss.str(line);
    string name, identity;
      int id;
      iss >> name >> identity >> id;
      Reader reader(name,identity,id);
      readerhead.push_back(reader);
    }
    file2.close();//关闭文件
  }
  void LibraryManager::ShowBooks(void){
  cout<<"图书列表："<<endl;
  for (const auto& book : Books) {
        book->showinfo();//调用每个对象重构的虚函数显示图书信息
        cout << "------------------------" << endl;
    }
  
  }
void  LibraryManager::AddBook(void){
  string type;
  cout<<"请输入图书类型(Magazine/Novel/Science):";
  cin>>type;
  string isbn, title, author;
  int total;
  cout<<"请输入ISBN:";
  cin>>isbn;
  cout<<"请输入标题：";
  cin>>title;
  cout<<"请输入作者：";
  cin>>author;
  cout<<"请输入添加总数：";
  cin>>total;
  int a=0;
  if(type=="Magazine"){
Magazine *mag=new Magazine(total,total,isbn,title,author);
  Books.push_back(mag);
  a=1;
  }else if(type=="Novel"){
    Novel *nov=new Novel(total,total,isbn,title,author);
  Books.push_back(nov);
  a=1;
  }else if(type=="Science"){
    Science *sci=new Science(total,total,isbn,title,author);
  Books.push_back(sci);
  a=1;
  }else{
    cout<<"图书类型输入错误！"<<endl;
  }
  if(a==1){
  ofstream file("book.txt", ios::app);//用程序向文件写入的方式（写入流）写入
  //图书类型|图书编号|图书名字|图书作者|图书总数量|图书可借
  file << type <<"|" << isbn << "|" << title << "|" << author << "|" << total << "|" << total<<endl;//写入文件
  file.close();
  cout<<"图书添加成功！"<<endl;
  }

}
void LibraryManager::DeleteBook(void){
  string isbn;
  cout<<"请输入要删除的图书ISBN:";
  cin>>isbn;
  bool found=false;//默认没找到
  for(auto it=Books.begin();it!=Books.end();++it){
    if((*it)->getIsbn()==isbn){//找到了就删除
      delete *it;//释放内存
      Books.erase(it);//从vector中删除
      found=true;
      break;
    }
  }
  if(found){//文件同步程序
    cout<<"图书删除成功！"<<endl;
    //更新文件
    ofstream file("book.txt");
    for(const auto& book:Books){
      //写入文件？？？？？？
      file<<typeid(*book).name()<<"|"<<book->getIsbn()<<"|"<<book->getTitle()<<"|"<<book->getAuthor()<<"|"<<book->getTotal()<<"|"<<book->getAvailable()<<endl;
    }
    file.close();
  }else{
    cout<<"未找到该图书！"<<endl;
  }
}