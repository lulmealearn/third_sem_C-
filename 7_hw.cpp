#include <iostream>
#include <string>

// Шаблонные функции
template <typename T>
T SUM(const T& a, const T& b) {
    return a + b;
}


template <typename T>
int SIZE(T& a) {
    return sizeof(a) / sizeof(*a);
}

// Базовый класс целей
class Target {
public:
    int health;
    int shield;
    std::string* debuffs {new std::string[20]};
    std::string* buffs {new std::string[20]};
    int FreeDebuff = 0;
    int FreeBuff = 0;

    virtual void inf() = 0;
};

// Базовый класс заклинаний
class Spell {
protected:
    std::string name;

public:
    virtual void ability(Target*) = 0;

    virtual void inf() {
        std::cout << "Spell: " << name << '\n';
    }
};

// Наследники заклинаний
class Attack : public Spell {
public:
    Attack() { name = "Attack"; }

    void ability(Target* t) override {
        t->debuffs[t->FreeDebuff++] = "burning";
        t->health -= 18;
    }
};

class Protect : public Spell {
public:
    Protect() { name = "Protect"; }

    void ability(Target* t) override {
        t->buffs[t->FreeBuff++] = "protected";
    }
};

class Unforgivable : public Spell {
public:
    Unforgivable() { name = "Unforgivable"; }

    void ability(Target* t) override {
        std::cout << "Better not use it.\n";
    }
};

// Элементы стихий
class Elements {
protected:
    int atack = 0;
    int protect = 0;
    std::string name;

public:
    virtual void effect(Target*, int) = 0;

    int getAttack() const { return atack; }
    int getProtect() const { return protect; }
    std::string getName() const { return name; }
};

// Элементы: Огонь, Вода, Земля
class Fire : public Elements {
public:
    Fire() { atack = 10; name = "Fire"; }

    void effect(Target* t, int) override {
        t->debuffs[t->FreeDebuff++] = "burning";
    }
};

class Water : public Elements {
public:
    Water() { atack = 5; name = "Water"; }

    void effect(Target* t, int) override {
        t->debuffs[t->FreeDebuff++] = "wash";
    }
};

class Earth : public Elements {
public:
    Earth() { protect = 8; name = "Earth"; }

    void effect(Target* t, int) override {
        t->buffs[t->FreeBuff++] = "stone";
    }
};

// Природные заклинания
class NatureSpell {
private:
    Elements** elem;
    int N;
    int level;

public:
    NatureSpell(Elements** el, int n) : elem(el), N(n), level(n / 3 + 1) {}

    void effect(Target* t) {
        int total_damage = 0;
        int total_shield = 0;

        for (int i = 0; i < N; ++i) {
            elem[i]->effect(t, i);
            total_damage = SUM(total_damage, elem[i]->getAttack());
            total_shield = SUM(total_shield, elem[i]->getProtect());
        }

        if (total_damage > t->shield) {
            t->health -= (total_damage - t->shield);
            t->shield = 0;
        } else {
            t->shield -= total_damage;
        }
        t->shield += total_shield;
    }

    void inf() const {
        std::cout << "Nature Spell: ";
        for (int i = 0; i < N; ++i) {
            std::cout << elem[i]->getName() << " ";
        }
        std::cout << "(Level " << level << ")\n";
    }

    int getLevel() const {
        return level;
    }
};


// Волшебник
class Wizard : public Target {
public:
    std::string name;
    int level;

    Wizard(std::string n, int l, int h, int s) : name(n), level(l) {
        health = h;
        shield = s;
    }

    void inf() override {
        std::cout << "Wizard: " << name << '\n';
        std::cout << "Health: " << health << ", Shield: " << shield << '\n';
    }

    void use(NatureSpell* spell, Target* target) {
        if (spell->getLevel() <= level) {
            spell->effect(target);
        } else {
            throw std::runtime_error("Level too low!");
        }
    }
};

// Главная функция
int main() {
    std::cout << "How many Nature spells do you know?\n";
    int N_NS;
    std::cin >> N_NS;

    NatureSpell* spells[N_NS];
    for (int i = 0; i < N_NS; ++i) {
        std::cout << "How many elements in spell?\n";
        int N;
        std::cin >> N;

        Elements** elements = new Elements*[N];
        for (int j = 0; j < N; ++j) {
            std::cout << "Enter element (fire, water, earth): ";
            std::string elem;
            std::cin >> elem;

            if (elem == "fire") {
                elements[j] = new Fire();
            } else if (elem == "water") {
                elements[j] = new Water();
            } else if (elem == "earth") {
                elements[j] = new Earth();
            } else {
                std::cerr << "Invalid element. Try again.\n";
                --j;
            }
        }
        spells[i] = new NatureSpell(elements, N);
    }

    Wizard harry("Harry", 3, 100, 50);
    Wizard enemy("Enemy", 2, 80, 30);

    try {
        spells[0]->inf();
        harry.use(spells[0], &enemy);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    harry.inf();
    enemy.inf();

    return 0;
}
