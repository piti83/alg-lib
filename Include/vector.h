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
// File: vector.h
//
// This file contains the implementation of the Vector class. Implementation
// is based on templates, so the class can be used with any type. Vector class
// implements an array that can be extended and shrinked. All elements are
// allocated on the heap. Capacity doubles every time the size exceeds current
// capacity.
//*****************************************************************************

#ifndef ALGLIB_INCLUDE_VECTOR_H_
#define ALGLIB_INCLUDE_VECTOR_H_

#include "constants.h"

/// <summary>
/// Default namespace for the AlgLib library.
/// </summary>
namespace alglib {

template <typename VectorType> class VectorIter {
public:
  // TODO: add definitions for operators and constructors.
  VectorType &operator*();
  VectorType &operator++();
  VectorType operator++(VectorType);
  bool operator!=(const VectorIter &);
  bool operator==(const VectorIter &);

private:
  VectorType *_ptr;
};

/// <summary>
/// Template based vector implementation that uses an array as a base structure.
/// It allocates memory on the heap, and it can grow dynamically. Capacity
/// doubles every time the size exceeds current capacity.
/// </summary>
/// <typeparam name="T"> type of data stored in vector.</typeparam>
template <typename T> class Vector {
public:
  // Constructors for vector class;
  Vector() noexcept;
  Vector(size_t elements) noexcept;
  Vector(size_t elements, const T &value) noexcept;

  // Inserting and removing elements from the vector.
  void Push(const T &value) noexcept;
  void Insert(const T &value, size_t index);
  T &Pop();

  // Accessing elements in the vector.
  T &At(size_t index);
  const T &At(size_t index) const;

  // Getting size and capacity of the vector.
  size_t Size() const noexcept;
  size_t Capacity() const noexcept;

  // Resizing and shrinking the vector.
  void Resize(size_t size);
  void ShrinkToFit();

  // Getting first and last element of the vector.
  T &Front();
  const T &Front() const;
  T &Back();
  const T &Back() const;

  // Destructor for the vector class.
  ~Vector() noexcept;

private:
  // Method that reallocates memory for the vector.
  void Reallocate(size_t amount);

  /// <summary>
  /// Amount of elements in the vector.
  /// </summary>
  size_t size;
  /// <summary>
  /// Maximum capacity of the vector. It grows when the size exceeds capacity.
  /// </summary>
  size_t capacity;

  /// <summary>
  /// Array that holds the data of the vector.
  /// </summary>
  T *data;
};

template <typename VectorType> VectorType &VectorIter<VectorType>::operator*() {
  return *_ptr;
}

/// <summary>
/// No argument constructor for the vector class. It initializes the vector with
/// default values. It allocates memory for 4 elements.
/// </summary>
template <typename T>
Vector<T>::Vector() noexcept : size(0), capacity(0), data(nullptr) {
  Reallocate(4);
}

/// <summary>
/// Constructor that initializes the vector with a given number of elements.
/// </summary>
/// <param name="elements"> amount of elements that will be initially
/// allocated.</param>
template <typename T>
Vector<T>::Vector(size_t elements) noexcept
    : size(0), capacity(0), data(nullptr) {
  Reallocate(elements);
}

/// <summary>
/// Constructor that initializes the vector to a given number of elements with a
/// given value. All elements will be set to the given value.
/// </summary>
/// <param name="elements"> amount of elements that will be initially
/// allocated. </param>
/// <param name="value"> value that all the elements will be
/// initialised to.</param>
template <typename T>
Vector<T>::Vector(size_t elements, const T &value) noexcept
    : size(0), capacity(0), data(nullptr) {
  Reallocate(elements);
  for (size_t i{}; i < capacity; ++i) {
    data[i] = value;
  }
}

/// <summary>
/// Adds a new element to the end of the vector. If the size exceeds the
/// capacity, the capacity is doubled.
/// </summary>
/// <param name="value"> value to be added.</param>
template <typename T> void Vector<T>::Push(const T &value) noexcept {
  if (size >= capacity) {
    Reallocate(capacity * 2);
  }
  data[size++] = value;
}

/// <summary>
/// Inserts a new element at a given index. If the index is out of range, an
/// exception is thrown. If the size exceeds the capacity, the capacity is
/// doubled just like in the Push method.
/// </summary>
/// <param name="value"> value to be inserted.</param>
/// <param name="index"> inserting position.</param>
template <typename T> void Vector<T>::Insert(const T &value, size_t index) {
  if (index > size) {
    throw std::runtime_error(errors::kIndexOutOfRange);
  }
  if (size + 1 > capacity) {
    Reallocate(capacity == 0 ? 1 : capacity * 2);
  }
  for (size_t i{size}; i > index; --i) {
    data[i] = data[i - 1];
  }
  data[index] = value;
  size++;
}

/// <summary>
/// Returns the last element of the vector and removes it from the vector by
/// decrementing the size.
/// </summary>
/// <returns> last element of the vector.</returns>
template <typename T> T &Vector<T>::Pop() { return data[size--]; }

/// <summary>
/// Returns the element at a given index. If the index is out of range, an
/// exception is thrown.
/// </summary>
/// <param name="index"> index of element to return.</param>
/// <returns> element at a given index.</returns>
template <typename T> T &Vector<T>::At(size_t index) {
  if (index >= size) {
    throw std::runtime_error(errors::kIndexOutOfRange);
  }
  return data[index];
}

/// <summary>
/// Returns the element at a given index. If the index is out of range, an
/// exception is thrown.
/// </summary>
/// <param name="index"> index of element to return.</param>
/// <returns> element at a given index.</returns>
template <typename T> const T &Vector<T>::At(size_t index) const {
  if (index >= size) {
    throw std::runtime_error(errors::kIndexOutOfRange);
  }
  return data[index];
}

/// <summary>
/// Return amount of elements in the vector.
/// </summary>
/// <returns> amount of elements in the vector.</returns>
template <typename T> size_t Vector<T>::Size() const noexcept { return size; }

/// <summary>
/// Returns current maximum capacity of the vector.
/// </summary>
/// <returns> current maximum capacity of the vector.</returns>
template <typename T> size_t Vector<T>::Capacity() const noexcept {
  return capacity;
}

/// <summary>
/// Modifies the size of the vector. If the new size is smaller than the current
/// size, the vector is truncated. If the new size is larger than the current
/// size, the vector is extended.
/// </summary>
/// <param name="size"> new size.</param>
template <typename T> void Vector<T>::Resize(size_t size) { Reallocate(size); }

/// <summary>
/// Shrinks the capacity of the vector to the current size by
/// reallocating memory with the size of the vector.
/// </summary>
template <typename T> void Vector<T>::ShrinkToFit() { Reallocate(size); }

/// <summary>
/// Returns the first element of the vector.
/// </summary>
/// <returns> first element of the vector.</returns>
template <typename T> T &Vector<T>::Front() { return data[0]; }

/// <summary>
/// Returns the first element of the vector.
/// </summary>
/// <returns> first element of the vector.</returns>
template <typename T> const T &Vector<T>::Front() const { return data[0]; }

/// <summary>
/// Returns the last element of the vector.
/// </summary>
/// <returns> last element of the vector.</returns>
template <typename T> T &Vector<T>::Back() { return data[size - 1]; }

/// <summary>
/// Returns the last element of the vector.
/// </summary>
/// <returns> last element of the vector.</returns>
template <typename T> const T &Vector<T>::Back() const {
  return data[size - 1];
}

/// <summary>
/// Deletes the vector and deallocates memory.
/// </summary>
template <typename T> Vector<T>::~Vector() noexcept { delete[] data; }

/// <summary>
/// Reallocates memory for the vector. It copies all the elements from the old
/// array to the new array. If the new capacity is smaller than the current
/// size, the size is truncated.
/// </summary>
/// <param name="amount"> new amount of elements.</param>
template <typename T> void Vector<T>::Reallocate(size_t amount) {
  T *new_data{new T[amount]};
  size = (amount < size) ? amount : size;
  for (size_t i{}; i < size; ++i) {
    new_data[i] = data[i];
  }
  delete[] data;
  data = new_data;
  capacity = amount;
}
} // namespace alglib

#endif // ALGLIB_INCLUDE_VECTOR_H_
