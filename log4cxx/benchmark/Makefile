all:
	g++ -o bench1 bench1.cpp `pkg-config liblog4cxx --libs --cflags`
	g++ -o bench2 bench2.cpp `pkg-config liblog4cxx --libs --cflags`

run-bench1:
	$(shell for i in `seq 10`; do time ./bench1 > /dev/null; done)

run-bench2:
	$(shell for i in `seq 10`; do time ./bench2 > /dev/null; done)
