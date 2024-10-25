// Включаем стандартный заголовочный файл для ввода/вывода
#include <iostream>

// Определение структуры Author для хранения имени и фамилии автора
struct Author {
    std::string firstName;
    std::string lastName;
};

// Определение структуры Book для хранения информации о книге
struct Book {
    std::string title;               // Название книги
    Author author;                    // Автор книги
    int yearOfPublication;           // Год издания
    int numberOfPages;                // Количество страниц

    // Конструктор по умолчанию для инициализации полей структуры Book
    Book() : title("Неизвестно"), yearOfPublication(0), numberOfPages(0) {
        author.firstName = "Неизвестно";
        author.lastName = "Неизвестно";
    }

    // Метод для вывода информации о книге на экран
    void displayBook() const {
        std::cout << "Название книги: " << title << std::endl;
        std::cout << "Автор: " << author.firstName << " " << author.lastName << std::endl;
        std::cout << "Год издания: " << yearOfPublication << std::endl;
        std::cout << "Количество страниц: " << numberOfPages << std::endl;
        std::cout << std::endl;
    }
};

// Функция для создания и заполнения структуры Book
Book createBook() {
    Book book;

    // Ввод названия книги
    std::cout << "Введите название книги: ";
    std::cin.ignore();                // Игнорируем символ перевода строки в потоке ввода
    std::getline(std::cin, book.title);

    // Ввод имени автора
    std::cout << "Введите имя автора: ";
    std::getline(std::cin, book.author.firstName);

    // Ввод фамилии автора
    std::cout << "Введите фамилию автора: ";
    std::getline(std::cin, book.author.lastName);

    // Ввод года издания
    std::cout << "Введите год издания: ";
    std::cin >> book.yearOfPublication;

    // Ввод количества страниц
    std::cout << "Введите количество страниц: ";
    std::cin >> book.numberOfPages;

    return book;
}

int main() {
    const int numberOfBooks = 3;      // Количество книг, которые будут введены

    // Массив книг
    Book books[numberOfBooks];

    // Цикл для ввода данных о каждой книге
    for (int i = 0; i < numberOfBooks; ++i) {
        // Спрашиваем пользователя, хочет ли он ввести данные для текущей книги
        std::cout << "Хотите ввести данные для книги " << i + 1 << "? (y/n): ";
        char answer;
        std::cin >> answer;

        if (answer == 'y' || answer == 'Y') {
            // Если пользователь согласен, вызываем функцию createBook для заполнения структуры Book
            books[i] = createBook();
        } else {
            // Если пользователь отказался, используем конструктор по умолчанию для инициализации полей структуры Book
            books[i] = Book();
        }
    }

    // Цикл для вывода информации о каждой книге на экран
    for (int i = 0; i < numberOfBooks; ++i) {
        std::cout << "Информация о книге " << i + 1 << ":" << std::endl;
        books[i].displayBook();
    }

    return 0;
}
