#include <iostream>
#include <numeric>
using namespace std;

int main() 
{ 
    int size_array, sum = 0;
    cin >> size_array;

    int *arr = new int[size_array];

    for (int i = 0; i < size_array; ++i) 
    {
        arr[i] = i * i;
    }

    sum = accumulate(arr, arr + size_array, 0);

    cout << sum;

    delete[] arr;
}
