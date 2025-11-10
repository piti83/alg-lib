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
// File: singly_linked_list.h
//
// This file contains the implementation of the SinglyLinkedList class.
// Implementation is based on templates, so the class can be used with any
// type. SinglyLinkedList contains methods for inserting, deleting, and
// searching for elements. It has its own node structure that contains the
// data and a pointer to the next node. The class is implemented in the
// alglib namespace.
//*****************************************************************************

#ifndef ALGLIB_INCLUDE_SINGLYLINKEDLIST_H_
#define ALGLIB_INCLUDE_SINGLYLINKEDLIST_H_

#include <cstdlib>
#include <functional>
#include <vector>

#include "constants.h"

/// <summary>
/// Default namespace for the AlgLib library.
/// </summary>
namespace alglib {

/// <summary>
/// Template based singly linked list implementation. All nodes are
/// dynamically allocated.
/// </summary>
template <typename T>
class SinglyLinkedList {
 public:
  // Constructor for the singly linked list.
  SinglyLinkedList();

  // Methods for exploring the singly linked list.
  void Traverse(const std::function<void(T)> &visit_callback) noexcept;
  size_t Size() const noexcept;
  size_t Find(T value) const;

  // Method for converting the singly linked list to a vector.
  std::vector<T> GetAsVector() const noexcept;

  // Insertion methods
  void InsertAtBeginning(T value) noexcept;
  void InsertAtEnd(T value) noexcept;
  void InsertAtPosition(uint32_t pos, T value);

  // Deletion methods
  void DeleteAtBeggining();
  void DeleteAtEnd();
  void DeleteAtPosition(uint32_t pos);

  // Destructor for the singly linked list.
  ~SinglyLinkedList();

 private:
  /// <summary>
  /// Node structure for the singly linked list.
  /// It contains the data of type T and a pointer to the next node.
  /// </summary>
  struct Node {
    // Constructor for the Node structure.
    Node(T data);
    // Destructor for the Node structure.
    ~Node() = default;

    /// <summary>
    /// Pointer to the next node in the singly linked list.
    /// </summary>
    Node *next;
    /// <summary>
    /// Value of type T that is stored in the node.
    /// </summary>
    T data;
  };

  /// <summary>
  /// Head pointer to the first node in the singly linked list.
  /// </summary>
  Node *head_;
};

/// <summary>
/// Constructor for the Node structure.
/// </summary>
/// <param name="data">
/// Value of type T that will be stored in nodes.
/// </param>
template <typename T>
SinglyLinkedList<T>::Node::Node(T data) : next(nullptr), data(data) {}

/// <summary>
/// Constructor for the SinglyLinkedList structure. Initializes the head
/// pointer to nullptr.
/// </summary>
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head_(nullptr) {}

/// <summary>
/// Method that traverses the singly linked list and prints the data
/// of each node. Modifying the method to do something else with the
/// data is straight forward and can be done by changing the body of
/// the while loop.
/// </summary>
template <typename T>
void SinglyLinkedList<T>::Traverse(
    const std::function<void(T)> &visit_callback) noexcept {
  Node *tmp{head_};
  while (tmp) {
    visit_callback(tmp->data);
    tmp = tmp->next;
  }
}

/// <summary>
/// Method that calculates number of nodes in the singly linked list
/// by traversing the list.
/// </summary>
/// <returns>Number of nodes in structure as size_t.</returns>
template <typename T>
size_t SinglyLinkedList<T>::Size() const noexcept {
  Node *tmp{head_};
  size_t count{};
  while (tmp) {
    ++count;
    tmp = tmp->next;
  }
  return count;
}

/// <summary>
/// Method that searches for a value in the singly linked list.
/// </summary>
/// <param name="value">Value that the list will be searched for.</param>
/// <returns>Index of first occurance of given value (0 = first).</returns>
template <typename T>
size_t SinglyLinkedList<T>::Find(T value) const {
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
/// Method that converts the singly linked list to a vector.
/// It is used for teseing purposes.
/// Using it in production code is not recommended as it is
/// simply missing the point of the singly linked list.
/// </summary>
/// <returns>std::vector of nodes that are in structure.</returns>
template <typename T>
std::vector<T> SinglyLinkedList<T>::GetAsVector() const noexcept {
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
/// Method that inserts a new node at the beginning of the singly linked list
/// by creating a new node and pointing it to the current head.
/// </summary>
/// <param name="value">Value for the new node.</param>
template <typename T>
void SinglyLinkedList<T>::InsertAtBeginning(T value) noexcept {
  Node *new_node{new Node(value)};
  new_node->next = head_;
  head_ = new_node;
}

/// <summary>
/// Method that inserts a new node at the end of the singly linked list
/// by traversing the list and adding the new node to the last node.
/// </summary>
/// <param name="value">Value for the new node.</param>
template <typename T>
void SinglyLinkedList<T>::InsertAtEnd(T value) noexcept {
  Node *new_node{new Node(value)};

  if (head_ == nullptr) {
    head_ = new_node;
    return;
  }

  Node *tmp{head_};
  while (tmp->next) {
    tmp = tmp->next;
  }

  tmp->next = new_node;
}

/// <summary>
/// Method that inserts a new node at the given position in the singly linked
/// list by traversing the list to find the possition and splicing the new
/// node in.
/// </summary
/// <param name="pos">Position for the new node (0 - first).</param>
/// <param name="value">Value for the new node.</param>
template <typename T>
void SinglyLinkedList<T>::InsertAtPosition(uint32_t pos, T value) {
  if (pos < 0) {
    throw std::runtime_error(errors::kIndexOutOfRange);
  } else if (pos == 0) {
    Node *newNode{new Node(value)};
    newNode->next = head_;
    head_ = newNode;
  } else {
    Node *tmp{head_};
    uint32_t count{};
    while (count < pos - 1 && tmp != nullptr) {
      tmp = tmp->next;
      ++count;
    }
    if (tmp == nullptr) throw std::runtime_error(errors::kIndexOutOfRange);
    Node *newNode{new Node(value)};
    newNode->next = tmp->next;
    tmp->next = newNode;
  }
}

/// <summary>
/// Method for deleting the first node in the singly linked list
/// by pointing the head to the next node and deleting the first node.
/// </summary>
template <typename T>
void SinglyLinkedList<T>::DeleteAtBeggining() {
  if (head_ == nullptr) {
    throw std::runtime_error(errors::kEmptyDeletion);
  } else if (head_->next == nullptr) {
    delete head_;
    head_ = nullptr;
  } else {
    Node *tmp{head_};
    head_ = head_->next;
    delete tmp;
  }
}

/// <summary>
/// Method for deleting the last node in the singly linked list
/// by traversing the list to the last node and deleting it.
/// </summary>
template <typename T>
void SinglyLinkedList<T>::DeleteAtEnd() {
  if (head_ == nullptr) {
    throw std::runtime_error(errors::kEmptyDeletion);
  } else if (head_->next == nullptr) {
    delete head_;
    head_ = nullptr;
  } else {
    Node *tmp{head_};
    while (tmp->next->next != nullptr) tmp = tmp->next;
    delete tmp->next;
    tmp->next = nullptr;
  }
}

/// <summary>
/// Method for deleting a node at a given position in the singly linked list
/// by traversing the list to the given position and splicing the node out.
/// </summary>
/// <param name="pos">Position of the node to delete (0 - first).</param>
template <typename T>
void SinglyLinkedList<T>::DeleteAtPosition(uint32_t pos) {
  if (head_ == nullptr) {
    throw std::runtime_error(errors::kEmptyDeletion);
  } else if (pos == 0) {
    Node *tmp{head_};
    head_ = head_->next;
    delete tmp;
  } else {
    Node *tmp{head_};
    uint32_t count{};
    while (count < pos - 1 && tmp != nullptr) {
      tmp = tmp->next;
      ++count;
    }
    if (tmp == nullptr || tmp->next == nullptr)
      throw std::runtime_error(errors::kIndexOutOfRange);
    Node *toDelete{tmp->next};
    tmp->next = toDelete->next;
    delete toDelete;
  }
}

/// <summary>
/// Method for deleting the singly linked list.
/// It traverses the list and deletes each node
/// as they are dynamically allocated.
/// </summary>
template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
  Node *tmp{head_};
  while (tmp) {
    Node *next{tmp->next};
    delete tmp;
    tmp = next;
  }
}

}  // namespace alglib

#endif  // ALGLIB_INCLUDE_SINGLYLINKEDLIST_H_