#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// Общие функции и классы
template <typename T>
T SUM(const T& a, const T& b) {
    return a + b;
}

// Класс Aang (базовый для People, Wizard, Monster)
class Aang {
public:
    int health;  // здоровье
    int shield;  // щит
    vector<string> blinding;  // негативные эффекты
    vector<string> gain;  // позитивные эффекты
    int resistance = 0;  // сопротивление

    virtual void inf() = 0;  // функция для вывода информации
};

// Иерархия классов заклинаний
class Spell {
protected:
    string name;  // имя заклинания
public:
    virtual void apply(Aang* aang) = 0;  // применение заклинания
    virtual void inf() const {
        cout << "Заклинание: " << name << "\n";
    }
    virtual ~Spell() = default;
};

class Attack : public Spell {
public:
    Attack() { name = "Атака"; }
    void apply(Aang* aang) {
        if(!aang->resistance)
        {
            aang->blinding.push_back("Ожог");
            aang->health -= 17;
        }
        else{
            aang->resistance--;
        }
    }
};

class Protect : public Spell {
public:
    Protect() { name = "Защита"; }
    void apply(Aang* aang)  {
        aang->gain.push_back("Щит");
    }
};

class Unforgivable : public Spell {
public:
    Unforgivable() { name = "Невыносимое"; }
    void apply(Aang* aang) {
        cout << "Не стоит использовать это заклинание.\n";
    }
};

// Иерархия классов элементов
class Element {
protected:
    string name;  // имя элемента
    int attack = 0;  // урон
    int protection = 0;  // защита
public:
    virtual void effect(Aang* aang) = 0;  // эффект элемента
    friend class NatureSpell;
};

class Fire : public Element {
public:
    Fire() { name = "Огонь"; attack = 11; }
    void effect(Aang* aang) {
        if(!aang->resistance)
        {
            aang->blinding.push_back("Ожог");
        }
        else{
            aang->resistance--;
        }
    }
};

class Water : public Element {
public:
    Water() { name = "Вода"; attack = 7; }
    void effect(Aang* aang)  {
        if(!aang->resistance){
            aang->blinding.push_back("Омочен");
        }
        else{
            aang->resistance--;
        }
    }
};

class Earth : public Element {
public:
    Earth() { name = "Земля"; protection = 3; }
    void effect(Aang* aang)  {
        aang->gain.push_back("Закрыт камнем"); 
    }
};

class Air : public Element {
public:
    Air() { name = "Воздух"; protection = 9; } 
    void effect(Aang* aang)  {
        aang->gain.push_back("Воздушная защита"); 
    }
};

// Класс NatureSpell
class NatureSpell {
private:
    vector<shared_ptr<Element>> elements;  // элементы заклинания
public:
    NatureSpell(const vector<shared_ptr<Element>>& elems) : elements(elems) {}

    void apply(Aang* aang) {
        int total_damage = 0, total_protection = 0;

        for (const auto& elem : elements) {
            elem->effect(aang);
            total_damage = SUM(total_damage, elem->attack);
            total_protection = SUM(total_protection, elem->protection);
        }
        if (aang->health <= 0) {
            throw("Барби");
        }
        if (total_damage > aang->shield) {
            total_damage -= aang->shield;
            aang->shield = 0;
            aang->health -= total_damage;
        } else {
            aang->shield -= total_damage;
        }
        aang->shield += total_protection;
    }

    void inf() {
        cout << "Заклинание природы: ";
        for (const auto& elem : elements) {
            cout << elem->name << " ";
        }
        cout << "\n";
    }
};

// Класс Книга
class Book {
private:
    string name;  // имя книги
    vector<shared_ptr<Spell>> spells;  // заклинания
    vector<shared_ptr<NatureSpell>> natureSpells;  // заклинания природы
public:
    Book(const string& n) : name(n) {}

    void addSpell(const shared_ptr<Spell>& spell) {
        spells.push_back(spell);
    }

    void addNatureSpell(const shared_ptr<NatureSpell>& spell) {
        natureSpells.push_back(spell);
    }

    void inf() const {
        cout << "Книга: " << name << "\n" << "Заклинания:\n";
        for (const auto& spell : spells) {
            spell->inf();
        }
        for (const auto& nSpell : natureSpells) {
            nSpell->inf();
        }
    }

    void use(Aang* a, string type) {
        if(type == "Ns") {
            for(const auto& nassp: natureSpells) {
                nassp->apply(a);
            }
        } else {
            for(const auto& sp: spells) {
                sp->apply(a);
            }
        }
    }
};

// Класс Маг
class Wizard : public Aang {
private:
    string name;  // имя мага
public:
    Wizard* adres = this;
    Wizard(const string& n, int h, int s) : name(n) {
        health = h;
        shield = s;
    }

    void inf() override {
        cout << "Маг: " << name << "\n" << "Здоровье: " << health << "\n" << "Щит: " << shield << "\n";
        cout << "Преимущества: ";
        for (const auto& buff : gain) {
            cout << buff << " ";
        }
        cout << "********: ";
        for (const auto& debuff : blinding) {
            cout << debuff  << " ";
        }
        cout << "\n";
    }

    void use(Aang* a, string i, Book* book) {
        book->use(a, i);
    }
};

// Классы Оружий
class Weapon {
protected:
    string name;  // имя оружия
    int damage;  // урон
    int clip = 0;  // количество патронов
public:
    virtual void use(Aang* people) = 0;   // использование оружия
    virtual void inf() const {
        cout << "Оружие: " << name << " Урон: " << damage << "\n";
    }
    virtual ~Weapon() = default;
};

class Sword : public Weapon {
public:
    Sword() { name = "Меч"; damage = 15; }
    void use(Aang* people) override {
        if(!people->resistance){
            people->gain.push_back("Ранен мечом");
            people->health -= damage;
        }
        else{
            people->resistance--;
        }
    }
};

class Bow : public Weapon {
public:
    Bow() { name = "Лук"; damage = 10; clip = 5; }
    void use(Aang* people) override {
        if(clip > 0){
            if(!people->resistance){
                people->gain.push_back("Ранен стрелой");
                people->health -= damage;
            }
            else{
                people->resistance--;
            }
            clip--;
        }  
    }
};

// Дополнительные классы оружий, например, Пистолет, Автомат и т.д.

// Функция для выбора оружия по имени
Weapon* chooseWeap(const string& weaponName) {
    if (weaponName == "Sword") {
        return new Sword();
    }
    if (weaponName == "Bow") {
        return new Bow();
    }
    // Добавьте больше оружий по необходимости
    return nullptr;  // Если оружие не найдено
}

// Класс Инвентарь
class Inventory {
private:
    vector<shared_ptr<Weapon>> weapons;  // оружие в инвентаре
public:
    Inventory(string one, string two) {
        weapons.push_back(make_shared<Sword>());
        weapons.push_back(std::shared_ptr<Weapon>(chooseWeap(one)));
        weapons.push_back(std::shared_ptr<Weapon>(chooseWeap(two)));
    }

    void useWeapons(Aang* people) {
        int selectedCount = 0;
        people->gain.clear();
        for (const auto& weapon : weapons) {
            if (selectedCount < 3) {
                weapon->use(people);
                selectedCount++;
            }
        }
    }

    void inf() {
        for (const auto& weapon : weapons) {
            weapon->inf();
        }
    }
};

// Класс Люди
class People : public Aang {
    string name;  // имя человека
public: 
    Inventory* inv;
    People* adres = this;
    People(string n, int h, int s, Inventory* i) {
        name = n;
        health = h;
        shield = s;
        inv = i;
    }

    void inf() override {
        cout << name << ": Здоровье = " << health << ", Щит = " << shield << "\n";
        cout << "Инвентарь: \n";
        inv->inf();
    }
};

// Класс Суперспособности
class Superpowers {
protected:
    string name;  // имя способности
    int damage = 0;  // урон
    int restoring_health = 0;  // восстановление здоровья
    int counting_attacks = 3;  // количество атак
public:
    virtual void use(Aang*) = 0;  // использование способности
    virtual void inf() const {
        cout << "Ульта: " << name << " Урон: " << damage << "\n";
    }
};

class Super_strength : public Superpowers {
public:
    Super_strength() {
        name = "Ульта";
        damage = 15;
    }
    void use(Aang* monster) override {
        monster->gain.push_back("Суперудар");
        monster->health -= damage; 
    }
};

// Класс Монстр
class Monster : public Aang {
private: 
    string name;  // имя монстра
public:
    Superpowers* sup;  // суперспособности
    Monster* adres = this;
    Monster(string n, int h, int s, Superpowers* a) {
        health = h;
        name = n;
        shield = s;
        sup = a;
    }

    void inf() override {
        cout << "Монстр: " << name << "\n" << "Здоровье: " << health << "\n" << "Щит: " << shield << "\n";
        sup->inf();
    }

    void use(Aang* other, string type, Book* book) {
        book->use(other, type);
    }
};

// Главная функция для тестирования
int main() {
    shared_ptr<Wizard> wizard = make_shared<Wizard>("Магистр", 100, 50);
    shared_ptr<Monster> monster = make_shared<Monster>("Дракон", 80, 20, new Super_strength());
    shared_ptr<Book> book = make_shared<Book>("Книга Заклинаний");
    shared_ptr<NatureSpell> natureSpell = make_shared<NatureSpell>(vector<shared_ptr<Element>>{make_shared<Fire>(), make_shared<Air>()});
    book->addNatureSpell(natureSpell);
    return 0;
}

