
/* Becareful, you should free the memory which was allocate by strdup */
/* Enable certain library functions (strdup) on linux. See feature_test_macros(7) */
#define _XOPEN_SOURCE 500 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>    /* for sqrt */
#include "hash.h"

/* sort setting */
//#define USE_DESC
#if defined(USE_ASCE)
#pragma message ("ascending")
	#define CMP_OPERATOR >
#elif defined(USE_DESC)
#pragma message ("descending")
	#define CMP_OPERATOR <
#else
#pragma message ("disorder")
	#define CMP_OPERATOR !=
#endif

/* get nearest prime of n */
static unsigned long next_prime(unsigned long n) {
    int i,t;
    while(1) {
		t = sqrt(n);
        for(i=2;i<t;i++)
            if(n%i == 0) break;
        if(i == t) break;
		n++;
    }
    return n;
}

/* Create a new hashtable. */
struct hashtable_s *ht_create( unsigned long size ) {

	struct hashtable_s *hashtable = NULL;
	unsigned long i;

	if( size < 1 ) return NULL;

	/* Allocate the table itself. */
	if( ( hashtable = malloc( sizeof( struct hashtable_s ) ) ) == NULL ) 
		return NULL;

	hashtable->size = next_prime(size);

	/* Allocate pointers to the head nodes. */
	if( ( hashtable->table = malloc( sizeof( struct entry_s * ) * hashtable->size ) ) == NULL ) 
		return NULL;
	for( i = 0; i < hashtable->size; i++ ) 
		hashtable->table[i] = NULL;

	return hashtable;	
}

/* Hash a string for a particular hash table. */
static unsigned long ht_hash( struct hashtable_s *hashtable, char *key ) {

	unsigned long int hashval = 0;

	/* Convert our string to an integer */
	while( *key != '\0' )
		hashval = (hashval << 5) ^ (*key++);
	return hashval % hashtable->size;
}

/* Create a key-value pair. */
static struct entry_s *ht_newpair( char *key, char *value ) {
	struct entry_s *newpair;

	if( ( newpair = malloc( sizeof( struct entry_s ) ) ) == NULL )
		return NULL;

	if( ( newpair->key = strdup( key ) ) == NULL )
		return NULL;

	if( ( newpair->value = strdup( value ) ) == NULL ) 
		return NULL;

	newpair->next = NULL;

	return newpair;
}

/* Insert a key-value pair into a hash table. */
void ht_set( struct hashtable_s *hashtable, char *key, char *value ) {
	unsigned long index = 0;
	struct entry_s *newpair = NULL;
	struct entry_s *next = NULL;
	struct entry_s *last = NULL;

	index = ht_hash( hashtable, key );

	next = hashtable->table[ index ];
	/* compare key for ascending sort */
	/* if comment this code, insertion will at the start position */
#if defined(USE_DESC) || defined(USE_ASCE)
	while( next != NULL && next->key != NULL && strcmp( key, next->key ) CMP_OPERATOR 0 ) {
		last = next;
		next = next->next;
	}
#endif
	/* There's already a pair. Let's replace that string. */
	if( next != NULL && next->key != NULL && strcmp( key, next->key ) == 0 ) {

		free( next->value );
		next->value = strdup( value );

		/* Nope, could't find it. Time to grow a pair. */
	} else {
		newpair = ht_newpair( key, value );

		/* We're at the start of the linked list in this index. */
		if( next == hashtable->table[ index ] ) {
			/* printf("insert at the start position.\n"); */
			newpair->next = next;
			hashtable->table[ index ] = newpair;
			/* We're at the end of the linked list in this index. */
		} else if ( next == NULL ) {
			/* printf("insert at the end position.\n"); */
			last->next = newpair;
			/* We're in the middle of the list. */
		} else {
			/* printf("insert in the middle position.\n"); */
			newpair->next = next;
			last->next = newpair;
		}
	}
}

/* Retrieve a key-value pair from a hash table. */
char *ht_get( struct hashtable_s *hashtable, char *key ) {
	unsigned long index = 0;
	struct entry_s *pair;

	index = ht_hash( hashtable, key );

	/* Step through the index, looking for our value. */
	pair = hashtable->table[ index ];
	while( pair != NULL && pair->key != NULL && strcmp( key, pair->key ) CMP_OPERATOR 0 ) 
		pair = pair->next;

	/* Did we actually find anything? */
	if( pair == NULL || pair->key == NULL || strcmp( key, pair->key ) != 0 ) {
		return NULL;
	} else {
		return pair->value;
	}
}

/* delete pair from hash table */
int ht_del( struct hashtable_s *hashtable, char *key ) { 
	unsigned long i=0;
	struct entry_s *cur;
	struct entry_s *prev;
	for (;i<hashtable->size;i++) {
		cur = prev = hashtable->table[i];
		while (NULL != cur && NULL != cur->key) {
			if (strcmp(key, cur->key) == 0) {
				if (cur == hashtable->table[i]) {
					hashtable->table[i] = cur->next;
				} else {
					prev->next = cur->next;
				}
				/* free */
				free(cur->key);
				free(cur->value);
				free(cur);
				return 0;
			}
			prev = cur;
			cur = cur->next;
		}
	}

	return 1;
}

/* release hashtable */
void ht_release( struct hashtable_s *hashtable ) {
	unsigned long i = 0;
	struct entry_s *cur = NULL;
	struct entry_s *tmp = NULL;
	for (;i<hashtable->size;i++) {
		cur = hashtable->table[i];
		while (cur != NULL) {
			tmp = cur->next;
			free(cur->key);     /* free key     */
			free(cur->value);   /* free value   */
			free(cur);			/* free entry_s */
			cur = tmp;
		}
	}
	free(hashtable->table);     /* free tables     */
	free(hashtable);            /* free hash entry */
}

/* show used bucket of hash table */
void show_hash_table(struct hashtable_s *hashtable) {
	unsigned long i = 0; 
	struct entry_s *tmp = NULL;
	printf("------------Hask table view------------\n");
	for (;i<hashtable->size;i++) {
		if (hashtable->table[i]!=NULL) {
			tmp = hashtable->table[i];
			while (tmp != NULL) {
				printf("table[%lu]=%s:%s\n", i, tmp->key, tmp->value);
				tmp = tmp->next;
			}
		}
	}
	printf("---------------------------------------\n");
}
