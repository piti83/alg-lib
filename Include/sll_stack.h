//*****************************************************************************
// The MIT License (MIT)
//
// Copyright � 2024 Piotr Walczak
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the �Software�), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED �AS IS�, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//*****************************************************************************

//*****************************************************************************
// File: sll_stack.h
//
// This file contains the implementation of the ListStack class. Implementation
// is based on templates, so the class can be used with any type. ListStack
// is a stack implementation that uses a singly linked list as a base structure.
// It allocates memory on the heap, so the stack can grow dynamically. The class
// is implemented in the alglib namespace.
//*****************************************************************************

#ifndef ALGLIB_INCLUDE_LISTSTACK_H_
#define ALGLIB_INCLUDE_LISTSTACK_H_

#include <stdexcept>

#include "constants.h"

/// <summary>
/// Default namespace for the AlgLib library.
/// </summary>
namespace alglib {

/// <summary>
/// SLLStack is a stack implementation that uses a singly linked list as a base
/// structure. It allocates memory on the heap, so the stack can grow
/// dynamically.
/// </summary>
/// <typeparam name="T"> type of data stored on the stack.</typeparam>
template <typename T>
class SLLStack {
 public:
  // Constructor for the ArrayStack.
  SLLStack();

  // Methods for manipulating the stack.
  void Push(T val) noexcept;
  T Pop();
  T Top() const;
  bool IsEmpty() const noexcept;
  size_t Size() const noexcept;

  // Destructor for the ArrayStack.
  ~SLLStack();

 private:
  /// <summary>
  /// Node structure for the singly linked list stack.
  /// Each element on the stack is stored in the node.
  /// </summary>
  struct Node {
    Node(T data);
    T data;
    Node *next;
  };

  /// <summary>
  /// Pointer to the top element of the stack.
  /// </summary>
  Node *top;
};

/// <summary>
/// Constructor for the Node structure. Sets up the initial values for the node.
/// </summary>
/// <param name="data"> value that will be stored in node.</param>
template <typename T>
SLLStack<T>::Node::Node(T data) : data(data), next(nullptr) {}

/// <summary>
/// Constructor for the SLLStack. Initializes the top pointer to nullptr.
/// </summary>
template <typename T>
SLLStack<T>::SLLStack() : top(nullptr) {}

/// <summary>
/// Pushes a value to the top of the stack by creating a new node on the heap
/// and setting the next pointer to the current top. The top pointer is then set
/// to the new node.
/// </summary>
/// <param name="val"> value to be pushed on the stack.</param>
template <typename T>
void SLLStack<T>::Push(T val) noexcept {
  Node *new_node{new Node(val)};
  new_node->next = top;
  top = new_node;
}

/// <summary>
/// Pops the value from the top of the stack and returns it. The top node is
/// deleted.
/// </summary>
/// <returns> value on top of the stack.</returns>
template <typename T>
T SLLStack<T>::Pop() {
  if (IsEmpty()) {
    throw std::runtime_error(errors::kEmptyDeletion);
  }
  T val{top->data};
  Node *tmp{top};
  top = top->next;
  delete tmp;
  return val;
}

/// <summary>
/// Returns value from the top of the stack without removing it.
/// </summary>
/// <returns> value on top of the stack.</returns>
template <typename T>
T SLLStack<T>::Top() const {
  if (IsEmpty()) {
    throw std::runtime_error(errors::kPeekAtEmpty);
  }
  return top->data;
}

/// <summary>
/// Checks if the stack is empty by checking if the top pointer is nullptr.
/// </summary>
/// <returns>true if empty, false if not.</returns>
template <typename T>
bool SLLStack<T>::IsEmpty() const noexcept {
  return top == nullptr;
}

/// <summary>
/// Calculates size of the stack by traversing the list and counting the nodes.
/// </summary>
/// <returns>amount values on stack.</returns>
template <typename T>
size_t SLLStack<T>::Size() const noexcept {
  size_t count{};
  Node *tmp{top};
  while (tmp) {
    ++count;
    tmp = tmp->next;
  }
  return count;
}

/// <summary>
/// Removes all nodes from the stack by traversing the list and deleting each.
/// </summary>
template <typename T>
SLLStack<T>::~SLLStack() {
  Node *tmp{top};
  while (tmp) {
    Node *next{tmp->next};
    delete tmp;
    tmp = next;
  }
}

}  // namespace alglib

#endif  // ALGLIB_INCLUDE_LISTSTACK_H_
