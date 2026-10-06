#include<iostream>
#include<fstream>//输入输出流
#include<sstream>//字符串流
#include<string>
using namespace std;
#include "LibraryManager.h"
#include "Book.h"
#include "Reader.h"
int main(){
//问候语
cout<<"欢迎使用图书管理系统"<<endl;
//加载图书数据
//从book.txt中读取图书信息
LibraryManager lm;
lm.AddData();
    while(1){
    //显示菜单
    lm.ShowMenu();
int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        //显示图书
        lm.ShowBooks();
        break;
    case 2:
        //添加图书
        lm.AddBook();
        break;
    case 3:
        //删除图书
        lm.DeleteBook();
        break;
    case 4:
        //修改图书信息
        lm.ModifyBook();//不同类之间的函数调用是属于依赖关系
        break;
    case 5:
        //输入编号查找图书
        lm.FindBook();
        break;
    case 6:
        //借书功能
        lm.BorrowBook();
        break;
    case 7:
        //还书功能，对Reader类进行扩展，增加借书和还书功能
        lm.ReturnBook();
        break;
    case 0:
        //退出功能
        cout << "感谢使用图书管理系统！" << endl;
        return 0;
    default:
        cout << "无效选择，请重新输入！" << endl;
        break;
    }

    return 0;
}
