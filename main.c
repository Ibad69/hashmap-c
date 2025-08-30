#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "hashmap.h"
#include <string.h>
#include <time.h>

int main () {
    clock_t start_time, end_time;
    double time_taken;
    // benchmark the hashmap by putting 10k values in it and then finding one from it 
    // compare the compute / searching time with something like go maps? IDK JUST DO IT BRO!

    htable_struct barr[100000];
    int barr_size = 0;

    // htable_struct *hashtable = calloc(16, sizeof(htable_struct));
    // htable htable = {.htable = hashtable, .max_length = 16, .curr_length = 0};
    htable *htable = ht_create();

    char *keys[100000];
    char *values[100000];
    // populate both data structures
    for (int i = 0; i < 100000; i++) {
        char buf[32];
        snprintf(buf, sizeof(buf), "key%d", i);

        keys[i] = strdup(buf);
        values[i] = strdup(buf);

        // printf("inserting keys[i] : %s \n", keys[i]);

        ht_insert(keys[i], values[i], htable);
        ht_insert_arr(keys[i], values[i], barr, &barr_size);

        // free(keys[i]);
    }

    printf("printingg the max length that has reached for the table : %zu \n", htable->max_length);
    printf("printing the current lenggth: %zu \n", htable->curr_length);

    // for (int i = 0; i < htable->max_length; i++) {
    //     // printf("the values that are existing : %s %s \n", htable.htable[i].name, htable.htable[i].value);
    // }

    // ht_insert("Content Type", "123", &htable, index, barr, &barr_size);


    // *************************** HASHMAP BENCHMARK ****************************************
    start_time = clock(); // Record the start time

    char *value = ht_get("key90000", htable);
    printf("the value received from the hashmap : %s \n", value);

    end_time = clock(); // Record the end time
    time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Convert to µs and ms for nicer printing
    double microseconds = time_taken * 1e6; // seconds → microseconds
    double milliseconds = time_taken * 1e3; // seconds → milliseconds

    if (microseconds < 1000.0) {
        printf("Lookup took %.3fµs\n", microseconds);
    } else if (milliseconds < 1000.0) {
        printf("Lookup took %.3fms\n", milliseconds);
    } else {
        printf("Lookup took %.3fs\n", time_taken);
    }
    // ******************* LINEAR SEARCH BENCHMARK ***************************
    clock_t start_time_arr, end_time_arr;
    double time_taken_arr;
    start_time_arr = clock(); // Record the start time

    char *arr = ht_get_arr("key90000", barr, &barr_size);
    printf("the value received from the arr : %s \n", arr);

    end_time_arr = clock(); // Record the end time
    time_taken_arr = (double)(end_time_arr - start_time_arr) / CLOCKS_PER_SEC; // Calculate elapsed time in seconds
    microseconds = time_taken_arr * 1e6; // seconds → microseconds
    milliseconds = time_taken_arr * 1e3; // seconds → milliseconds

    if (microseconds < 1000.0) {
        printf("Lookup took %.3fµs\n", microseconds);
    } else if (milliseconds < 1000.0) {
        printf("Lookup took %.3fms\n", milliseconds);
    } else {
        printf("Lookup took %.3fs\n", time_taken_arr);
    }

    ht_destroy(htable);

    return 0;
}
