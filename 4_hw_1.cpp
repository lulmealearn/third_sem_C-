#include <iostream>
#include <numeric>
using namespace std;

#define SIZE 100
#define DYNAMIC_MEMORY

void Filling_the_array(int* array, int length){
  for(int i = 0; i<length; i++){
    array[i] = i*i;
  }
  for(int i = 0; i<length; i++){
  cout<<array[i]<<' ';  
  }

}

int main() 
{
#ifdef DYNAMIC_MEMORY
  int* array = new int[SIZE];
  int*& link_array_2 = array;
  Filling_the_array(link_array_2, SIZE);

#else
  int array[SIZE];
  int (&link_array_1)[SIZE] = array;
  Filling_the_array(link_array_1, SIZE);

#endif

#ifdef DYNAMIC_MEMORY
  delete[] array;
#else
  return 0;
#endif

}
