#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"

CacheEntry *cache;
int current_cache_size = 0;
int cache_hits = 0;
int cache_accesses = 0;
int max_cache_size = 0;

void init_cache(int size) {
    cache = (CacheEntry *)malloc(size * sizeof(CacheEntry));
    max_cache_size = size;
}

int check_cache(unsigned long long num, int *steps) {
    cache_accesses++;  

    for (int i = 0; i < current_cache_size; i++) {
        if (cache[i].num == num) {
            *steps = cache[i].steps;
            cache_hits++;
            return 1;
        }
    }
    return 0;
}

void add_to_cache(unsigned long long num, int steps, const char *policy) {
    if (current_cache_size < max_cache_size) {
        cache[current_cache_size].num = num;
        cache[current_cache_size].steps = steps;
        current_cache_size++;
    } else {
        if (strcmp(policy, "LRU") == 0) {
            cache[0].num = num;
            cache[0].steps = steps;
        } else if (strcmp(policy, "LFU") == 0) {
            int min_freq_index = 0;
            for (int i = 1; i < current_cache_size; i++) {
                if (cache[i].freq < cache[min_freq_index].freq) {
                    min_freq_index = i;
                }
            }
            cache[min_freq_index].num = num;
            cache[min_freq_index].steps = steps;
        }
    }
}

double get_cache_hit_rate() {
    if (cache_accesses == 0) {
        return 0.0;  
    }
    return (double)cache_hits / cache_accesses * 100;
}


void free_cache() {
    free(cache);
}
