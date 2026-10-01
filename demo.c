#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Animal {
protected:
    string 
public:
    Animal(string n) : name(n) {}

    virtual void speak() const = 0;

    virtual ~Animal() = default;
};
class Dog : public Animal {
public:
    Dog(string n) : Animal(n) {}
    void speak() const override {         
        cout << name << ": ÍôÍôÍô£¡\n";
    }
};
class Cat : public Animal {
public:
    Cat(string n) : Animal(n) {}
    void speak() const override {
        cout << name << ": ß÷ß÷ß÷~\n";
    }
};
class Sheep : public Animal {
public:
    Sheep(string n) : Animal(n) {}
    void speak() const override {
        cout << name << ": ßã¡ª¡ª\n";
    }
};

int main() {
    vector<Animal*> zoo;
    zoo.push_back(new Dog("Íú²Æ"));
    zoo.push_back(new Cat("ßäßä"));
    zoo.push_back(new Sheep("¶ä¶ä"));
    zoo.push_back(new Dog("À´¸£"));
   
    for (Animal* a : zoo) {
        a->speak();                       
    }
//×îºóÇåÀí¿Õ¼ä 
    for (Animal* a : zoo) delete a;
    return 0;
}

