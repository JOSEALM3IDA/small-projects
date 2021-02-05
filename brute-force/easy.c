#include <stdio.h>

// Generate all possible combinations of 4 digit numbers [0, 9999]
int main() {
    char pw[5] = {'\0'};
    int count = 0;

    for (int p0 = '0'; p0 <= '9'; p0++) {
        pw[0] = p0;
        for (int p1 = '0'; p1 <= '9'; p1++) {
            pw[1] = p1;
            for (int p2 = '0'; p2 <= '9'; p2++) {
                pw[2] = p2;
                for (int p3 = '0'; p3 <= '9'; p3++) {
                    pw[3] = p3;
                    printf("%s\t\t", pw);
                    count++;
                }
            }
        }
    }

    printf("\nNumber of passwords generated: %d\n", count);
    return 0;
}