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
   istringstream iss;//这字符串流是为了方便分出一整段的字符
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
  while(type!="Magazine"&&type!="Novel"&&type!="Science"){
    cout<<"图书类型输入错误，请重新输入(Magazine/Novel/Science):";
    cin>>type;
  }
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
  }else{}
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
    //更新文件，全部删除后重新写入
    ofstream file("book.txt");//文件输入流，覆盖写入
    for(const auto& book:Books){
      //typeid查真实类型，name()返回类型名，注意这里是指针所以要用*book
      file<<book->getType()<<" "<<book->getIsbn()<<" "<<book->getTitle()<<" "<<book->getAuthor()<<" "<<book->getTotal()<<" "<<book->getAvailable()<<"|"<<endl;
    }
    file.close();
  }else{
    cout<<"未找到该图书！"<<endl;
  }
}
void LibraryManager::ModifyBook(void){//查找到了之后就跟删除一样的
  string isbn;
  cout<<"请输入要修改的图书ISBN:";
  cin>>isbn;
  //程序内存部分先把他删掉，再写入 
  for(auto it=Books.begin();it!=Books.end();++it){
    if((*it)->getIsbn()==isbn){//找到了就删除
      delete *it;//释放内存
      Books.erase(it);//从vector中删除
      break;
    }//如果没跳出来就是没有
    cout<<"未找到该图书！"<<endl;
    return;
  }
     cout<<"请输入图书类型(Magazine/Novel/Science):";
     string type;
     cin>>type;
     while(type!="Magazine"&&type!="Novel"&&type!="Science"){
       cout<<"图书类型输入错误，请重新输入(Magazine/Novel/Science):";
       cin>>type;
     }
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
     if(type=="Magazine"){
     Magazine *mag=new Magazine(total,total,isbn,title,author);
     Books.push_back(mag);
     }else if(type=="Novel"){
       Novel *nov=new Novel(total,total,isbn,title,author);
     Books.push_back(nov);
     }else if(type=="Science"){
       Science *sci=new Science(total,total,isbn,title,author);
     Books.push_back(sci);
     }
     //更新文件，全部删除后重新写入(文本文件写入流)
       ofstream file("book.txt");//文件输入流，覆盖写入
       for(const auto& book:Books){
         file<<book->getType()<<" "<<book->getIsbn()<<" "<<book->getTitle()<<" "<<book->getAuthor()<<" "<<book->getTotal()<<" "<<book->getAvailable()<<"|"<<endl;
       }
       file.close();
}
void LibraryManager::FindBook(void){
  string isbn;
  cout<<"请输入要查找的图书ISBN:";
  cin>>isbn;
  bool found=false;//标志位
  for(const auto& book:Books){//增强for循环遍历图书列表
    if(book->getIsbn()==isbn){
      book->showinfo();//找到就显示
      found=true;
      break;
    }
  }
  if(!found){
    cout<<"未找到该图书！"<<endl;
  }
}
void LibraryManager::BorrowBook(void){
  string name, identity;
  int id;
  cout<<"请输入借书人姓名:";
  cin>>name;
  cout<<"请输入借书人身份:";
  cin>>identity;
  while(identity!="学生"&&identity!="教师"){
    cout<<"借书人身份输入错误，请重新输入(学生/教师):";
    cin>>identity;
  }
  cout<<"请输入借书人学号:";
  cin>>id;
  cout<<"请输入要借的图书ISBN:";
  string isbn;
  cin>>isbn;
  bool found=false;
  //查找图书
  for(auto& book:Books){
    if(book->getIsbn()==isbn){
      //找到图书，检查可借数量
      if(book->getAvailable()>0){
        book->setAvailable(book->getAvailable()-1);//可借数减1
        //查找读者是否已经存在
        bool readerFound=false;
        for(auto& reader:readerhead){
          if(reader.getId()==id){
            readerFound=true;
            //添加借出的图书到读者的借书列表            
            reader.borrowedBooks.push_back(book);
            cout<<"借书成功！"<<endl;
            break;
          }
        }
        if(!readerFound){
          //如果读者不存在，创建新的读者并添加到列表
          Reader newReader(name, identity, id);
          newReader.borrowedBooks.push_back(book);
          readerhead.push_back(newReader);
          cout<<"借书成功！新读者已添加。"<<endl;
        }
      }
      found=true;
      break;
    }
  }
  if(!found){
    cout<<"未找到该图书！"<<endl;
    return;
  }

}
void LibraryManager::ReturnBook(void){
  string name;
  cout<<"请输入还书人姓名:";
  cin>>name;
  //查找读者
  bool readerFound=false;
  for(auto& reader:readerhead){
    if(reader.getName()==name){
      readerFound=true;
      cout<<"借出的图书列表："<<endl;
      reader.showBorrowedBooks();
      cout<<"请输入要归还的图书ISBN:";
      string isbn;
      cin>>isbn;
      bool bookFound=false;
      //循环找到借出的图书列表中是否有该图书
      for(auto it=reader.borrowedBooks.begin();it!=reader.borrowedBooks.end();++it){
        if((*it)->getIsbn()==isbn){
          //找到图书，增加可借数量，Books中对应的图书可借数量也要增加
          (*it)->setAvailable((*it)->getAvailable()+1);
          //从读者的借书列表中移除该图书
          reader.borrowedBooks.erase(it);//vector的erase方法会自动调整大小
          //在文件里面重新写入
       ofstream file("book.txt");//文件输入流，覆盖写入
       for(const auto& book:Books){
         file<<book->getType()<<" "<<book->getIsbn()<<" "<<book->getTitle()<<" "<<book->getAuthor()<<" "<<book->getTotal()<<" "<<book->getAvailable()<<"|"<<endl;
       }
       file.close();


          cout<<"还书成功！"<<endl;
          bookFound=true;
          break;
        }
      }
      
      if(!bookFound){
        cout<<"未找到该图书在借出列表中！请重新选择"<<endl;
      }
      break;
    }
  }
  if(!readerFound){
    cout<<"未找到该读者！"<<endl;
  }
}
