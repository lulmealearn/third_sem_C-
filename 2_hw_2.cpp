#include <iostream>
using namespace std;

int main() 
{ 
    int array_size, value, intermediate_value;
    cin >> array_size;
    intermediate_value = 0;
  
    int *array = new int[array_size];
  
    for (int i = 0; i < array_size; i++) 
    {
        cin >> value;

        if (value == 0) 
        {
            break;
        }

        if (i == 0) 
        {
            array[i] = value;
        }

        if (i >= 1) 
        {
            array[i] = array[i - 1] + value;
            cout << array[i] << "\n";
        }
    }  

    delete[] array;      
}
