#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

class LibraryManager{
  
  public:
    LibraryManager();
    void ShowMenu(void);
    void AddData(void);
    void ShowBooks(void);
    void AddBook(void);
    void DeleteBook(void);
    void ModifyBook(void);
    void FindBook(void);
    void BorrowBook(void);
    void ReturnBook(void);
};

#endif // LIBRARYMANAGER_H
