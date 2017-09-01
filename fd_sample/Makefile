CFLAGS += -g -W -Wall -lrt
LDFLAGS += -lpthread -lrt

PRGS =	\
	eventfd_sample		\
	pipe_sample		\
	socketpair_sample	\
	timerfd_sample		\
	signal_alarm		\
	timer_create_by_signal	\
	timer_create_by_thread	\
	timer_create_by_pipe	\
	signalfd_sample		\
	signal_fd_sim

all:	${PRGS}

clean:
	rm -fr ${PRGS} *.o

