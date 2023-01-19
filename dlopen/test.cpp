#include <cstdio>
#include <dlfcn.h>

int main() {
    void* lib = dlopen("./lib.so", RTLD_LAZY);
    int (*fptr)();
    //fptr = (int(*)())dlsym(lib, "myfunc1");
    fptr = (int(*)())dlsym(lib, "myfunc2");
    int out = fptr();
    printf("%d\n", out);
}
