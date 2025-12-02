#include <stdio.h>
#include <stdlib.h>

#define FILENAME "input.txt"

int main(void) {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        return 1;
    }

    char line[128];
    int result = 0;
    int curr_value = 50;
    int direction = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        char R_or_L = line[0];
        int value = atoi(line + 1);

        if (R_or_L == 'R') {
            direction = 1;
        } else if (R_or_L == 'L') {
            direction = -1;
        }

        for (int i = 0; i < value; i++){
            curr_value = (curr_value + direction) % 100;
            if (curr_value == 0)
                result++;

            if (curr_value < 0) {
                curr_value += 100;
            }
        }
    }

    printf("Password = %d\n", result);
    fclose(fp);
    return 0;
}
