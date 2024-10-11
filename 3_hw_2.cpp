#include <iostream>
#define N 100

struct Vector {
    float m[N];

    Vector() {
        for (int i = 0; i < N; i++) {
            m[i] = 0.0f;
        }
    }

    void multiply(float a) {
        for (int i = 0; i < N; i++) {
            m[i] *= a;
        }
    }


    void display() const {
        for (int i = 0; i < N; i++) {
            std::cout << m[i] << " ";
        }
        std::cout << std::endl;
    }
};


Vector sum(const Vector& a, const Vector& b) {
    Vector c;
    for (int i = 0; i < N; i++) {
        c.m[i] = a.m[i] + b.m[i];
    }
    return c;
}


float dotProduct(const Vector& a, const Vector& b) {
    float result = 0.0f;
    for (int i = 0; i < N; i++) {
        result += a.m[i] * b.m[i];
    }
    return result;
}

int main() {
    std::cout << "Write " << N << " coordinates of two vectors:" << std::endl;
    Vector v1, v2;


    std::cout << "Enter coordinates for the first vector:" << std::endl;
    for (int i = 0; i < N; i++) {
        float x;
        std::cin >> x;
        v1.m[i] = x;
    }

    std::cout << "Enter coordinates for the second vector:" << std::endl;
    for (int i = 0; i < N; i++) {
        float y;
        std::cin >> y;
        v2.m[i] = y;
    }

    float scalar;
    std::cout << "Enter a scalar to multiply the first vector: ";
    std::cin >> scalar;
    Vector v1Scaled = v1;
    v1Scaled.multiply(scalar);
    std::cout << "Scaled vector: ";
    v1Scaled.display();

    Vector v3 = sum(v1, v2);
    std::cout << "Sum of vectors: ";
    v3.display();

    float dotProductResult = dotProduct(v1, v2);
    std::cout << "Dot product of vectors: " << dotProductResult << std::endl;

    return 0;
}
