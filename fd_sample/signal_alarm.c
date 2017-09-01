#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

void sig_handler( int sig_no );
int  limit_loop  = 0;
int  loop_count  = 0;

int main( int argc, char ** argv ) {

    struct sigaction sa;

    if( argc < 4 ) {
	fprintf( stderr, "Usage: %s <num> <num> <num>...\n", argv[0] );
	exit( EXIT_FAILURE );
    }

    struct itimerval val;
    val.it_interval.tv_sec  = atoi( argv[1] );
    val.it_interval.tv_usec = 0;
    val.it_value.tv_sec     = atoi( argv[2] );
    val.it_value.tv_usec    = 0;
    limit_loop = atoi( argv[3] );

    setitimer( ITIMER_REAL, &val, 0 );

    sa.sa_handler = sig_handler;
    sigemptyset( &sa.sa_mask );
    sigaction( SIGALRM, &sa, 0 );

    while( limit_loop != loop_count ) {
        pause( );
    }
    return 0;
}

void sig_handler( int sig_no ) {

    ( void )sig_no;

    static int sec = 0;
    printf( "%2d count passed.\n", sec );
    sec ++;
    loop_count ++;
}
