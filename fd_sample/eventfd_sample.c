#include <sys/eventfd.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char ** argv ) {
    int      efd, j;
    uint64_t u;

    if( argc < 3 ) {
	fprintf( stderr, "Usage: %s <num> <num> ...\n", argv[0] );
	exit( EXIT_FAILURE );
    }

    efd = eventfd( 0, 0 );
    switch( fork()) {
    case 0:
	for( j = 2; j < argc; j ++ ) {
	    u = strtoull( argv[j], 0, 0 );
	    write( efd, &u, sizeof( u ));
	}
	close( efd );
	printf( "Child completed\n" );
	exit( EXIT_SUCCESS );

    default:
	printf( "Parent sleep %d sec.\n", atoi( argv[1] ));
	sleep( atoi( argv[1] ));

	read( efd, &u, sizeof( uint64_t ));
	printf( "Parent read by eventfd:[%llu]\n", ( unsigned long long )u );
	close( efd );
	exit( EXIT_SUCCESS );
    }
}
