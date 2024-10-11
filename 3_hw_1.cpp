#include <iostream>
#define DYNAMIC_MEMORY 0
#define N 17

void fillArray(int* arr) {
    for (int i = 0; i < N; i++) {
        arr[i] = i * i;
        std::cout << arr[i] << '\n';
    }
}


void fillArray(double* arr) {
    for (int i = 0; i < N; i++) {
        arr[i] = i * i;
        std::cout << arr[i] << '\n';
    }
}


void fillArrayHalf(double* arr) {
    for (int i = 0; i < N; i++) {
        arr[i] = (double)i * i / 2;
        std::cout << arr[i] << '\n';
    }
}

int main() {
    #if DYNAMIC_MEMORY == 1

        int* numbers = new int[N];
        fillArray(numbers);
        delete[] numbers;
    #else

        double massiv[N];
        double* mas = massiv;
        fillArray(mas);
        fillArrayHalf(mas);
    #endif

    return 0;
}
