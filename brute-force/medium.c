#include <stdio.h>

#define PW_LENGTH 5

char cs[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
             'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
             '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
int length = sizeof(cs) / sizeof(char);
char pw[PW_LENGTH + 1] = {'\0'};
unsigned long long int pwCount = 0;

// Generate all possible combinations of digits and letters (capitalized or not), with length PW_LENGTH
void recursive(int pos) {
    int p;
    if (pos == PW_LENGTH - 1)
        for (p = 0; p < length; p++) {
            pw[pos] = cs[p];
            pwCount++;
        }
    else
        for (p = 0; p < length; p++) {
            pw[pos] = cs[p];
            recursive(pos + 1);
        }
}

int main() {
    recursive(0);
    printf("Number of passwords generated: %llu\n", pwCount);
    return 0;
}