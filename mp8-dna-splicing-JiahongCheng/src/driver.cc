#include <iostream>

#include "dna_strand.hpp"

int main() {
  
  Node* first1 = new Node('a');
  Node* first2 = new Node('a');
  Node* first3 = new Node('a');
  Node* first4 = new Node('a');
  Node* first5 = new Node('a');
  first1->next = first2;
  first2->next = first3;
  first3->next = first4;
  first4->next = first5;
  DNAstrand dna = DNAstrand(first1, first5);
  DNAstrand dna2 = DNAstrand(first1, first5);
  char pattern[] = "aaa";
  dna.SpliceIn(pattern, dna2);

  return 0;
}
