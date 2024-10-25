// Включаем стандартный заголовочный файл для ввода/вывода
#include <iostream>

// Определение константы N, которая представляет размер вектора
const int N = 3; // Примерное значение, можно изменить

// Определение структуры Vector для хранения и манипуляций с векторами
struct Vector {
    float m[N]; // Массив для хранения координат вектора

    // Конструктор по умолчанию для инициализации полей структуры Vector
    Vector() {
        for (int i = 0; i < N; i++) {
            m[i] = 0.0f; // Инициализируем все координаты вектора нулем
        }
    }

    // Метод для умножения вектора на скаляр
    void multiply(float a) {
        for (int i = 0; i < N; i++) {
            m[i] *= a; // Умножаем каждую координату вектора на скаляр
        }
    }

    // Метод для вывода координат вектора на экран
    void display() const {
        for (int i = 0; i < N; i++) {
            std::cout << m[i] << " "; // Выводим каждую координату вектора
        }
        std::cout << std::endl;
    }
};

// Функция для суммирования двух векторов
Vector sum(const Vector& a, const Vector& b) {
    Vector c; // Создаем новый вектор для хранения суммы
    for (int i = 0; i < N; i++) {
        c.m[i] = a.m[i] + b.m[i]; // Суммируем соответствующие координаты двух векторов
    }
    return c;
}

// Функция для вычисления скалярного произведения двух векторов
float dotProduct(const Vector& a, const Vector& b) {
    float result = 0.0f; // Инициализируем результат скалярного произведения нулем
    for (int i = 0; i < N; i++) {
        result += a.m[i] * b.m[i]; // Суммируем произведения соответствующих координат двух векторов
    }
    return result;
}

int main() {
    // Выводим сообщение о количестве координат, которые нужно ввести для двух векторов
    std::cout << "Write " << N << " coordinates of two vectors:" << std::endl;

    // Создаем два объекта типа Vector
    Vector v1, v2;

    // Вводим координаты первого вектора
    std::cout << "Enter coordinates for the first vector:" << std::endl;
    for (int i = 0; i < N; i++) {
        float x;
        std::cin >> x; // Читаем координату из стандартного ввода
        v1.m[i] = x; // Записываем координату в первый вектор
    }

    // Вводим координаты второго вектора
    std::cout << "Enter coordinates for the second vector:" << std::endl;
    for (int i = 0; i < N; i++) {
        float y;
        std::cin >> y; // Читаем координату из стандартного ввода
        v2.m[i] = y; // Записываем координату во второй вектор
    }

    // Вводим скаляр для умножения первого вектора
    float scalar;
    std::cout << "Enter a scalar to multiply the first vector: ";
    std::cin >> scalar;

    // Создаем копию первого вектора и умножаем ее на скаляр
    Vector v1Scaled = v1;
    v1Scaled.multiply(scalar);

    // Выводим результат умножения на скаляр
    std::cout << "Scaled vector: ";
    v1Scaled.display();

    // Вычисляем сумму двух векторов и выводим результат
    Vector v3 = sum(v1, v2);
    std::cout << "Sum of vectors: ";
    v3.display();

    // Вычисляем скалярное произведение двух векторов и выводим результат
    float dotProductResult = dotProduct(v1, v2);
    std::cout << "Dot product of vectors: " << dotProductResult << std::endl;

    return 0;
}
