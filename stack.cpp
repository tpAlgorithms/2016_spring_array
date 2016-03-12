#include <cstdio>

struct stack_t {
  static const int DEFAULT_SIZE = 42;
  
  int *data;
  int capacity;
  int size;
};

void stack_init(stack_t &stack) {
  stack.data = new int[stack_t::DEFAULT_SIZE];
  stack.capacity = stack_t::DEFAULT_SIZE;
  stack.size = 0;
}

template <typename T>
void swap(T &a, T &b) {
  T tmp = a;
  a = b;
  b = tmp;
}

void stack_resize(stack_t &stack, int new_capacity) {
  int *tmp = new int[new_capacity];
  for (int i = 0; i < stack.size && i < new_capacity; ++i) {
    swap(tmp[i], stack.data[i]);
  }
  //delete [] stack.data;
  swap(stack.data, tmp);
  delete [] stack.data;
  stack.capacity = new_capacity;
  if (new_capacity < stack.size) {
    stack.size = new_capacity;
  }
}

void stack_push(stack_t &stack, int value) {
  if (stack.size == stack.capacity) {
    stack_resize(stack, stack.capacity * 2);
  }
  stack.data[stack.size] = value;
  ++stack.size;
}

bool stack_empty(const stack_t &stack) {
  return stack.size == 0;
}

int stack_head(const stack_t &stack) {
  return stack.data[stack.size - 1];
}

void stack_pop(stack_t &stack) {
  --stack.size;
}

void stack_clear(stack_t & stack) {
  delete [] stack.data;
  stack.data = NULL;
  stack.capacity = 0;
  stack.size = 0;
}


int main() {
  stack_t stack;
  stack_init(stack);
  
  for (int i = 0; i < 10; ++i) {
    stack_push(stack, (i * i) % 43);
  }

  while(!stack_empty(stack)) {
    int value = stack_head(stack);
    printf("%d ", value);
    stack_pop(stack);
  }

  stack_clear(stack);

  return 0;
}
