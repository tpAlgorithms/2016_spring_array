#include <iostream>

int i;

int* make_array(int size) {
  int *data = new int[size];
  for (i = 0; i < size; ++i) {
    data[i] = (i * i) % 43; 
  }
  return data;
}

int main() {
  int *first = make_array(123);
  int *second = make_array(123);
  
  for (i = 0; i < 123; ++i) {
    std::cout << first[i] << " ";
  }
  std::cout << std::endl;
  
  delete [] first;
  delete [] second;
  return 0;
};
