#include <iostream>
#include <string>

struct Author {
    std::string firstName;
    std::string lastName;
};

struct Book {
    std::string title;
    Author author;
    int yearOfPublication;
    int numberOfPages;

    Book() : title("Неизвестно"), yearOfPublication(0), numberOfPages(0) {
        author.firstName = "Неизвестно";
        author.lastName = "Неизвестно";
    }

    void displayBook() const {
        std::cout << "Название книги: " << title << std::endl;
        std::cout << "Автор: " << author.firstName << " " << author.lastName << std::endl;
        std::cout << "Год издания: " << yearOfPublication << std::endl;
        std::cout << "Количество страниц: " << numberOfPages << std::endl;
        std::cout << std::endl;
    }
};

Book createBook() {
    Book book;

    std::cout << "Введите название книги: ";
    std::cin.ignore();
    std::getline(std::cin, book.title);

    std::cout << "Введите имя автора: ";
    std::getline(std::cin, book.author.firstName);

    std::cout << "Введите фамилию автора: ";
    std::getline(std::cin, book.author.lastName);

    std::cout << "Введите год издания: ";
    std::cin >> book.yearOfPublication;

    std::cout << "Введите количество страниц: ";
    std::cin >> book.numberOfPages;

    return book;
}

int main() {
    const int numberOfBooks = 3;
    Book books[numberOfBooks];

    for (int i = 0; i < numberOfBooks; ++i) {
        std::cout << "Хотите ввести данные для книги " << i + 1 << "? (y/n): ";
        char answer;
        std::cin >> answer;

        if (answer == 'y' || answer == 'Y') {
            books[i] = createBook();
        } else {

            books[i] = Book();
        }
    }

    for (int i = 0; i < numberOfBooks; ++i) {
        std::cout << "Информация о книге " << i + 1 << ":" << std::endl;
        books[i].displayBook();
    }

    return 0;
}
