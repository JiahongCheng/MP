// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("True == True", "") { REQUIRE(true == true); }

/////////////////////////////////////////////////////////////////////////////////////////////







// Here is all of the class hpp file and the cc file, do not modify them:

// //////////////////////////////////////////////////

// //shared_pointer.hpp

// #ifndef SHARED_POINTER_HPP
// #define SHARED_POINTER_HPP

// #include <iostream>

// enum class kSharedPointerType { kArray, kObject };

// template <typename T>
// class SharedPointer {
// public:
//   SharedPointer(T* address,
//                 kSharedPointerType type = kSharedPointerType::kObject);

//   ~SharedPointer();

//   SharedPointer(const SharedPointer<T>& source);
  
//   SharedPointer<T>& operator=(const SharedPointer<T>& source);

//   // Provided, do not modify!
//   SharedPointer() = default;
//   T& operator*() { return *holder_; }
//   T* operator->() { return holder_; }
//   const T* operator->() const { return holder_; }
//   T* Get() { return holder_; }
//   const T* Get() const { return holder_; }
//   unsigned int UseCount() const {
//     return (ref_count_ != nullptr) ? *ref_count_ : 0;
//   }

// private:
//   T* holder_ = nullptr;
//   kSharedPointerType type_ = kSharedPointerType::kObject;
//   unsigned int* ref_count_ = nullptr;
// };

// // non-member helper function declarations

// // non-member helper function definitions

// // member function definitions


// template <typename T>
// SharedPointer<T>::SharedPointer(T* address, kSharedPointerType type)
//     : holder_(address), type_(type), ref_count_(new unsigned int(1)){
// }

// template <typename T>
// SharedPointer<T>::~SharedPointer() {
//   if (ref_count_ == nullptr) {
//     return;
//   }
//   if ((*ref_count_)-- == 0) {
//     if (type_ == kSharedPointerType::kArray) {
//       delete[] holder_;
//     } else {
//       delete holder_;
//     }
//     delete ref_count_;
//     ref_count_ = nullptr;
//     holder_ = nullptr;
//   }
// }

// template <typename T>
// SharedPointer<T>::SharedPointer(const SharedPointer<T>& source)
//     : holder_(source.holder_), type_(source.type_), ref_count_(source.ref_count_) {
//   if (ref_count_ == nullptr) return;
//   ++(*ref_count_);
// }

// template <typename T>
// SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<T>& source) {
//   if (this == &source) {
//     return *this;
//   }
//   if (ref_count_ != nullptr && *ref_count_ > 0) {///
//     (*ref_count_)--;
//     if ((*ref_count_) == 0) {
//     if (type_ == kSharedPointerType::kArray) {
//       delete[] holder_;
//     } else {
//       delete holder_;
//     }
//       delete ref_count_;
//       ref_count_ = nullptr;
//       holder_ = nullptr;
//     }
//   }
//   holder_ = source.holder_;
//   type_ = source.type_;
//   ref_count_ = source.ref_count_;
//   if (ref_count_ != nullptr) {
//     ++(*ref_count_);
//   }
//   return *this;
// }


// #endif

// //////////////////////////////////////////////////

// //cord.hpp

// #ifndef CORD_HPP
// #define CORD_HPP

// #include <string_view>

// #include "shared_pointer.hpp"

// class Cord {
// public:
//   Cord(std::string_view sv);
//   ~Cord();
//   SharedPointer<char> ToString() const;

//   // Provided, do not modify!
//   Cord() = default;
//   Cord(const Cord& rhs) = delete;
//   Cord& operator=(const Cord& rhs) = delete;
//   unsigned int Length() const { return length_; }
//   const SharedPointer<Cord> Left() const { return left_; }
//   const SharedPointer<Cord> Right() const { return right_; }
//   const std::string_view Data() const { return data_; }

// private:
//   // data members
//   SharedPointer<Cord> left_;
//   SharedPointer<Cord> right_;
//   char* data_ = nullptr;
//   unsigned int length_ = 0;
//   // friend functions
//   friend SharedPointer<Cord> ConcatCords(const SharedPointer<Cord>& left_cord,
//                                          const SharedPointer<Cord>& right_cord);
// };

// #endif

// //////////////////////////////////////////////////

// //cord.cc
// #include "cord.hpp"

// #include <stdexcept>

// #include "cord_utilities.hpp"

// #include <stack>


// Cord::Cord(std::string_view sv) {
//   if (sv.empty()) {
//     throw std::invalid_argument("empty string_view");
//   }
//   length_ = static_cast<unsigned int>(sv.size());
//   data_ = new char[length_ + 1];
//   for (unsigned int i = 0; i < length_; i++) {
//     data_[i] = sv[i];
//   }
//   data_[length_] = '\0';
// }

// Cord::~Cord() {
//   delete[] data_;
//   data_ = nullptr;
// }

// SharedPointer<char> Cord::ToString() const {
//   std::stack<const Cord*> cord_stack;
//   cord_stack.push(this);

//   char* output_string = new char[length_ + 1];
//   unsigned int pos = 0;

//   while (!cord_stack.empty()) {
//     const Cord* curr = cord_stack.top();
//     cord_stack.pop();

//     if (curr->data_ != nullptr) {
//       std::copy(curr->data_, curr->data_ + curr->length_, output_string + pos);
//       pos += curr->length_;
//     } else {
//       if (curr->right_.Get() != nullptr) {
//         cord_stack.push(curr->right_.Get());
//       }
//       if (curr->left_.Get() != nullptr) {
//         cord_stack.push(curr->left_.Get());
//       }
//     }
//   }

//   output_string[length_] = '\0';
//   return SharedPointer<char>{output_string, kSharedPointerType::kArray};
// }



// ///////////////////////////////////////////////////////////////////////

// //cord_utilities.hpp

// #ifndef CORD_UTILITIES_HPP
// #define CORD_UTILITIES_HPP

// #include "cord.hpp"
// #include "shared_pointer.hpp"

// SharedPointer<Cord> ConcatCords(const SharedPointer<Cord>& left_cord,
//                                  const SharedPointer<Cord>& right_cord);

// SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord,
//                               unsigned int lower_idx,
//                               unsigned int upper_idx);

// #endif
// ///////////////////////////////////////////////////////////////////////

// //cord_utilities.cc

// #include "cord_utilities.hpp"


// SharedPointer<Cord> ConcatCords(const SharedPointer<Cord>& left_cord, const SharedPointer<Cord>& right_cord) {
//   if (left_cord.Get() == nullptr || right_cord.Get() == nullptr) {
//     throw std::invalid_argument("Invalid");
//   }
//     Cord* concat_cord = new Cord();
//     concat_cord->left_ = left_cord;
//     concat_cord->right_ = right_cord;
//     concat_cord->length_ = left_cord->Length() + right_cord->Length();
//     concat_cord->data_ = nullptr;
//     return SharedPointer<Cord>{concat_cord};
// }

// SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord, unsigned int lower_idx, unsigned int upper_idx) {
//     if (curr_cord.Get() == nullptr || lower_idx >= upper_idx || upper_idx > curr_cord->Length()) {
//         throw std::out_of_range("Invalid");
//     }
//     std::string_view result_sv;
//     std::stack<std::pair<SharedPointer<Cord>, unsigned int>> cord_stack;
//     cord_stack.push({curr_cord, 0});

//     while (!cord_stack.empty()) {
//         auto [cord, idx] = cord_stack.top();
//         cord_stack.pop();
//         unsigned int curr_length = cord->Length();

//         if (cord->Left().Get() != nullptr && cord->Right().Get() != nullptr) {
//             if (idx + curr_length > lower_idx) {
//                 cord_stack.push({cord->Right(), idx + cord->Left()->Length()});
//                 cord_stack.push({cord->Left(), idx});
//             }
//         } else {
//             unsigned int start = (idx > lower_idx) ? idx : lower_idx;
//             unsigned int end = (idx + curr_length < upper_idx) ? idx + curr_length : upper_idx;

//             if (start < end) {
//                 result_sv = std::string_view(cord->Data().data() + start - idx, end - start);
//             }
//         }
//     }

//     if (!result_sv.empty()) {
//         return SharedPointer<Cord>{new Cord(result_sv)};
//     }
//   return nullptr;
// }

// ///////////////////////////////////////////////////////////////////////

// Only the following header files are allowed to be #included in your solution files "shared_pointer.hpp" "cord.hpp" "cord_utilities.hpp" <iostream> <stack> <stdexcept> <string_view>

// some additional information:
// Some cords are leaves, and others are not. Here's our first rule:

// Only leaf nodes can have data_
// And by definition of leaf nodes in trees, they should not have any child nodes:

// Leaf nodes' left_ and right_ are always nullptr
// Leaf nodes in this tree data structure will generally contain data, but will not point to other cords. A leaf node will typically have data; however, a default constructed Cord object will not.

// Non-leaf nodes' left_ and right_ pointers will always non-null; data_ will always point to nullptr
// Non-leaf nodes' left_ and right_ pointers will always non-null: non-leaf cords will always be build using a concatenation operation that will ensure that any non-leaf cord's left_ and right_ will always point to a valid cord object. This will be an invariant for our type.

// Moreover, non-leaf nodes will not contain data. This is expressed by pointing data_ to nullptr.


// write and rewrite the function SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord, unsigned int lower_idx, unsigned int upper_idx);
// Function Description: Substrings the cord pointed to by curr_cord with the given indices (lower_idx is inclusive and upper_idx is exclusive). For more information, kindly see above. Throws an exception if lower_idx or upper_idx is outside the bounds of the cord pointed to by curr_cord, or if lower_idx >= upper_idx.

// SubString operation
// SubString is called with a lower index (inclusive) and an upper index (exclusive). This substring operation is performed in a way that utilizes the existing cord structure as much as possible.

// See it for yourself. Say we have this cord structure:

// And if we call SubString with lower_idx=2 and upper_idx=8, we will be capturing the string "llowor". Because the existing cords can fully represent this substring, we create a new cord (blue) that wires to the leaf cords that represent "llo" and "wor" as shown in the diagram:

// Now, if we call SubString with lower_idx=2 and upper_idx=7, the first part can be fully reused (i.e. "llo"), but the second part "wo" is not an existing cord. Therefore, we would have to create a new cord with this string and then wire that as the blue Cord 's right node, as shown in the diagram:

// And in the worst case, if we call SubString with lower_idx=3 and upper_idx=6 to capture the string "low", there's no way to represent this string with the existing cords. Therefore, we take "lo" from the left half of the original cord, and "w" from the right part, and then create new cords as the following:

// Similarly, if you are taking a SubString with lower_idx=3 and upper_idx=5 to capture the string "lo", there's also no existing cord that represents this string. However, since we are taking a substring from a single leaf node, there's no left or right. Therefore, the resultant Cord would be a cord that is a leaf node, containing "lo" as its data.

// In a more complicated scenario, we might take a SubString with lower_idx=3 and upper_idx=9 to capture the string "loworl". In this case, as you can see, we can reuse the node "wor", but "lo" and "l" need to be created as new cords. In this case, as long as you are maximizing the number of nodes you are reusing, the resultant Cord can be wired in any way. Look at the example below—the new cords in pink (labeled A) and blue (labeled B) are acceptable.

// Notice from these examples that when you are maximizing the number of nodes that you are reusing (as you are supposed to), the maximum number of new leaf cords you are creating cannot exceed 2.

// Also note that the same rules apply to multi-level cords. You only allocate new memory when you have to. Here's an example of a SubString taken on a multi-level cord, with lower_idx=2 and upper_idx=13:


















// SharedPointer(T* address, kSharedPointerType type = kSharedPointerType::kObject): (The first parameter the address of a free store object typed T that the SharedPointer object being constructed will take ownership of. From construction forward, the SharedPointer objects sharing this resource are responsible for its deallocation. The value passed to the address parameter is used to initialize the data member holder_.The second parameter kSharedPointerType is passed kSharedPointerType::kArray only if the free store object whose address was passed to this constructor's first parameter is an array. Otherwise, the default value of kSharedPointerType::kObject will be used. The value stored in type is used to initialize the data member type_.Finally, ref_count_ is initialized with the address of a newly allocated unsigned int object on the free store with the starting value of 1. The object pointed to by ref_count_ will serve as the reference count to holder_.)

// ~SharedPointer(): (The destructor will always decrement *ref_count_ (the object pointed to by ref_count_) by 1. When *ref_count_ become 0, the last object engaged in shared ownership is being destructed. In this case, you will deallocate memory for the free store objects pointed to by holder_ and ref_count_. Use type_ to ensure the proper delete operator is invoked on the address stored in holder_.)

// SharedPointer(const SharedPointer<T>& source): (The copy construction of a SharedPointer<T> object increases the number of SharedPointer<T> objects engaged in the shared ownership of source.holder_. Therefore, the copy policy for this type will be a shallow (member-wise) copy of source's data members, since we want the objects pointed to by holder_ and ref_count_ to be shared. Don't forget to increment *ref_count_ by 1 to record the increased number of objects engaged in shared ownership of holder_.)

// SharedPointer<T>& operator=(const SharedPointer<T>& source): (The implementation of the copy assignment operator follows that of the copy constructor, albeit with two additional considerations: (1) you must check for self-assignment and do nothing (return *this) if it occurs; (2) since the object on the left-hand side of the = operator is existing, it can be engaged in shared ownership with another object. To remove this object from those responsibilities, you should decrement *ref_count_ (the object pointed to by ref_count_) by 1. Should *ref_count_ become 0, this object is the last object engaged in shared ownership; therefore, you will deallocate memory for the free store objects pointed to by holder_ and ref_count_. Use type_ to ensure the proper delete operator is invoked on the address stored in holder_. After considering cases (1) and (2) from above, you will perform a shallow (member-wise) copy of source's data members, Once you've done this, don't forget to increment *ref_count_ by 1 to record the increased number of objects engaged in shared ownership of holder_.)






// SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord, unsigned int lower_idx, unsigned int upper_idx) {
//     if (curr_cord.Get() == nullptr || lower_idx >= upper_idx || upper_idx > curr_cord->Length()) {
//         throw std::out_of_range(" ");
//     }
//     std::string_view result_sv;
//     std::stack<std::pair<SharedPointer<Cord>, unsigned int>> cord_stack;
//     cord_stack.push({curr_cord, 0});

//     while (!cord_stack.empty()) {
//         auto [cord, idx] = cord_stack.top();
//         cord_stack.pop();
//         unsigned int curr_length = cord->Length();

//         if (cord->Left().Get() != nullptr && cord->Right().Get() != nullptr) {
//             if (idx + curr_length > lower_idx) {
//                 cord_stack.push({cord->Right(), idx + cord->Left()->Length()});
//                 cord_stack.push({cord->Left(), idx});
//             }
//         } else {
//             unsigned int start = (idx > lower_idx) ? idx : lower_idx;
//             unsigned int end = (idx + curr_length < upper_idx) ? idx + curr_length : upper_idx;

//             if (start < end) {
//                 result_sv = std::string_view(cord->Data().data() + start - idx, end - start);
//             }
//         }
//     }

//     if (!result_sv.empty()) {
//         return SharedPointer<Cord>{new Cord(result_sv)};
//     }
//   return nullptr;
// }