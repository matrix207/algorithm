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

struct hashtable_s *ht_create( unsigned long size );

void ht_set( struct hashtable_s *hashtable, char *key, char *value );

char *ht_get( struct hashtable_s *hashtable, char *key );

int ht_del( struct hashtable_s *hashtable, char *key );

void ht_release( struct hashtable_s *hashtable );

void show_hash_table(struct hashtable_s *hashtable);

#endif /* HASH_H */
