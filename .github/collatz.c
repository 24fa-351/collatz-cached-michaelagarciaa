#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cache.h" 

int collatz_steps(unsigned long long num) {
    int steps = 0;
    while (num != 1) {
        if (num % 2 == 0)
            num /= 2;
        else
            num = 3 * num + 1;
        steps++;
    }
    return steps;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s <N> <MIN> <MAX> <cache_size>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    unsigned long long MIN = strtoull(argv[2], NULL, 10);
    unsigned long long MAX = strtoull(argv[3], NULL, 10);
    int cache_size = atoi(argv[4]);
    char cache_policy[10];

    printf("Enter cache policy (LRU, LFU): ");
    scanf("%s", cache_policy);

    init_cache(cache_size);

    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        unsigned long long RN = (rand() % (MAX - MIN + 1)) + MIN;
        int steps = 0;

        if (check_cache(RN, &steps) == 0) {
            steps = collatz_steps(RN);
            add_to_cache(RN, steps, cache_policy);
        }

        printf("Number: %llu, Steps: %d\n", RN, steps);
    }

    printf("Cache hit rate: %.2f%%\n", get_cache_hit_rate());

    free_cache();
    return 0;
}
