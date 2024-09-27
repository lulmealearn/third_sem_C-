#include <iostream>
#include <string>
using namespace std;

int main() 
{ 
    string str_1, str_2;
    int count = 0, len_1 = 0, len_2 = 0, substring;

    cin >> str_1;
    cin >> str_2;

    len_1 = str_1.length();
    len_2 = str_2.length();

    for (int i = 0; i < (len_1 - len_2); )
    {
        substring = str_1.find(str_2, i);

        if (substring == string::npos)
        {
            break;
        }

        ++count;

        i = substring + len_2 - 1;
    }

    cout << count;
}
