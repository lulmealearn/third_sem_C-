// Включаем стандартный заголовочный файл для ввода/вывода
#include <iostream>
// Включаем стандартный заголовочный файл для математических функций
#include <cmath>

int main() {
    // Объявляем переменную для хранения введенного числа
    int number;
    
    // Выводим приглашение пользователю ввести число
    std::cout << "Введите число: ";
    
    // Читаем ввод пользователя и сохраняем его в переменную number
    std::cin >> number;

    // Инициализируем переменную divisor для проверки делителей, начиная с 2
    int divisor = 2; 
    
    // Инициализируем переменную largest_divisor для хранения наибольшего делителя
    int largest_divisor = 1; 
    
    // Предполагаем, что число простое до тех пор, пока не будет найден делитель
    bool is_prime = true; 
    
    // Цикл проверки делителей числа, продолжающийся до квадратного корня из числа
    while (divisor <= sqrt(number)) {
        // Проверяем, является ли текущее значение divisor делителем числа
        if (number % divisor == 0) {
            // Если divisor является делителем, обновляем largest_divisor
            largest_divisor = number / divisor; 
            // Устанавливаем is_prime в false, указывая, что число не простое
            is_prime = false; 
        }
        // Инкрементируем divisor для проверки следующего потенциального делителя
        divisor++;
    }

    // Проверяем, является ли число простым или нет
    if (!is_prime) {
        // Если число не простое, выводим наибольший делитель
        std::cout << "Наибольший делитель числа " << number << ": " << largest_divisor << std::endl;
    } else {
        // Если число простое, выводим соответствующее сообщение
        std::cout << "Число " << number << " является простым." << std::endl;
    }

    // Возвращаем значение 0 из основной функции, указывая на успешное завершение программы
    return 0;
}
