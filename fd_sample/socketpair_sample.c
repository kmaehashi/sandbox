#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>

int main( int argc, char ** argv ) {
    int   fd[2], j;
    uint64_t u;

    if( argc < 3 ) {
	fprintf( stderr, "Usage: %s <num> <num>...\n", argv[0] );
	exit( EXIT_FAILURE );
    }

    socketpair( AF_LOCAL, SOCK_STREAM, 0, fd );
    switch( fork( )) {
    case 0:
	close( fd[0] );
	for( j = 2; j < argc; j ++ ) {
	    u = strtoull( argv[j], NULL, 0 );
	    write( fd[1], &u, sizeof( u ));
	}
	close( fd[1] );
	printf( "Child completed\n" );
	exit( EXIT_SUCCESS );

    default:
	close( fd[1] );
	printf( "Parent sleep %d sec.\n", atoi( argv[1] ));
	sleep( atoi( argv[1] ));

	while( read( fd[0], &u, sizeof( uint64_t )) > 0 )
	    printf( "parent_read by sock:[%lld]\n", ( unsigned long long )u );

	close( fd[0] );
	printf( "Parent completed\n" );
	exit( EXIT_SUCCESS );
    }
}
