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
// File: circular_queue.h
//
// This file contains the implementation of the CircularQueue class.
// Implementation is based on templates, so the class can be used with any type.
// CircularQueue is a queue implementation that uses an array as a base
// structure. It doesn't allocate memory on the heap, but it has a fixed
// capacity.
//*****************************************************************************

#ifndef ALGLIB_INCLUDE_CIRCULARQUEUE_H_
#define ALGLIB_INCLUDE_CIRCULARQUEUE_H_

#include <array>
#include <stdexcept>

#include "constants.h"

/// <summary>
/// Default namespace for the AlgLib library.
/// </summary>
namespace alglib {

/// <summary>
/// CircularQueue class is a queue data structure implemented using an array.
/// It doesn't allocate memory on the heap and has a fixed capacity that has
/// to be defined at compile time. It uses a circular buffer to store elements.
/// </summary>
/// <typeparam name="T"> type that will be stored in queue.</typeparam>
/// <typeparam name="capacity"> max capacity of queue.</typeparam>
template <typename T, size_t capacity>
class CircularQueue {
 public:
  // Constructor for the CircularQueue.
  CircularQueue();

  // Manipulation methods for the queue.
  bool IsEmpty() const noexcept;
  bool IsFull() const noexcept;
  T Dequeue();
  void Enqueue(T value);

  // Methods for peeking at values in the queue.
  T PeekFront() const;
  T PeekRear() const;

 private:
  /// <summary>
  /// Main array that stores elements of the queue.
  /// </summary>
  std::array<T, capacity> queue;
  /// <summary>
  /// Index of the front element of the queue.
  /// </summary>
  size_t front;
  /// <summary>
  /// Amount of active elements in the queue.
  /// </summary>
  size_t size;
};

/// <summary>
/// Constructor for the CircularQueue. It initializes the front index and size
/// to 0.
/// </summary>
template <typename T, size_t capacity>
CircularQueue<T, capacity>::CircularQueue() : front(0), size(0), queue() {}

/// <summary>
/// Checks if the queue is empty by checking the size value.
/// If size is 0, the queue is empty.
/// </summary>
/// <returns> true if empty, false if not.</returns>
template <typename T, size_t capacity>
bool CircularQueue<T, capacity>::IsEmpty() const noexcept {
  return size == 0;
}

/// <summary>
/// Checks if the queue is full by comparing the size value to the capacity.
/// </summary>
/// <returns> true if full, false if not</returns>
template <typename T, size_t capacity>
bool CircularQueue<T, capacity>::IsFull() const noexcept {
  return size == capacity;
}

/// <summary>
/// Gets the value from the front of the queue and moves the front index to the
/// next element. If the queue is empty (size == 0), it throws a runtime error.
/// </summary>
/// <returns> value of front element in queue.</returns>
template <typename T, size_t capacity>
T CircularQueue<T, capacity>::Dequeue() {
  if (IsEmpty()) {
    throw std::runtime_error(errors::kEmptyDeletion);
  }
  T result{queue.at(front)};
  front = (front + 1) % capacity;
  --size;
  return result;
}

/// <summary>
/// Adds a new value to the rear of the queue. If the queue is full, it throws
/// a runtime error. Size is increased by 1.
/// </summary>
/// <param name="value"> value to be inserted into queue.</param>
template <typename T, size_t capacity>
void CircularQueue<T, capacity>::Enqueue(T value) {
  if (IsFull()) {
    throw std::runtime_error(errors::kObjectFull);
  }
  size_t rear{(front + size) % capacity};
  queue.at(rear) = value;
  ++size;
}

/// <summary>
/// Gets the value from the front without moving the front index.
/// </summary>
/// <returns> value from the front of the queue.</returns>
template <typename T, size_t capacity>
T CircularQueue<T, capacity>::PeekFront() const {
  if (IsEmpty()) {
    throw std::runtime_error(errors::kPeekAtEmpty);
  }
  return queue.at(front);
}

/// <summary>
/// Gets value from the rear of the queue without changing the size of the
/// queue.
/// </summary>
/// <returns> value from the rear of the queue.</returns>
template <typename T, size_t capacity>
T CircularQueue<T, capacity>::PeekRear() const {
  if (IsEmpty()) {
    throw std::runtime_error(errors::kPeekAtEmpty);
  }
  size_t rear{(front + size - 1) % capacity};
  return queue.at(rear);
}

}  // namespace alglib

#endif  // ALGLIB_INCLUDE_CIRCULARQUEUE_H_