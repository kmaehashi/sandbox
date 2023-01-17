extern "C" int myfunc1() {
    return 100;
}

extern "C" int myfunc2() {
    throw "error";
}
