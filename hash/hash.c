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

/* check and find nearest prime http://www.numberempire.com/primenumbers.php */
/* tell the compiler that it's an unsigned integer by suffixing it with "U" */
#define MAX_32BIT_PRIME 4294967291U
#define MAX_64BIT_PRIME 18446744073709551557U

#define MAX_32BIT       4294967295U
#define MAX_64BIT       18446744073709551615U

#ifdef __x86_64__
#  define MAX_PRIME_OF_OS MAX_64BIT_PRIME
#else
#  define MAX_PRIME_OF_OS MAX_32BIT_PRIME
#endif

/* get next nearest prime of n */
static unsigned long next_prime(unsigned long n) {
    int i,t;
	if (n >= MAX_PRIME_OF_OS) 
		return MAX_PRIME_OF_OS;
    while(1) {
		t = sqrt(n);
        for(i=2;i<t;i++)
            if(n%i == 0) break;
        if(i == t) break;
		n++;
    }
    return n;
}

/* string duplicate 
 * http://www.diplom.org/~njudge/cxref/strdup.c.src.html 
 * https://fossies.org/dox/glibc-2.19/strdup_8c_source.html 
 */
static char *ht_strdup(const char *str) {
	char *copy = NULL;
	size_t size= strlen(str)+1;
	if ((copy = (char*)malloc(size)) == NULL)
		return NULL;
	return (char*)memcpy(copy, str, size);
}

/* Create a new hashtable. */
struct hashtable *ht_create( unsigned long size ) {

	struct hashtable *pht = NULL;
	unsigned long i;

	if( size < 1 ) return NULL;

	/* Allocate the table itself. */
	if( ( pht = malloc( sizeof( struct hashtable ) ) ) == NULL ) 
		return NULL;

	pht->size = next_prime(size);

	/* Allocate pointers to the head nodes. */
	if( ( pht->table = malloc( sizeof( struct node * ) * pht->size ) ) == NULL ) 
		return NULL;
	for( i = 0; i < pht->size; i++ ) 
		pht->table[i] = NULL;

	return pht;	
}

/* Hash a string for a particular hash table. */
static unsigned long ht_hash( struct hashtable *pht, char *key ) {

	unsigned long int hashval = 0;

	/* Convert our string to an integer */
	while( *key != '\0' )
		hashval = (hashval << 5) ^ (*key++);
	return hashval % pht->size;
}

/* Create a key-value pair. */
static struct node *ht_newpair( char *key, char *value ) {
	struct node *newpair;

	if( ( newpair = malloc( sizeof( struct node ) ) ) == NULL )
		return NULL;

	if( ( newpair->key = ht_strdup( key ) ) == NULL )
		return NULL;

	if( ( newpair->value = ht_strdup( value ) ) == NULL ) 
		return NULL;

	newpair->next = NULL;

	return newpair;
}

/* Insert a key-value pair into a hash table. */
void ht_set( struct hashtable *pht, char *key, char *value ) {
	unsigned long index = 0;
	struct node *newpair = NULL;
	struct node *next = NULL;
	struct node *last = NULL;

	index = ht_hash(pht, key);

	next = pht->table[ index ];
	/* compare key for ascending sort */
	/* if comment this code, insertion will at the start position */
#if defined(USE_DESC) || defined(USE_ASCE)
	while( next != NULL && next->key != NULL && strcmp(key, next->key) CMP_OPERATOR 0 ) {
		last = next;
		next = next->next;
	}
#endif
	/* There's already a pair. Let's replace that string. */
	if( next != NULL && next->key != NULL && strcmp(key, next->key) == 0 ) {

		free( next->value );
		next->value = ht_strdup( value );

		/* Nope, could't find it. Time to grow a pair. */
	} else {
		newpair = ht_newpair( key, value );

		/* We're at the start of the linked list in this index. */
		if( next == pht->table[ index ] ) {
			/* printf("insert at the start position.\n"); */
			newpair->next = next;
			pht->table[ index ] = newpair;
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
char *ht_get( struct hashtable *pht, char *key ) {
	unsigned long index = 0;
	struct node *pair;

	index = ht_hash(pht, key);

	/* Step through the index, looking for our value. */
	pair = pht->table[ index ];
	while( pair != NULL && pair->key != NULL && strcmp(key, pair->key) CMP_OPERATOR 0 ) 
		pair = pair->next;

	/* Did we actually find anything? */
	if( pair == NULL || pair->key == NULL || strcmp(key, pair->key) != 0 ) {
		return NULL;
	} else {
		return pair->value;
	}
}

/* delete pair from hash table */
int ht_del( struct hashtable *pht, char *key ) { 
	unsigned long i=0;
	struct node *cur;
	struct node *prev;
	for (;i<pht->size;i++) {
		cur = prev = pht->table[i];
		while (NULL != cur && NULL != cur->key) {
			if (strcmp(key, cur->key) == 0) {
				if (cur == pht->table[i]) {
					pht->table[i] = cur->next;
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
void ht_release( struct hashtable *pht ) {
	unsigned long i = 0;
	struct node *cur = NULL;
	struct node *tmp = NULL;
	for (;i<pht->size;i++) {
		cur = pht->table[i];
		while (cur != NULL) {
			tmp = cur->next;
			free(cur->key);     /* free key     */
			free(cur->value);   /* free value   */
			free(cur);			/* free node */
			cur = tmp;
		}
	}
	free(pht->table);     /* free tables     */
	free(pht);            /* free hash entry */
}

/* show used bucket of hash table */
void show_hash_table(struct hashtable *pht) {
	unsigned long i = 0; 
	struct node *tmp = NULL;
	printf("------------Hask table view------------\n");
	for (;i<pht->size;i++) {
		if (pht->table[i]!=NULL) {
			tmp = pht->table[i];
			printf("table[%lu]=", i);
			while (tmp != NULL) {
				printf("(%s:%s) ", tmp->key, tmp->value);
				tmp = tmp->next;
			}
		}
		printf("\n");
	}
	printf("---------------------------------------\n");
}
