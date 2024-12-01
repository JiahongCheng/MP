#include "cord_utilities.hpp"

#include <stack>
#include <stdexcept>
#include <string_view>

SharedPointer<Cord> ConcatCords(const SharedPointer<Cord>& left_cord, const SharedPointer<Cord>& right_cord) {
  if (left_cord.Get() == nullptr || right_cord.Get() == nullptr) {
    throw std::invalid_argument("Invalid");
  }
    Cord* concat_cord = new Cord();
    concat_cord->left_ = left_cord;
    concat_cord->right_ = right_cord;
    concat_cord->length_ = left_cord->Length() + right_cord->Length();
    concat_cord->data_ = nullptr;
    return SharedPointer<Cord>{concat_cord};
}

SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord, unsigned int lower_idx, unsigned int upper_idx) {
    if (curr_cord.Get() == nullptr || lower_idx >= upper_idx || upper_idx > curr_cord->Length()) {
        throw std::out_of_range(" ");
    }
    SharedPointer<Cord> new_left = nullptr;
    SharedPointer<Cord> new_right = nullptr;
    std::stack<std::pair<SharedPointer<Cord>, std::pair<unsigned int, bool>>> cord_stack;
    cord_stack.push({curr_cord, {0, false}});
    while (!cord_stack.empty()) {
        auto [cord, idx_right] = cord_stack.top();
        cord_stack.pop();
        unsigned int idx = idx_right.first;
        bool right_side = idx_right.second;
        if (!cord->Data().empty()) {
            unsigned int start = (idx > lower_idx) ? idx : lower_idx;
            unsigned int end = (idx + cord->Length() < upper_idx) ? idx + cord->Length() : upper_idx;
            if (start < end) {
                std::string_view result_sv(cord->Data().data() + start - idx, end - start);
                SharedPointer<Cord> result_cord = SharedPointer<Cord>{new Cord(result_sv)};
                if (right_side) {
                    new_right = result_cord;
                } else {
                    new_left = result_cord;
                }
            }
        } else {
            if (idx + cord->Length() > lower_idx) {
                cord_stack.push({cord->Right(), {idx + cord->Left()->Length(), true}});
                cord_stack.push({cord->Left(), {idx, false}});
            }
        }
    }
    if (new_left.Get() != nullptr && new_right.Get() != nullptr) {
        return ConcatCords(new_left, new_right);
    }
    if (new_left.Get() != nullptr) {
        return new_left;
    } 
    return new_right;
}