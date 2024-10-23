#include <iostream>
#include <numeric>
using namespace std;

int find(int* array, int value, int lenth){
int counter = 0;
cout<<"Поиск элемента в массиве типа int:\n";
for(int i = 0; i<lenth; i++){
  if (array[i]==value){
    cout<<"Элемент есть в массиве типа int\n";
    cout<<"Его индекс в массиве "<< i<<"\n";
    counter = 1;
    cout<<"\n";
  }
}
if (counter==0){
  cout<<"Такого элемента нет в массиве\n";
  cout<<"\n";
}
}


float find(float* array, float value, int lenth){
int counter = 0;
cout<<"Поиск элемента в массиве типа float\n";
for(int i = 0; i<lenth; i++){
  if (array[i]==value){
    cout<<"Элемент есть в массиве типа float\n";
    cout<<"Его индекс в массиве "<< i<<"\n";
    counter = 1;
    cout<<"\n";
  }
}
if (counter==0){
  cout<<"Такого элемента нет в массиве\n";
  cout<<"\n";
}
}

char find(char* array, char value, int lenth){
int counter = 0;
cout<<"Поиск элемента в массиве типа char\n";
for(int i = 0; i<lenth; i++){
  if (array[i]==value){
    cout<<"Элемент есть в массиве типа char\n";
    cout<<"Его индекс в массиве "<< i<<"\n";
    counter = 1;
    cout<<"\n";
  }
}
if (counter==0){
  cout<<"Такого элемента нет в массиве\n";
  cout<<"\n";
}
}


int main() {
int size_integers, size_floating_point, size_character;
int find_integers;
float find_floating_point;
char find_character;

cout<<"Введите размер массива типа int\n";
cin>> size_integers;
cout<<"Введите массив типа int\n";
int array_integers[size_integers];

for(int i = 0; i < size_integers; i++){
  cin>>array_integers[i];
}
cout<<"Введите элемент типа int, который необходимо найти\n";
cin>>find_integers;


cout<<"Введите размер массива типа float\n";
cin>> size_floating_point;
cout<<"Введите массив типа float\n";
float array_floating_point[size_floating_point];

for(int i = 0; i < size_floating_point; i++){
  cin>>array_floating_point[i];
}
cout<<"Введите элемент типа float, который необходимо найти\n";
cin>>find_floating_point;


cout<<"Введите размер массива типа char\n";
cin>> size_character;
cout<<"Введите массив типа char\n";
char array_character[size_character];

for(int i = 0; i < size_character; i++){
  cin>>array_character[i];
}
cout<<"Введите элемент типа char, который необходимо найти\n";
cin>>find_character;

find(array_integers, find_integers, size_integers);
find(array_floating_point, find_floating_point, size_floating_point);
find(array_character, find_character, size_character);

}
