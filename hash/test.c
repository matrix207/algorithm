#include <stdlib.h>  /* for setenv */
#include <stdio.h>
#include <mcheck.h>  /* for mtrace */
#include "hash.h"

int main( int argc, char **argv ) {
/* for trace memory leak */
#if defined(MTRACE)
	setenv("MALLOC_TRACE", "output", 1);  
	mtrace();
#endif

	/* create hash table */
	struct hashtable_s *hashtable = ht_create( 4 );
	
	/* Insertion */
	ht_set( hashtable, "key3", "test value of key1" );
	ht_set( hashtable, "key4", "math math math" );
	ht_set( hashtable, "dennis", "happy cooking" );
	ht_set( hashtable, "tina", "funny life" );
	ht_set( hashtable, "key0", "key0test" );
	ht_set( hashtable, "key1", "key1test" );
	ht_set( hashtable, "key9", "key9test" );
	ht_set( hashtable, "key6", "key6test" );
	ht_set( hashtable, "key7", "key7test" );

	/* searching */
	printf( "%s\n", ht_get( hashtable, "key3" ) );
	printf( "%s\n", ht_get( hashtable, "key4" ) );
	printf( "%s\n", ht_get( hashtable, "dennis" ) );
	printf( "%s\n", ht_get( hashtable, "tina" ) );
	printf( "%s\n", ht_get( hashtable, "key0" ) );
	printf( "%s\n", ht_get( hashtable, "key1" ) );

	/* show all */
	show_hash_table(hashtable);

	/* deletion */
	ht_del(hashtable, "key0");
	ht_del(hashtable, "key1");
	ht_del(hashtable, "key3");

	/* show all */
	show_hash_table(hashtable);

	/* free hash table */
	ht_release(hashtable);

/* for trace memory leak */
#if defined(MTRACE)
	muntrace();
#endif

	return 0;
}
