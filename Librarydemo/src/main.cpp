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
    lm.showmenu();



int choice;
    cin >> choice;
    switch (choice)
    {
    

        
//添加图书，把图书数据保存在book.txt中
//删除图书
//修改图书信息
//输入编号查找图书
//借书功能
//还书功能，对Reader类进行扩展，增加借书和还书功能
//打印
//退出功能

    case constant expression:
        /* code */
        break;
    
    default:
        break;
    }

    return 0;
}
