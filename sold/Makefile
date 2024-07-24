all:
	g++ -fPIC -c -o foo0.o foo0.cpp
	g++ -fPIC -c -o foo1.o foo1.cpp
	ar rcs libfoo.a foo0.o foo1.o
	g++ -fPIC -shared -o libfoo.so.1.0.0 -Wl,-soname,libfoo.so.1 foo_shared.cpp libfoo.a
	ln -snf libfoo.so.1.0.0 libfoo.so.1
	ln -snf libfoo.so.1 libfoo.so
	g++ -fPIC -o driver driver.cpp -lfoo -L.

	mv libfoo.so.1.0.0 libfoo.so.1.0.0.default
	sold --check-output -i libfoo.so.1.0.0.default -o libfoo.so.1.0.0

clean:
	rm *.a *.o *.so *.so.*
