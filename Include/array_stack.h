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
// File: array_stack.h
//
// This file contains the implementation of the ArrayStack class. Implementation
// is based on templates, so the class can be used with any type. ArrayStack
// is a stack implementation that uses an array as a base structure. It doesn't
// allocate memory on the heap, so it is faster than the implementation that
// can grow dynamically. The class is implemented in the alglib namespace.
//*****************************************************************************

#ifndef ALGLIB_INCLUDE_ARRAYSTACK_H_
#define ALGLIB_INCLUDE_ARRAYSTACK_H_

#include <array>
#include <stdexcept>

#include "constants.h"

/// <summary>
/// Default namespace for the AlgLib library.
/// </summary>
namespace alglib {

/// <summary>
/// Template based stack implementation that uses an array as a base structure.
/// It doesn't allocate memory on the heap, but it has a fixed capacity that has
/// to be defined at compile time.
/// </summary>
/// <typeparam name="T"> type of data stored in stack</typeparam>
/// <typeparam name="capacity"> max capacity of stack (size of
/// array)</typeparam>
template <typename T, size_t capacity>
class ArrayStack {
 public:
  // Constructor for the ArrayStack.
  ArrayStack();

  // Methods for manipulating the stack.
  void Push(T val);
  T Pop();
  T Top() const;
  bool IsEmpty() const noexcept;
  bool IsFull() const noexcept;
  size_t Size() const noexcept;
  size_t Capacity() const noexcept;

 private:
  /// <summary>
  /// Array that holds the data of the stack.
  /// </summary>
  std::array<T, capacity> data;

  /// <summary>
  /// Index of the top element in the stack.
  /// </summary>
  int topIndex;
};

/// <summary>
/// ArrayStack constructor. Only initializes the topIndex to -1.
/// </summary>
template <typename T, size_t capacity>
ArrayStack<T, capacity>::ArrayStack() : topIndex(-1), data() {}

/// <summary>
/// Pushes a value to the top of the stack.
/// Handles the topIndex and checks if the stack is full.
/// </summary>
/// <param name="val"> value to be pushed.</param>
template <typename T, size_t capacity>
void ArrayStack<T, capacity>::Push(T val) {
  topIndex++;
  if (topIndex >= capacity) {
    throw std::runtime_error(errors::kObjectFull);
  }
  data[topIndex] = val;
}

/// <summary>
/// Pops the value from the top of the stack.
/// </summary>
/// <returns> value that was on the top of the stack.</returns>
template <typename T, size_t capacity>
T ArrayStack<T, capacity>::Pop() {
  if (topIndex < 0) {
    throw std::runtime_error(errors::kEmptyDeletion);
  }
  return data.at(topIndex--);
}

/// <summary>
/// Method that gets the value from the top of the stack without removing it.
/// </summary>
/// <returns>vale that is on the top of the stack.</returns>
template <typename T, size_t capacity>
T ArrayStack<T, capacity>::Top() const {
  if (IsEmpty()) {
    throw std::runtime_error(errors::kPeekAtEmpty);
  }
  return data.at(topIndex);
}

/// <summary>
/// Method that checks if the stack is empty.
/// </summary>
/// <returns>true if empty, false if not</returns>
template <typename T, size_t capacity>
bool ArrayStack<T, capacity>::IsEmpty() const noexcept {
  return topIndex < 0;
}

/// <summary>
/// Method that checks if the stack is full.
/// </summary>
/// <returns>true if stack is full, false if not.</returns>
template <typename T, size_t capacity>  
bool ArrayStack<T, capacity>::IsFull() const noexcept {  
 return topIndex == capacity - 1;  
}

/// <summary>
/// Method that gets amount of elements in the stack.
/// </summary>
/// <returns> number of items in the stack.</returns>
template <typename T, size_t capacity>
size_t ArrayStack<T, capacity>::Size() const noexcept {
  return topIndex + 1;
}

/// <summary>
/// Method that gets the maximum capacity of the stack.
/// </summary>
/// <returns> maximum capacity of the stack.</returns>
template <typename T, size_t capacity>
size_t ArrayStack<T, capacity>::Capacity() const noexcept {
  return capacity;
}

}  // namespace alglib

#endif  // ALGLIB_INCLUDE_ARRAYSTACK_H_