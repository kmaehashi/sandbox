#include <foo1.hpp>

namespace foo {

void Context::bar(int i) {
    if (i < 0) {
        throw MyException();
    }
}

}
