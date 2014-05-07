#ifndef HASH_H
#define HASH_H

/* debug macro */
#define GO_HERE() printf("%s %s %d\n", __FILE__, __func__, __LINE__)

struct node {
	char *key;
	char *value;
	struct node *next;
};

struct hashtable {
	unsigned long int size;
	struct node **table;	
};

struct hashtable *ht_create( unsigned long size );

void ht_set( struct hashtable *pht, char *key, char *value );

char *ht_get( struct hashtable *pht, char *key );

int ht_del( struct hashtable *pht, char *key );

void ht_release( struct hashtable *pht );

void show_hash_table(struct hashtable *pht);

#endif /* HASH_H */
