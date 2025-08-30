#include <stddef.h>
#include <stdint.h>

typedef struct HTABLE_STRUCT {
    char *name;
    char *value;
} htable_struct;

typedef struct HTABLE {
    htable_struct *htable;
    size_t curr_length;
    size_t max_length;
} htable;

uint64_t hash_key (const char* key, size_t capacity);


htable* ht_create(); 
void ht_destroy(htable *table); 
void ht_insert(void *key, void *value, htable *table); 
char* ht_get(void *key, htable *table); 
char* ht_get_arr(void *key, htable_struct *barr, int *barr_size);
void ht_insert_arr(void *key, void *value, htable_struct *barr, int *barr_size);
