#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void  make_sigaction( int sig, void ( *signal_handle )( int sig ));
void  signal_handler     ( int sig );
void  signal_term_handler( int sig );
void  signal_int_handler ( int sig );
void  signal_quit_handler( int sig );
int    pipefd[2];
struct {
    int     sigid;
    void    ( *sig_handle )( int sig );
}   siginfo[] = {
{   SIGTERM, signal_term_handler, },
{   SIGINT,  signal_int_handler,  },
{   SIGQUIT, signal_quit_handler, },
};
#define array( a )  ( sizeof( a )/sizeof( a[0] ))

int main( ) {

    fd_set rset, org_rset;
    unsigned int i;
    int sig = 0;

    for( i = 0; i < array( siginfo ); i ++ ) {
	make_sigaction( siginfo[i].sigid, signal_handler );
    }

    pipe( pipefd );
    FD_ZERO( &org_rset );
    FD_SET( pipefd[0], &org_rset );

    while( 1 ) {
	rset = org_rset;
	int rtn = select( FD_SETSIZE, &rset, 0, 0, 0 );
	if( rtn < 0 && errno == EINTR ) {
	    continue;
	}
	read( pipefd[0], &sig, sizeof( int ));
	for( i = 0; i < array( siginfo ); i ++ ) {
	    if( siginfo[i].sigid == sig ) {
		siginfo[i].sig_handle( siginfo[i].sigid );
		break;
	    }
	}
    }
    return 0;
}

void  make_sigaction( int sig, void ( *signal_handle )( int sig )) {
    struct sigaction sa;
    sa.sa_handler = signal_handle;
    sa.sa_flags   = SA_RESTART;
    sigemptyset( &sa.sa_mask );
    sigaction( sig, &sa, 0 );
    return;
}

void signal_term_handler( int sig ) {
    static int cnt;
    cnt ++;
    printf( "inside %s Path ... [%d] [%d]\n", __FUNCTION__, sig, cnt );
}

void signal_int_handler( int sig ) {
    static int cnt;
    cnt ++;
    printf( "inside %s Path ... [%d] [%d]\n", __FUNCTION__, sig, cnt );
}

void signal_quit_handler( int sig ) {
    static int cnt;
    cnt ++;
    printf( "inside %s Path ... [%d] [%d]\n", __FUNCTION__, sig, cnt );
}

void  signal_handler( int sig ) {
    write( pipefd[1], &sig, sizeof( int ));
}
