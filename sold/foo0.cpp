#include <iostream>

#include <foo1.hpp>

namespace foo {

void DoTryCatch(int i) {
    Context ctx;
    try {
        ctx.bar(i);
        std::cout << "success" << std::endl;
    } catch (Context::MyException&) {
        std::cout << "exception" << std::endl;
    }
}

}
