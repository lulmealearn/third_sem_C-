#include <iostream>
#include <math.h>
using namespace std;

int main() 
{   
    double the_square_root;
    int value, remains, divider;
    cin >> value;
    
    divider = 0;
    remains = 0;

    if (value == 1) 
    {
        cout << "1";
    }

    if (value == 2) 
    {
        cout << "Простое число";
    }

    if (value > 2) 
    {
        the_square_root = sqrt(value);

        for (int i = 2; i <= the_square_root; i++) 
        {
            remains = value % i;

            if (remains == 0) 
            {
                divider = i;
            }
        }

        if (divider == 0) 
        {
            cout << "Простое число\n";
        } 
        else 
        {
            cout << divider;
        }
    } 
}
