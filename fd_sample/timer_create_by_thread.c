#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <wait.h>

int cnt = 0;
#define TV2SEC(tv) ((double)((tv).tv_sec) + (double)((tv).tv_usec / 1000000.0))
void timer_thread( sigval_t val );

int main( int argc, char ** argv ) {

    if( argc < 2 ) {
	exit( 1 );
    }

    timer_t timer_id;
    struct sigevent ev;
    ev.sigev_notify             = SIGEV_THREAD;
    ev.sigev_value.sival_ptr    = &timer_id;
    ev.sigev_notify_function    = timer_thread;
    ev.sigev_notify_attributes  = 0;

    struct itimerspec ts;
    ts.it_value.tv_sec = 1;
    ts.it_value.tv_nsec = 0;
    ts.it_interval.tv_sec = 1;
    ts.it_interval.tv_nsec = 0;

    timer_create( CLOCK_MONOTONIC,&ev, &timer_id );
    timer_settime( timer_id, 0, &ts, 0 );

    while( cnt < atoi( argv[1] )) {
	sleep( 1 );
    }
    return 0;
}

void timer_thread( sigval_t val ) {
    ( void )val;

    static struct timeval  tv1,tv2;
    gettimeofday( &tv2, 0 );
    if( cnt == 0 ) {
	printf( "timer_thread %d Path...\n", cnt + 1 );
    }
    else {
	double rtn = TV2SEC( tv2 ) - TV2SEC( tv1 ) - 1;
	printf( "timer_thread %d Path... [%f]\n", cnt + 1, rtn );
    }
    tv1 = tv2;
    cnt ++;
}
