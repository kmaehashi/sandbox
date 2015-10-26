#include <iostream>
#include "jubatus/core/storage/bit_vector.hpp"

using namespace std;

int main() {
  const int SIZE = 1000000; /* n.b. different from test.cpp */
  jubatus::core::storage::bit_vector bv(1024);

  clock_t start;

  start = clock();
  for (int i =0; i < SIZE; ++i) {
    bv.calc_hamming_distance(bv);
  }
  cout << "empty vector: took " << (clock() - start) << endl;

  bv.set_bit(1023); // flip the last bit
  start = clock();
  for (int i =0; i < SIZE; ++i) {
    bv.calc_hamming_distance(bv);
  }
  cout << "non-empty vector: took " << (clock() - start) << endl;

  return 0;
}
