#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <wait.h>
int pipefd[2];
#define TV2SEC(tv) ((double)((tv).tv_sec) + (double)((tv).tv_usec / 1000000.0))
void timer_thread( sigval_t val );

int main( int argc, char ** argv ) {

    if( argc < 2 ) {
	exit( 1 );
    }
    int max_cnt = atoi( argv[1] );

    struct timeval  tv1,tv2;
    sigval_t sig;
    int      i;
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

    pipe( pipefd );
    timer_create( CLOCK_MONOTONIC, &ev, &timer_id );
    timer_settime( timer_id, 0, &ts, 0 );

    fd_set rset, org_rset;
    FD_ZERO( &org_rset );
    FD_SET( pipefd[0], &org_rset );

    for( i = 0; i < max_cnt; i ++ ) {
	rset = org_rset;
	int rtn = select( FD_SETSIZE, &rset, 0, 0, 0 );
	if( rtn < 0 && errno == EINTR ) {
	    continue;
	}
	read( pipefd[0], &sig, sizeof( sigval_t ));
	gettimeofday( &tv2, 0 );
	if( i ) {
	    printf( "timer_thread %d Path... [%f]\n",
		i, TV2SEC( tv2 ) - TV2SEC( tv1 ));
	}
	tv1 = tv2;
    }
    return 0;
}

void timer_thread( sigval_t val ) {
    write( pipefd[1], &val, sizeof( sigval_t ));
}
