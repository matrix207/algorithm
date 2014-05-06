#ifndef HASH_H
#define HASH_H

/* debug macro */
#define GO_HERE() printf("%s %s %d\n", __FILE__, __func__, __LINE__)

struct entry_s {
	char *key;
	char *value;
	struct entry_s *next;
};

struct hashtable_s {
	unsigned long int size;
	struct entry_s **table;	
};

/* Create a new hashtable. */
struct hashtable_s *ht_create( unsigned long size );

/* Insert a key-value pair into a hash table. */
void ht_set( struct hashtable_s *hashtable, char *key, char *value );

/* Retrieve a key-value pair from a hash table. */
char *ht_get( struct hashtable_s *hashtable, char *key );

/* release hashtable */
void ht_release( struct hashtable_s *hashtable );

/* show used bucket of hash table */
void show_hash_table(struct hashtable_s *hashtable);

#endif /* HASH_H */
