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
// File: doubly_linked_list.h
//
// This file contains the implementation of a Doubly Linked List.
// The Doubly Linked List is a data structure that consists of a sequence of
// elements, each containing a link to its previous element and a link to its
// next element. The Doubly Linked List allows for efficient insertion and
// deletion of elements at the beginning, end, and at any position in the list.
// The Doubly Linked List also allows for efficient traversal of the list and
// searching for elements in the list.
//*****************************************************************************

#ifndef ALGLIB_INCLUDE_DOUBLYLINKEDLIST_H_
#define ALGLIB_INCLUDE_DOUBLYLINKEDLIST_H_

#include <cstdlib>
#include <functional>

#include "constants.h"

/// <summary>
/// Default namespace for the AlgLib library.
/// </summary>
namespace alglib {

/// <summary>
/// Template based doubly linked list implementation. All nodes are
/// dynamically allocated.
/// </summary>
template <typename T>
class DoublyLinkedList {
 public:
  // Constructor for the doubly linked list.
  DoublyLinkedList();

  // Methods for exploring the doubly linked list.
  void Traverse(const std::function<void(T)> &visit_callback) noexcept;
  size_t Size() const noexcept;
  size_t Find(const T value) const;

  // Method for converting the doubly linked list to a vector.
  std::vector<T> GetAsVector() const noexcept;

  // Methods for inserting elements into the doubly linked list.
  void InsertAtBeginning(const T data) noexcept;
  void InsertAtEnd(const T data) noexcept;
  void InsertAtPosition(const uint32_t pos, const T data);

  // Methods for deleting elements from the doubly linked list.
  void DeleteAtBeginning();
  void DeleteAtEnd();
  void DeleteAtPosition(uint32_t pos);

  // Method for checking if the doubly linked list is empty.
  bool IsEmpty() const noexcept;

  // Destructor for the doubly linked list.
  ~DoublyLinkedList();

 private:
  /// <summary>
  /// Node structure for the doubly linked list.
  /// Contains a pointer to the next node, a pointer to the previous node,
  /// and the data of the node.
  /// </summary>
  struct Node {
    Node(T data);
    ~Node() = default;
    Node *next;
    Node *previous;
    T data;
  };

  // Head and tail pointers for the doubly linked list.
  Node *head_;
  Node *tail_;
};

/// <summary>
/// Constructor for the Node structure. It initializes the data of the node
/// with the given data and sets the next and previous pointers to nullptr.
/// </summary>
/// <param name="data"> Value that will be set as node value.</param>
template <typename T>
DoublyLinkedList<T>::Node::Node(const T data)
    : next(nullptr), previous(nullptr), data(data) {}

/// <summary>
/// Constructor for the doubly linked list. It initializes the head and tail
/// pointers to nullptr.
/// </summary>
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head_(nullptr), tail_(nullptr) {}

/// <summary>
/// Method for traversing the doubly linked list. It starts at the head of the
/// list and moves to the next node until the end of the list is reached.
/// </summary>
template <typename T>
void DoublyLinkedList<T>::Traverse(
    const std::function<void(T)> &visit_callback) noexcept {
  Node *tmp{head_};
  while (tmp) {
    visit_callback(tmp->data);
    tmp = tmp->next;
  }
}

/// <summary>
/// Method for calculating the number of elements in the doubly linked list.
/// It starts at the head of the list and moves to the next node until the end
/// of the list is reached.
/// </summary>
/// <returns> Number of nodes in list.</returns>
template <typename T>
size_t DoublyLinkedList<T>::Size() const noexcept {
  Node *tmp{head_};
  size_t count{};
  while (tmp) {
    ++count;
    tmp = tmp->next;
  }
  return count;
}

/// <summary>
/// Method for finding a value in the doubly linked list. It starts at the head
/// of the list and moves to the next node until the end of the list is reached.
/// </summary>
/// <param name="value"> Value that list is searched for.</param>
/// <returns> Index of element if found. (0 - first).</returns>
template <typename T>
size_t DoublyLinkedList<T>::Find(const T value) const {
  Node *tmp{head_};
  size_t count{};
  while (tmp && tmp->data != value) {
    ++count;
    tmp = tmp->next;
  }
  if (tmp == nullptr) {
    throw std::runtime_error(errors::kItemNotFound);
  } else {
    return count;
  }
}

/// <summary>
/// Method for converting the doubly linked list to a vector. It starts at the
/// head of the list and moves to the next node until the end of the list is
/// reached.
/// It is used for testing purposes.
/// Using it in production code is not recommended as it is simply missing the
/// point of the doubly linked list.
/// </summary>
/// <returns>Doubly linked list as vector.</returns>
template <typename T>
std::vector<T> DoublyLinkedList<T>::GetAsVector() const noexcept {
  std::vector<T> vec{};
  vec.reserve(Size());
  Node *tmp{head_};
  while (tmp) {
    vec.emplace_back(tmp->data);
    tmp = tmp->next;
  }
  return vec;
}

/// <summary>
/// Method for inserting a new node at the beginning of the doubly linked list.
/// It creates a new node with the given data and sets the next pointer of the
/// new node to the head of the list. If the list is not empty, it sets the
/// previous pointer of the head node to the new node.
/// </summary>
/// <param name="data">Value that will be inserted.</param>
template <typename T>
void DoublyLinkedList<T>::InsertAtBeginning(const T data) noexcept {
  Node *new_node{new Node(data)};
  if (IsEmpty()) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    new_node->next = head_;
    head_->previous = new_node;
    head_ = new_node;
  }
}

/// <summary>
/// Method for inserting a new node at the end of the doubly linked list.
/// It creates a new node with the given data and sets the next pointer of the
/// last node in the list to the new node. If the list is empty, it sets the
/// head pointer to the new node.
/// </summary>
/// <param name="data">Value that will be inserted.</param>
template <typename T>
void DoublyLinkedList<T>::InsertAtEnd(const T data) noexcept {
  Node *new_node{new Node(data)};
  if (IsEmpty()) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    tail_->next = new_node;
    new_node->previous = tail_;
    tail_ = new_node;
  }
}

/// <summary>
/// Method for inserting a new node at the given position in the doubly linked
/// list. If the position is 0, insert at the beginning. If the position is
/// equal to the size, insert at the end. Otherwise, link it into the middle. If
/// pos is out of range, an exception is thrown.
/// </summary>
/// <param name="pos">Position to insert the data (0-based index).</param>
/// <param name="data">Value that will be inserted.</param>
template <typename T>
void DoublyLinkedList<T>::InsertAtPosition(const uint32_t pos, const T data) {
  const size_t current_size{Size()};
  if (pos > current_size) {
    throw std::runtime_error(errors::kIndexOutOfRange);
  }
  if (pos == 0) {
    InsertAtBeginning(data);
    return;
  }
  if (pos == current_size) {
    InsertAtEnd(data);
    return;
  }
  Node *new_node = new Node(data);
  Node *prev_node = head_;
  for (uint32_t i{}; i < pos - 1; ++i) {
    prev_node = prev_node->next;
  }
  Node *next_node{prev_node->next};
  new_node->next = next_node;
  new_node->previous = prev_node;
  prev_node->next = new_node;
  if (next_node) {
    next_node->previous = new_node;
  }
}

/// <summary>
/// Method for deleting the first node in the doubly linked list. If the list
/// is empty, an exception is thrown. If the list has only one node, the node
/// is deleted and the head pointer is set to nullptr.
/// </summary>
template <typename T>
void DoublyLinkedList<T>::DeleteAtBeginning() {
  if (IsEmpty()) {
    throw std::runtime_error(errors::kEmptyDeletion);
  }
  if (head_ == tail_) {
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    Node *tmp{head_};
    head_ = head_->next;
    head_->previous = nullptr;
    delete tmp;
  }
}

/// <summary>
/// Method for deleting the last node in the doubly linked list. If the list is
/// empty, an exception is thrown. If the list has only one node, the node is
/// deleted and the head pointer is set to nullptr
/// </summary>
template <typename T>
void DoublyLinkedList<T>::DeleteAtEnd() {
  if (IsEmpty()) {
    throw std::runtime_error(errors::kEmptyDeletion);
  }
  if (head_ == tail_) {
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    Node *tmp{tail_};
    tail_ = tail_->previous;
    tail_->next = nullptr;
    delete tmp;
  }
}

/// <summary>
/// Deletes the node at the given position in the doubly linked list. If the
/// list is empty, an exception is thrown. If the position is out of range, an
/// exception is thrown.
/// </summary>
/// <param name="pos">Position of node to delete (0 - first).</param>
template <typename T>
void DoublyLinkedList<T>::DeleteAtPosition(uint32_t pos) {
  if (IsEmpty()) {
    throw std::runtime_error(errors::kEmptyDeletion);
  }
  const size_t current_size{Size()};
  if (pos >= current_size) {
    throw std::runtime_error(errors::kIndexOutOfRange);
  }
  if (pos == 0) {
    DeleteAtBeginning();
    return;
  }
  if (pos == current_size - 1) {
    DeleteAtEnd();
    return;
  }
  Node *curr{head_};
  for (uint32_t i{}; i < pos; ++i) {
    curr = curr->next;
  }
  Node *prev_node{curr->previous};
  Node *next_node{curr->next};
  if (prev_node) {
    prev_node->next = next_node;
  }
  if (next_node) {
    next_node->previous = next_node;
  }
  delete curr;
}

/// <summary>
/// Destructor for the doubly linked list. It traverses the list and deletes
/// each node in the list. It also deletes the tail pointer.
/// </summary>
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  Node *tmp{head_};
  while (tmp) {
    Node *next{tmp->next};
    delete tmp;
    tmp = next;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

/// <summary>
/// Method for checking if the doubly linked list is empty
/// </summary>
/// <returns>True if the list is empty, false otherwise.</returns>
template <typename T>
bool DoublyLinkedList<T>::IsEmpty() const noexcept {
  return (head_ == nullptr);
}

}  // namespace alglib

#endif  // ALGLIB_INCLUDE_DOUBLYLINKEDLIST_H_