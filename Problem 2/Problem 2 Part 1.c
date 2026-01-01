#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILENAME "input.txt"
#define SIZE 4096       
#define MAX_RANGES 128

char values[SIZE];
long long starts[MAX_RANGES], ends[MAX_RANGES];
int count = 0;

static int read_input(void);


static long long pow10ll(int k) {
    long long p = 1;
    while (k-- > 0) p *= 10;
    return p;
}

static long long ceil_div_ll(long long a, long long b) {
    if (a >= 0) return (a + b - 1) / b;
    return a / b;
}

static __int128 sum_arith_ll(long long lo, long long hi) {
    __int128 n = (__int128)(hi - lo + 1);
    return n * ((__int128)lo + (__int128)hi) / 2;
}

static __int128 sum_invalid_in_range(long long a, long long b) {
    __int128 total = 0;

    for (int k = 1; k <= 9; k++) {                 
        long long p10 = pow10ll(k);                
        long long denom = p10 + 1;                
        long long x_min = ceil_div_ll(a, denom);
        long long x_max = b / denom;

        long long k_lo = (k == 1) ? 1 : pow10ll(k - 1);
        long long k_hi = p10 - 1;

        if (x_min < k_lo) x_min = k_lo;
        if (x_max > k_hi) x_max = k_hi;

        if (x_min <= x_max) {
            __int128 sumX = sum_arith_ll(x_min, x_max);
            total += (__int128)denom * sumX;
        }
    }
    return total;
}

int main(void) {
    if (!read_input()) return 1;

    __int128 total_sum = 0;

    for (int i = 0; i < count; i++) {
        long long a = starts[i];
        long long b = ends[i];
        if (a > b) { long long t = a; a = b; b = t; }
        total_sum += sum_invalid_in_range(a, b);
    }

    // print __int128
    if (total_sum == 0) {
        printf("0\n");
    } else {
        char out[64];
        int idx = 0;
        __int128 x = total_sum;
        if (x < 0) { putchar('-'); x = -x; }
        while (x > 0) {
            int digit = (int)(x % 10);
            out[idx++] = (char)('0' + digit);
            x /= 10;
        }
        while (idx--) putchar(out[idx]);
        putchar('\n');
    }

    return 0;
}

static int read_input(void) {
    FILE *fp = fopen(FILENAME, "r");
    if (!fp) {
        perror("fopen");
        return 0;
    }

    if (!fgets(values, sizeof(values), fp)) {
        fclose(fp);
        fprintf(stderr, "Failed to read input line\n");
        return 0;
    }
    fclose(fp);

    // strip trailing newline if present
    values[strcspn(values, "\r\n")] = '\0';

    char *range = strtok(values, ",");

    while (range != NULL) {
        long long a, b;
        if (sscanf(range, "%lld-%lld", &a, &b) == 2) {
            if (count >= MAX_RANGES) {
                fprintf(stderr, "Too many ranges (max %d)\n", MAX_RANGES);
                return 0;
            }
            starts[count] = a;
            ends[count]   = b;
            count++;
        }
        range = strtok(NULL, ",");
    }

    printf("\nStored ranges:\n");
    for (int i = 0; i < count; i++) {
        printf("Range %d: %lld to %lld\n", i, starts[i], ends[i]);
    }

    return 1;
}
