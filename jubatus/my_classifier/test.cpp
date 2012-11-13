#include <jubatus/storage/storage_factory.hpp>

#include "test.hpp"

namespace jubatus {

my_classifier::my_classifier() : classifier_base(storage::storage_factory::create_storage("local")) {
}

my_classifier::~my_classifier() {}

void my_classifier::train(const sfv_t& sfv, const std::string& label) {
  /* nop */
}

std::string my_classifier::name() const {
  return "MY_CLASSIFIER";
}

} /* namespace jubatus */

int main() {
  jubatus::my_classifier c;
  std::cout << c.C() << std::endl;
}
