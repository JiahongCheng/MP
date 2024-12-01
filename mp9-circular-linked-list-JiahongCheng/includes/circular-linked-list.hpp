#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void Reverse();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  head_ = nullptr;
  tail_ = nullptr;
  node_order_ = source.node_order_;

  if (source.head_ == nullptr) return;

  head_ = new Node<T>(source.head_->data);
  Node<T>* tmp = head_;
  Node<T>* source_tmp = source.head_->next;

  while (source_tmp != source.head_) {
    tmp->next = new Node<T>(source_tmp->data);
    tmp = tmp->next;
    source_tmp = source_tmp->next;
  }

  tail_ = tmp;
  tail_->next = head_;
}


template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (head_ == nullptr) {
    head_ = new Node<T>(data);
    head_->next = head_;
    tail_ = head_;
    return;
  }
  if (node_order_ == Order::kASC) {// insert asc
    if (data < head_->data) {
      auto* tmp = new Node<T>(data);
      tail_->next = tmp;
      tmp->next = head_;
      head_ = tmp;
      return;
    }
    Node<T>* tmp = head_;
    while (data >= tmp->next->data) { if (tmp == tail_) break; tmp = tmp->next; }
    auto* asc = new Node<T>(data);
    asc->next = tmp->next;
    tmp->next = asc;
    if (tmp == tail_) tail_ = asc;
    /////////////////////////////////
  } else if (node_order_ == Order::kDESC) {// insert desc
    if (data > head_->data) {
      auto* tmp = new Node<T>(data);
      tail_->next = tmp;
      tmp->next = head_;
      head_ = tmp;
      return;
    }
    Node<T>* tmp = head_;
    while (data <= tmp->next->data) {
      if (tmp == tail_) break;
      tmp = tmp->next;
    }
    auto* desc = new Node<T>(data);
    desc->next = tmp->next;
    tmp->next = desc;
    if (tmp == tail_) tail_ = desc;
  }
}
template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(
    const CircularLinkedList<T>& source) {
  if (&source == this) return *this;
  // Clean up existing nodes
  while (head_ != tail_) {
    Node<T>* tmp = head_->next;
    delete head_;
    head_ = nullptr;
    head_ = tmp;
  }
  delete tail_;
  if (source.head_ == nullptr) return *this;
  if (source.head_ == source.tail_) {
    head_ = tail_ = new Node<T>(source.head_->data);
    head_->next = head_;
    return *this;
  }
  head_ = new Node<T>(source.head_->data);
  head_->next = new Node<T>(source.head_->next->data);
  Node<T>* tmp = head_->next;
  Node<T>* source_tmp = source.head_->next;
  while (source_tmp != source.head_) {
    if (source_tmp == source.tail_) {
      tail_ = tmp;
      tail_->next = head_;
      break;
    }
    tmp->next = new Node<T>(source_tmp->next->data);
    tmp = tmp->next;
    source_tmp = source_tmp->next;
  }
  node_order_ = source.node_order_;
  return *this;
}

template <typename T>
void CircularLinkedList<T>::Reverse() {
  Node<T>* tail = tail_;
  if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  } else {
    node_order_ = Order::kASC;
  }
  if (head_ == nullptr || head_ == tail_) {
    return;
  }
  while (head_ != tail) {
    Node<T>* current = head_;
    while (current->next != tail) current = current->next;
    tail->next = current;
    tail = current;
  }
  head_->next = tail_; Node<T>* tmp = head_; head_ = tail_; tail_ = tmp;
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  if (head_ == nullptr) {
    return;
  }
  if (head_ == tail_) {
    delete head_;
    return;
  }
  while(head_ != tail_) {
    Node<T>* tmp = head_->next;
    delete head_;
    head_ = nullptr;
    head_ = tmp;
  }
  delete tail_;
  head_ = tail_ = nullptr;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

#endif



