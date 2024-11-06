#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Animal {
protected:
    int age;
    string breed;
    string name;
    int health;

public:
    Animal(int age, const string& breed, const string& name, int health)
        : age(age), breed(breed), name(name), health(health) {}

    virtual ~Animal() {}

    virtual void makeSound() const = 0;

    void displayInfo() const {
        cout << "Имя: " << name << ", Порода: " << breed << ", Возраст: " << age << " лет\n";
    }

    int getHealth() const {
        return health;
    }

    void setHealth(int healthValue) {
        health = healthValue;
    }

    friend class Veterinarian;
};

class Cat : public Animal {
public:
    Cat(int age, const string& breed, const string& name, int health)
        : Animal(age, breed, name, health) {}

    void makeSound() const override {
        cout << name << " говорит: Кит ты маму мав?\n";
    }
};

class Dog : public Animal {
public:
    Dog(int age, const string& breed, const string& name, int health)
        : Animal(age, breed, name, health) {}

    void makeSound() const override {
        cout << name << " говорит: Гааааав\n";
    }
};

class Owner {
public:
    struct FullName {
        string firstName;
        string lastName;
    };

    FullName fullName;
    int age;
    vector<Animal*> pets;

    Owner(const string& firstName, const string& lastName, int age)
        : age(age) {
        fullName.firstName = firstName;
        fullName.lastName = lastName;
    }

    void addPet(Animal* pet) {
        pets.push_back(pet);
    }

    void showPets() const {
        cout << "Питомцы хозяина " << fullName.firstName << " " << fullName.lastName << ":\n";
        for (const auto& pet : pets) {
            pet->displayInfo();
            pet->makeSound();
            cout << "HP питомца: " << pet->getHealth() << "\n";
        }
    }
};

class Veterinarian {
public:
    void medicalCheck(Animal& animal) {
        cout << "Ветеринар чекает здоровье питомца " << animal.name << ".\n";
    }

    void treat(Animal& animal, int treatmentAmount) {
        cout << "Лечение питомца " << animal.name << ". HP увеличено " << treatmentAmount << ".\n";
        animal.setHealth(animal.getHealth() + treatmentAmount);
    }

    void talkToOwner(const Owner& owner) const {
        cout << "Ветеринар болтает с хозяином: " << owner.fullName.firstName << " " << owner.fullName.lastName << "\n";
    }
};

int main() {
    Cat myCat(3, "Сиамская", "Клеопатра", 80);
    Dog myDog(5, "Лабрадор", "Батон", 90);

    Owner owner("Артур", "Ахметьянов", 19);
    owner.addPet(&myCat);
    owner.addPet(&myDog);

    owner.showPets();

    Veterinarian vet;
    vet.talkToOwner(owner);
    vet.medicalCheck(myCat);
    vet.treat(myCat, 10);
    vet.medicalCheck(myDog);
    vet.treat(myDog, 15); 

    owner.showPets();

    return 0;
}
