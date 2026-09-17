// ============================================================
// 终端版图书管理系统（C++ 单文件版）
// 对标 Java 结构：Book=实体类  Library=Service层  main=Controller
// 编译：g++ -std=c++17 library.cpp -o library.exe
// ============================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>

// ================== 实体类：Book（相当于 Java Bean） ==================
class Book {
public:
    std::string isbn;
    std::string title;
    std::string author;
    int total = 0;      // 馆藏总数
    int available = 0;  // 当前可借数量
};

// ================== 管理类：Library（相当于 Java 的 Service 层） ==================
class Library {
public:
    // ---------- 增 ----------
    bool addBook(const Book& b) {
        if (findByIsbn(b.isbn)) return false;   // ISBN 已存在，拒绝重复添加
        books_.push_back(b);
        return true;
    }

    // ---------- 删 ----------
    bool removeBook(const std::string& isbn) {
        for (auto it = books_.begin(); it != books_.end(); ++it) {
            if (it->isbn == isbn) {
                books_.erase(it);               // vector 按迭代器删除
                return true;
            }
        }
        return false;
    }

    // ---------- 查（按 ISBN 精确查找，返回指针方便修改，找不到返回 nullptr） ----------
    Book* findByIsbn(const std::string& isbn) {
        for (auto& b : books_)
            if (b.isbn == isbn) return &b;
        return nullptr;
    }

    // ---------- 查（按书名模糊查找） ----------
    std::vector<Book*> findByTitle(const std::string& keyword) {
        std::vector<Book*> result;
        for (auto& b : books_)
            if (b.title.find(keyword) != std::string::npos)
                result.push_back(&b);
        return result;
    }

    // ---------- 借书 ----------
    bool borrowBook(const std::string& isbn) {
        Book* b = findByIsbn(isbn);
        if (!b || b->available <= 0) return false;
        --b->available;
        return true;
    }

    // ---------- 还书 ----------
    bool giveBackBook(const std::string& isbn) {
        Book* b = findByIsbn(isbn);
        if (!b || b->available >= b->total) return false;  // 防止重复归还
        ++b->available;
        return true;
    }

    // ---------- 显示全部 ----------
    void listAll() const {
        if (books_.empty()) {
            std::cout << "书库为空\n";
            return;
        }
        printHeader();
        for (const auto& b : books_) printRow(b);
    }

    // ---------- 持久化：保存（相当于 Java 的 DAO 层） ----------
    void saveToFile(const std::string& path) const {
        std::ofstream out(path);
        for (const auto& b : books_)
            out << b.isbn << '|' << b.title << '|' << b.author
                << '|' << b.total << '|' << b.available << '\n';
    }

    // ---------- 持久化：加载 ----------
    void loadFromFile(const std::string& path) {
        books_.clear();
        std::ifstream in(path);
        if (!in) return;                        // 文件不存在 = 第一次运行，空库
        std::string line;
        while (std::getline(in, line)) {
            if (line.empty()) continue;
            std::istringstream ss(line);        // 按 | 拆分字段
            Book b;
            std::string total, available;
            std::getline(ss, b.isbn, '|');
            std::getline(ss, b.title, '|');
            std::getline(ss, b.author, '|');
            std::getline(ss, total, '|');
            std::getline(ss, available, '|');
            b.total = std::stoi(total);
            b.available = std::stoi(available);
            books_.push_back(b);
        }
    }

private:
    std::vector<Book> books_;                   // 数据就存这里

    static void printHeader() {
        std::cout << std::left
                  << std::setw(15) << "ISBN"
                  << std::setw(20) << "书名"
                  << std::setw(12) << "作者"
                  << std::setw(6)  << "总量"
                  << std::setw(6)  << "可借" << '\n';
    }
    static void printRow(const Book& b) {
        std::cout << std::left
                  << std::setw(15) << b.isbn
                  << std::setw(20) << b.title
                  << std::setw(12) << b.author
                  << std::setw(6)  << b.total
                  << std::setw(6)  << b.available << '\n';
    }
};

// ================== 工具函数：安全的整数输入 ==================
// cin >> 之后残留换行符会污染后面的 getline，这是 C++ 输入的经典坑
int readInt(const std::string& hint) {
    int value;
    while (true) {
        std::cout << hint;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();                       // 清除错误状态
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "输入无效，请输入数字！\n";
    }
}

std::string readLine(const std::string& hint) {
    std::cout << hint;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

// ================== 菜单与主循环（相当于 Java 的 Controller） ==================
void showMenu() {
    std::cout << "\n===== 图书管理系统 =====\n"
              << "1. 添加图书\n"
              << "2. 显示全部\n"
              << "3. 按 ISBN 查找\n"
              << "4. 按书名模糊查找\n"
              << "5. 借书\n"
              << "6. 还书\n"
              << "7. 删除图书\n"
              << "0. 保存并退出\n";
}

void handleAdd(Library& lib) {
    Book b;
    b.isbn    = readLine("ISBN: ");
    b.title   = readLine("书名: ");
    b.author  = readLine("作者: ");
    b.total   = readInt("馆藏数量: ");
    b.available = b.total;
    if (lib.addBook(b)) std::cout << "添加成功！\n";
    else                std::cout << "添加失败：该 ISBN 已存在\n";
}

int main() {
    system("chcp 65001");                       // Windows 终端切到 UTF-8，防止中文乱码

    Library lib;
    lib.loadFromFile("books.txt");              // 启动时读取数据

    while (true) {
        showMenu();
        int choice = readInt("请选择: ");
        switch (choice) {
            case 1: handleAdd(lib); break;
            case 2: lib.listAll(); break;
            case 3: {
                Book* b = lib.findByIsbn(readLine("ISBN: "));
                if (b) { std::cout << "找到："; lib.listAll(); }
                else     std::cout << "未找到该图书\n";
                break;
            }
            case 4: {
                auto found = lib.findByTitle(readLine("书名关键字: "));
                if (found.empty()) { std::cout << "未找到相关图书\n"; break; }
                std::cout << "共找到 " << found.size() << " 本：\n";
                for (const auto* b : found) std::cout << "  " << b->isbn << " 《" << b->title << "》 可借 " << b->available << '\n';
                break;
            }
            case 5:
                std::cout << (lib.borrowBook(readLine("ISBN: ")) ? "借书成功\n" : "借书失败（不存在或已借完）\n");
                break;
            case 6:
                std::cout << (lib.giveBackBook(readLine("ISBN: ")) ? "还书成功\n" : "还书失败（不存在或超出总量）\n");
                break;
            case 7:
                std::cout << (lib.removeBook(readLine("ISBN: ")) ? "删除成功\n" : "未找到该图书\n");
                break;
            case 0:
                lib.saveToFile("books.txt");    // 退出前持久化
                std::cout << "数据已保存，再见！\n";
                return 0;
            default:
                std::cout << "无此选项\n";
        }
    }
}
