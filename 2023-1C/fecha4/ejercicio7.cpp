#include <cstdlib>
#include <iostream>

#define SIZE 10

using namespace std;

template <typename T> class Stack {
private:
  T *arr;
  T top;
  int capacity;

public:
  Stack(int size = SIZE);
  ~Stack();

  void push(T x);
  T pop();
  T peek() const;

  int size() const;
  bool isEmpty() const;
  bool isFull() const;

  Stack<T> operator+(const Stack<T> &other) const;
  bool operator==(const Stack<T> &other) const;
  operator int() const;

  template <typename U>
  friend ostream &operator<<(ostream &os, const Stack<U> &stack);

  template <typename U>
  friend istream &operator>>(istream &is, Stack<U> &stack);
};

template <typename T> Stack<T>::Stack(int size) {
  arr = new T[size];
  capacity = size;
  top = -1;
}

template <typename T> Stack<T>::~Stack() { delete[] arr; }

template <typename T> void Stack<T>::push(T x) {
  if (isFull()) {
    cout << "Stack is full" << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Inserting " << x << endl;
  arr[++top] = x;
}

template <typename T> T Stack<T>::pop() {
  if (isEmpty()) {
    cout << "Stack is empty" << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Removing " << peek() << endl;

  return arr[top--];
}

template <typename T> T Stack<T>::peek() const {
  if (isEmpty()) {
    cout << "Stack is empty" << endl;
    exit(EXIT_FAILURE);
  }

  return arr[top];
}

template <typename T> int Stack<T>::size() const { return top + 1; }

template <typename T> bool Stack<T>::isEmpty() const { return top == -1; }

template <typename T> bool Stack<T>::isFull() const {
  return top == capacity - 1;
}

template <typename T>
Stack<T> Stack<T>::operator+(const Stack<T> &other) const {
  Stack<T> result(this->size() + other.size());

  for (int i = 0; i <= this->top; ++i) {
    result.push(this->arr[i]);
  }

  for (int i = 0; i <= other.top; ++i) {
    result.push(other.arr[i]);
  }

  return result;
}

template <typename T> bool Stack<T>::operator==(const Stack<T> &other) const {
  if (this->size() != other.size()) {
    return false;
  }

  for (int i = 0; i <= this->top; ++i) {
    if (this->arr[i] != other.arr[i]) {
      return false;
    }
  }

  return true;
}

template <typename T> Stack<T>::operator int() const {
  if (!isEmpty()) {
    return static_cast<int>(this->arr[this->top]);
  }
  return 0;
}

template <typename U> ostream &operator<<(ostream &os, const Stack<U> &stack) {
  for (int i = stack.top; i >= 0; --i) {
    os << stack.arr[i] << " ";
  }
  return os;
}

template <typename U> istream &operator>>(istream &is, Stack<U> &stack) {
  int num;
  while (is >> num) {
    stack.push(num);
  }
  return is;
}

int main() {
  Stack<int> stack1;
  Stack<int> stack2;

  stack1.push(1);
  stack1.push(2);

  stack2.push(1);
  stack2.push(2);

  cout << "Stack 1: " << stack1 << endl;
  cout << "Stack 2: " << stack2 << endl;

  if (stack1 == stack2) {
    cout << "Stacks are equal." << endl;
  } else {
    cout << "Stacks are not equal." << endl;
  }

  int topValue = static_cast<int>(stack1);

  std::cout << "Top value of the stack: " << topValue << std::endl;

  return 0;
}