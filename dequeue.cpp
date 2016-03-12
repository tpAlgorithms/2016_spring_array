#include <cstdio>
#include <iostream>


struct node_t {
  int data;
  node_t *next;
  node_t *prev;

  node_t(const int &value):data(value), next(this), prev(this) {}
};

struct dequeue_t {
  node_t *head;

  dequeue_t(): head(NULL) {}
  ~dequeue_t() {
    clear();
  }

  void clear() {
    while(!empty()) {
      pop_back();
    }
  }

  void push_back(const int& value) {
    node_t *node = new node_t(value);
    if (head == NULL) {
      head = node;
      return;
    }

    node->next = head;
    node->prev = head->prev;
    head->prev->next = node;
    head->prev = node;
  }
  
  void push_front(const int& value) {
    push_back(value);
    head = head->prev;
  }

  void pop_back() {
    node_t *node = head->prev;

    head->prev = head->prev->prev;
    head->prev->next = head;

    if (head == node) {
      head = NULL;
    }
    delete node;
  }
  void pop_front() {
    head = head->next;
    pop_back();
  }

  bool empty() const {
    return head == NULL;
  }

  const int& front() const {
    return head->data;
  }
  const int& back() const {
    return head->prev->data;
  }
};

int main() {
  dequeue_t queue;

  for (int i = 0; i < 10; ++i) {
    queue.push_front(i);
  }

  for (; !queue.empty(); queue.pop_back()) {
    std::cout << queue.back() << " ";
  }
  std::cout << std::endl;

  return 0;
}













