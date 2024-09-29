#ifndef CACHE_H
#define CACHE_H

typedef struct {
    unsigned long long num;
    int steps;
    int freq; 
} CacheEntry;

void init_cache(int size);
int check_cache(unsigned long long num, int *steps);
void add_to_cache(unsigned long long num, int steps, const char *policy);
double get_cache_hit_rate();
void free_cache();

#endif
