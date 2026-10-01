#include<iostream>
#include<string>
#include<vector>
#include<fstream>//输入输出流
#include<sstream>//字符串流
using namespace std;
#include "Book.h"
#include "Reader.h"



 
  void showmenu(void){
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
  void AddData(void){//加载图书数据,和读者数据
    vector<Magazine> Maghead;//
  vector<Science> Scihead;
  vector<Novel> Novhead;
  vector<Reader> readerhead;
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
       Magazine mag(total,available,isbn,title,author);
      Maghead.push_back(mag);
      }else if(type=="Novel"){//如果是小说
       
      iss >> isbn >> title >> author >> total >> available;
       Novel  Nov(total,available,isbn,title,author);//total和available这个代表这本书的总数和可借数
      Novhead.push_back(Nov);
      }else if(type=="Science"){//如果是科技书
      iss >> isbn >> title >> author >> total >> available;
       Science sci(total,available,isbn,title,author);
      Scihead.push_back(sci);
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

