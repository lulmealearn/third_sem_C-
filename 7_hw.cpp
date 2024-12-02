#include <iostream>
#include <string>

template <typename T>
T SUM(T& a, T& b) {
    return a + b;
}

class Target {
public:
    int health;
    int shield;
    std::string* debuffs {new std::string[20]};
    std::string* buffs {new std::string[20]};
    int FreeDebuff = 0;
    int FreeBuff = 0;

    virtual void inf() = 0;
    virtual ~Target() {
        delete[] debuffs;
        delete[] buffs;
    }
};

class Spell {
protected:
    std::string name;
    int damage;
    int protect;
    int heal;
    int level;

    virtual void ability(Target*) = 0;

public:
    void inf() {
        std::cout << "Spell: " << name << '\n';
    }
    virtual ~Spell() = default;
};


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


class Household : public Spell {
public:
    Household() { name = "Household"; }
    void ability(Target* t) override {
        std::cout << "This is not a combat spell.\n";
    }
};

class Unforgivable : public Spell {
public:
    Unforgivable() { name = "Unforgivable"; }
    void ability(Target* t) override {
        std::cout << "Better not use this spell.\n";
    }
};

class Elements {
protected:
    int atack = 0;
    int protect = 0;
    std::string name;

public:
    virtual void effect(Target*, int) = 0;
    virtual ~Elements() = default;
};

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
        t->debuffs[t->FreeDebuff++] = "washed";
    }
};

class Earth : public Elements {
public:
    Earth() { protect = 8; name = "Earth"; }
    void effect(Target* t, int) override {
        t->buffs[t->FreeBuff++] = "stone shield";
    }
};

class NatureSpell {
private:
    Elements** elem;
    int N;

public:
    int level;
    NatureSpell(Elements** el, int n) : elem(el), N(n), level((n / 3) + 1) {}
    ~NatureSpell() {
        for (int i = 0; i < N; ++i) {
            delete elem[i];
        }
        delete[] elem;
    }

    void effect(Target* t) {
        int total_damage = 0;
        int total_shield = 0;

        for (int i = 0; i < N; ++i) {
            elem[i]->effect(t, i);
            total_damage = SUM(total_damage, elem[i]->atack);
            total_shield = SUM(total_shield, elem[i]->protect);
        }

        if (total_damage > t->shield) {
            total_damage -= t->shield;
            t->shield = 0;
            t->health -= total_damage;
        } else {
            t->shield -= total_damage;
        }

        t->shield += total_shield;
    }

    void inf() {
        std::cout << "Nature spell (level " << level << "): ";
        for (int i = 0; i < N; ++i) {
            std::cout << elem[i]->name << " ";
        }
        std::cout << '\n';
    }
};

class Book {
public:
    std::string name;
    int pages;
    Spell** Harry_spells;
    NatureSpell** Nature_spells;
    int Nat_Sp;
    int Har_Sp;

    Book(std::string n, int p, NatureSpell** ns, int n_ns, Spell** sp, int s)
        : name(n), pages(p), Nature_spells(ns), Nat_Sp(n_ns), Harry_spells(sp), Har_Sp(s) {}

    void inf() {
        std::cout << "Book: " << name << "\nNature spells:\n";
        for (int i = 0; i < Nat_Sp; ++i) {
            Nature_spells[i]->inf();
        }
        std::cout << "Harry Potter spells:\n";
        for (int i = 0; i < Har_Sp; ++i) {
            Harry_spells[i]->inf();
        }
    }
};

class Wizard : public Target {
public:
    std::string name;
    int level;

    Wizard(std::string n, int l, int h, int s) : name(n), level(l), health(h), shield(s) {}

    void inf() override {
        std::cout << "Wizard: " << name << "\nHealth: " << health << ", Shield: " << shield << "\n";
    }

    void use(Book* book, int spell_index, Target* t) {
        if (book->Nature_spells[spell_index]->level <= level) {
            book->Nature_spells[spell_index]->effect(t);
        } else {
            throw std::runtime_error("Level too low to use this spell!");
        }
    }
};

int main() {
    try {
        std::cout << "Enter number of Nature spells: ";
        int N_NS;
        std::cin >> N_NS;

        NatureSpell* nature_spells[N_NS];
        for (int i = 0; i < N_NS; ++i) {
            std::cout << "Enter number of elements for spell " << (i + 1) << ": ";
            int N;
            std::cin >> N;

            Elements** elements = new Elements*[N];
            for (int j = 0; j < N; ++j) {
                std::cout << "Enter element type (f=fire, w=water, e=earth): ";
                char type;
                std::cin >> type;

                if (type == 'f') {
                    elements[j] = new Fire();
                } else if (type == 'w') {
                    elements[j] = new Water();
                } else if (type == 'e') {
                    elements[j] = new Earth();
                } else {
                    std::cout << "Invalid input. Try again.\n";
                    --j;
                }
            }

            nature_spells[i] = new NatureSpell(elements, N);
        }

        Spell* harry_spells[3] = {new Attack(), new Protect(), new Unforgivable()};

        Book spell_book("Grimoire", 100, nature_spells, N_NS, harry_spells, 3);
        spell_book.inf();

        Wizard harry("Harry", 3, 100, 50);
        Wizard enemy("Enemy", 1, 80, 20);

        std::cout << "Choose a Nature spell (1-" << N_NS << "): ";
        int spell_choice;
        std::cin >> spell_choice;

        harry.use(&spell_book, spell_choice - 1, &enemy);

        enemy.inf();

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}
