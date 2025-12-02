#include <stdio.h>
#include <stdlib.h>

#define FILENAME "input.txt"

int main(void) {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    char line[128];
    int result = 0;
    int curr_value = 50; 

    while (fgets(line, sizeof(line), fp) != NULL) {
        char R_or_L = line[0];
        long value = atoi(line + 1);  
        int direction;

        if (R_or_L == 'R')
            direction = 1;
        else if (R_or_L == 'L')
            direction = -1;

        int dist_to_zero;
        if (direction == 1) {
            dist_to_zero = (curr_value == 0) ? 100 : (100 - curr_value);
        } else { 
            dist_to_zero = (curr_value == 0) ? 100 : curr_value;
        }

        if (value >= dist_to_zero) {
            int remaining = value - dist_to_zero;
            result += 1 + remaining / 100;
        }

        int delta = (value % 100) * direction;

        curr_value = (curr_value + delta) % 100;
        
        if (curr_value < 0)
            curr_value += 100;
    }

    printf("Password = %d\n", result);
    fclose(fp);
    return 0;
}
