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
// File: sll_queue.h
//
// This file contains implementation of SLLQueue class. It uses singly linked
// list as a base for queue data structure. All nodes are allocated on the
//*****************************************************************************

#ifndef ALGLIB_INCLUDE_SLLQUEUE_H_
#define ALGLIB_INCLUDE_SLLQUEUE_H_

#include <stdexcept>

#include "constants.h"

/// <summary>
/// Default namespace for the library.
/// </summary>
namespace alglib {

/// <summary>
/// SLLQueue class is a queue data structure implemented using singly linked
/// list. It allocates nodes on the heap. Queue can grow dynamically. There is
/// no limit to the amount of elements besides the memory available.
/// </summary>
/// <typeparam name="T"> type that will be stored in queue.</typeparam>
template <typename T>
class SLLQueue {
 public:
  // Constructor for the SLLQueue.
  SLLQueue();

  // Manipulation methods for the queue.
  bool IsEmpty() const noexcept;
  T Dequeue();
  void Enqueue(T value) noexcept;

  // Methods for peeking at the front and rear of the queue.
  T PeekFront() const;
  T PeekRear() const;

  // Destructor for the SLLQueue.
  ~SLLQueue();

 private:
  /// <summary>
  /// Node structure for the singly linked list queue.
  /// Every element of queue is stored in the node.
  /// </summary>
  struct Node {
    T val;
    Node *next;
    Node(T value);
  };
  /// <summary>
  /// Pointer to the front of the queue.
  /// </summary>
  Node *front;
  /// <summary>
  /// Pointer to the rear of the queue.
  /// </summary>
  Node *rear;
};

/// <summary>
/// Constructor for the Node structure. Initializes the value to a given value
/// and next pointer to nullptr.
/// </summary>
/// <param name="value"> value to be set in the node.</param>
template <typename T>
SLLQueue<T>::Node::Node(T value) : val(value), next(nullptr) {}

/// <summary>
/// SLLQueue constructor initializes the front and rear pointers to nullptr.
/// </summary>
template <typename T>
SLLQueue<T>::SLLQueue() : front(nullptr), rear(nullptr) {}

/// <summary>
/// Checks if the queue is empty by checking if the front pointer is nullptr.
/// </summary>
/// <returns> true if empty, false if not.</returns>
template <typename T>
bool SLLQueue<T>::IsEmpty() const noexcept {
  return front == nullptr;
}

/// <summary>
/// Pops the value from the front of the queue and returns it. The front pointer
/// is then set to the next node in the queue. If the front pointer is nullptr,
/// the rear pointer is also set to nullptr. It deletes the node from the front,
/// so it cannot be accesed after the operation. if the queue is empty, it
/// throws a runtime error.
/// </summary>
/// <returns></returns>
template <typename T>
T SLLQueue<T>::Dequeue() {
  if (IsEmpty()) {
    throw std::runtime_error(errors::kEmptyDeletion);
  }
  T result{front->val};
  Node *tmp{front};
  front = front->next;
  if (front == nullptr) {
    rear = nullptr;
  }
  delete tmp;
  return result;
}

/// <summary>
/// Adds a new node to the rear of the queue. If the queue is empty, the front
/// and rear pointers are set to the new node. Otherwise, the new node is set as
/// the next node of the rear pointer and the rear pointer is set to the new node.
/// </summary>
/// <param name="value"> value to be inserted into queue.</param>
template <typename T>
void SLLQueue<T>::Enqueue(T value) noexcept {
  Node *new_node{new Node(value)};
  if (IsEmpty()) {
    front = rear = new_node;
  }
  rear->next = new_node;
  rear = rear->next;
}

/// <summary>
/// Gets the value from the front of the queue without removing it. If the queue
/// is empty, it throws a runtime error.
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns></returns>
template <typename T>
T SLLQueue<T>::PeekFront() const {
  if (IsEmpty()) {
    throw std::runtime_error(errors::kObjectEmpty);
  }
  return front->val;
}

/// <summary>
/// Gets the value from the rear of the queue without removing it. If the queue
/// is empty, it throws a runtime error.
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns></returns>
template <typename T>
T SLLQueue<T>::PeekRear() const {
  if (IsEmpty()) {
    throw std::runtime_error(errors::kObjectEmpty);
  }
  return rear->val;
}

/// <summary>
/// Deletes all nodes from the queue. It starts from the front and deletes all
/// nodes until the rear. It then deletes the rear node.
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T>
SLLQueue<T>::~SLLQueue() {
  Node *tmp{front};
  while (tmp != rear) {
    Node *next{tmp->next};
    delete tmp;
    tmp = next;
  }
  delete rear;
}

}  // namespace alglib

#endif  // ALGLIB_INCLUDE_SLLQUEUE_H_
