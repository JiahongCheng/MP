#include "cord.hpp"

#include <stdexcept>

#include "cord_utilities.hpp"

#include <stack>


Cord::Cord(std::string_view sv) {
  if (sv.empty()) {
    throw std::invalid_argument("empty string_view");
  }
  length_ = static_cast<unsigned int>(sv.size());
  data_ = new char[length_ + 1];
  for (unsigned int i = 0; i < length_; i++) {
    data_[i] = sv[i];
  }
  data_[length_] = '\0';
}

Cord::~Cord() {
  delete[] data_;
  data_ = nullptr;
}

SharedPointer<char> Cord::ToString() const {
  std::stack<const Cord*> cord_stack;
  cord_stack.push(this);

  char* output_string = new char[length_ + 1];
  unsigned int pos = 0;

  while (!cord_stack.empty()) {
    const Cord* curr = cord_stack.top();
    cord_stack.pop();

    if (curr->data_ != nullptr) {
      std::copy(curr->data_, curr->data_ + curr->length_, output_string + pos);
      pos += curr->length_;
    } else {
      if (curr->right_.Get() != nullptr) {
        cord_stack.push(curr->right_.Get());
      }
      if (curr->left_.Get() != nullptr) {
        cord_stack.push(curr->left_.Get());
      }
    }
  }

  output_string[length_] = '\0';
  return SharedPointer<char>{output_string, kSharedPointerType::kArray};
}




