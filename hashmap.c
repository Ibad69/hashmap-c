#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "hashmap.h"

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

// a hash map is generally built on top of an array
// it hashes the key of the pair (key, value) and then puts it onto some index with the value ofcourse
// and then at the time of finding we can just lookup to something like the hash itself
// They use a hash function to convert a "hashable" key into an index in the array. From a high-level, all that matters to us is that the hash function:
// Takes a key and returns an integer.
// Always returns the same integer for the same key.
// Always returns a valid index in the array (e.g. not negative, and not greater than the array size)
//


// Hashing function which implements kind of the FNV-1a Algorithm
uint64_t hash_key (const char* key, size_t capacity) {

    uint64_t hash = FNV_OFFSET;
    for (const char *p = key; *p; p++) {
        hash ^= (uint64_t) (unsigned char) (*p);
        hash *= FNV_PRIME;
    }

    return hash;
}

void ht_insert_entry(void *key, void *value, htable_struct *ht_entries_arr, size_t capacity) {
    
    // this below would mask out the from the huge hash last 4 bits because we are using & operator and & operator only has 4 bits if it is somethingg like 16
    // the bits for the capacity can increase also obviously, a smart and fast way to do this if had used modulus it would be slow because modulus has to subtract down
    // to the multiples of capacity until the value reached id less < capacity, this just masks out the bits according to capacity and gives us a result by comparing
    // the binary for the 5 bits and capacity

    uint64_t hash = hash_key((char*)key, capacity);
    size_t index = (size_t)(hash & (uint64_t)(capacity-1));

    ht_entries_arr[index].name = (char*)key;
    ht_entries_arr[index].value = (char*)value;
    // table->curr_length++; 
}


void ht_scale(htable *table) {
    size_t new_capacity = table->max_length * 2;

    // calloc the new entries

    htable_struct *new_ht = calloc(new_capacity, sizeof(htable_struct));
    if (new_ht == NULL) {
        printf("there was an error calloc the memory \n");
    }

    htable_struct *old_ht = table->htable;
    // table->htable = 

    for(int i = 0; i < table->max_length; i++) {
        htable_struct ht_entry = table->htable[i];
        // printf("the entries key : %s \n", ht_entry.name);
        if (ht_entry.name != NULL) {
            // do the ht_insert 
            ht_insert_entry(ht_entry.name, ht_entry.value, new_ht, new_capacity);
        }
    }
    // free(table->htable);
    table->max_length = new_capacity;
    table->htable = new_ht;
}

void ht_insert(void *key, void *value, htable *table){

    // then check if the index is already having a value
    // if so keep looping to next index until you find an empty one and insert there
    // implement linear probing over here
    
    // you will have to check first if the size is half full
    // if half full then realloc the memory
    if (table->curr_length == table->max_length / 2) {
        // printf("we have reached the point where we need to scale out our hashmap REALLOC length : %zu \n", table->curr_length);        
        ht_scale(table);
    }

    ht_insert_entry(key, value, table->htable, table->max_length);
    table->curr_length++;

    // barr[*barr_size] = kvp;
   // (*barr_size)++;
}

char* ht_get(void *key, htable *table){
    uint64_t hash = hash_key((char*)key, table->max_length);
    size_t index = (size_t)(hash & (uint64_t)(table->max_length - 1));
    return table->htable[index].value;
}

char *ht_get_arr(void *key, htable_struct *barr, int *barr_size) {
    for (size_t i = 0; i < *barr_size; i++) {
        if (strcmp(barr[i].name, (char*)key) == 0) {   
            return barr[i].value;
        }
    }
    return "no string found";
}

void ht_insert_arr(void *key, void *value, htable_struct *barr, int *barr_size){
    barr[*barr_size].name = (char*)key;
    barr[*barr_size].value = (char*)value;
    (*barr_size)++;
}

