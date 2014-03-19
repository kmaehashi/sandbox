#include <iostream>
#include <cstring>
#include <cstdlib>

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "give a single error number as an argument" << std::endl;
    return 1;
  }
  std::cout << ::strerror(atoi(argv[1])) << std::endl;
  return 0;
}
