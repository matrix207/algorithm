#include <stdlib.h>  /* for setenv */
#include <stdio.h>
#include <mcheck.h>  /* for mtrace */
#include "hash.h"
#include <math.h>

int main( int argc, char **argv ) {
/* for trace memory leak */
#if defined(MTRACE)
	setenv("MALLOC_TRACE", "output", 1);  
	mtrace();
#endif

	/* create hash table */
	struct hashtable *pht = ht_create( 4 );
	
	/* Insertion */
	ht_set( pht, "key3", "test value of key1" );
	ht_set( pht, "key4", "math math math" );
	ht_set( pht, "dennis", "happy cooking" );
	ht_set( pht, "tina", "funny life" );
	ht_set( pht, "key0", "key0test" );
	ht_set( pht, "key1", "key1test" );
	ht_set( pht, "key9", "key9test" );
	ht_set( pht, "key6", "key6test" );
	ht_set( pht, "key7", "key7test" );

	/* searching */
	printf( "%s\n", ht_get( pht, "key3" ) );
	printf( "%s\n", ht_get( pht, "key4" ) );
	printf( "%s\n", ht_get( pht, "dennis" ) );
	printf( "%s\n", ht_get( pht, "tina" ) );
	printf( "%s\n", ht_get( pht, "key0" ) );
	printf( "%s\n", ht_get( pht, "key1" ) );

	/* show all */
	show_hash_table(pht);

	/* deletion */
	ht_del(pht, "key0");
	ht_del(pht, "key1");
	ht_del(pht, "key3");

	/* show all */
	show_hash_table(pht);

	/* free hash table */
	ht_release(pht);

/* for trace memory leak */
#if defined(MTRACE)
	muntrace();
#endif

	return 0;
}
