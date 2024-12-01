#include "dna_strand.hpp"

#include <stdexcept>
#include <iostream>

DNAstrand::~DNAstrand() {
    while (head_ != nullptr) {
        Node* tmp = head_-> next;
        delete head_;
        head_ = tmp;
    }
}
void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
    char* c = new char[ReturnPatternSize()];
    if (&to_splice_in == this) { return; }
    Node* tmp = head_; 
    Node* prev = head_;
    for (int i = 0; i < ReturnPatternSize(); i++) { c[i] = tmp ->data; tmp = tmp -> next;} 
    int pattern_length = 0; 
    for (unsigned int i = 0; i < sizeof(pattern); i++) { 
        if (pattern[i] == '\0') { break; } 
        pattern_length++; 
    }
    int index = 0;
    for (int i = ReturnPatternSize() - pattern_length; i >= 0; i--) { 
        index = 0;
        for (int j = 0; j < pattern_length; j++) { 
            if (c[i + j] == pattern[j]) { 
                index++; if (index == pattern_length) { break; } 
                continue; 
            }
            break;
        } if (index == pattern_length) {
            int found = i + pattern_length;
            prev = head_; for (int i = 0; i < found - pattern_length - 1; i++) { prev = prev -> next; }
            Node* next = head_;
            for (int i = 0; i < found; i++) {
                next = next -> next; 
            }
            Node* node = prev -> next;
            if (found == pattern_length) { node = head_; }
            for (int i = 0; i < pattern_length; i++) {
                Node* deletes = node -> next;
                delete node;
                node = deletes; 
            }
            if (found == pattern_length) {
                head_ = to_splice_in.head_;
                to_splice_in.tail_ -> next = next;
            } else { 
                prev -> next = to_splice_in.head_;
                to_splice_in.tail_ -> next = next; 
            }
            if (next == nullptr) { tail_ = to_splice_in.tail_; }
            to_splice_in.head_ = nullptr;
            to_splice_in.tail_ = nullptr;
            std::cout << "first" << std::endl;
            delete[] c;
            return;
        }
    }
    std::cout << "second" << std::endl;
    delete[] c;
    throw std::runtime_error(" ");
}

int DNAstrand::ReturnPatternSize() {
    int idx = 0; 
    Node* tmp = head_;
    while (tmp != nullptr) {
        idx++;
        tmp = tmp -> next;
    }
    return idx;
}

