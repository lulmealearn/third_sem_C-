#include <iostream>
#include <cmath>

int main() {
    int number;
    std::cout << "Введите число: ";
    std::cin >> number;

    int divisor = 2; 
    int largest_divisor = 1; 
    bool is_prime = true; 
    
    while (divisor <= sqrt(number)) {
        if (number % divisor == 0) {
            largest_divisor = number / divisor; 
            is_prime = false; 
        }
        divisor++;
    }


    if (!is_prime) {
        std::cout << "Наибольший делитель числа " << number << ": " << largest_divisor << std::endl;
    }
    
    else {
        std::cout << "Число " << number << " является простым." << std::endl;
    }

    return 0;
}
