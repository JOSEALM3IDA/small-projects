#include <stdio.h>

void getBmpSize(char* fileName, int* width, int* height) {
    int i;
    FILE* f = fopen(fileName, "rb");
    if (f == NULL) {
        *width = *height = -1;
        return;
    }

    unsigned char data[4] = { 0 };
    fseek(f, 18, SEEK_SET);
    
    for (i = 0; i < 4; i++)
        fread(data + i, sizeof(unsigned char), 1, f);

    *width = data[0] + data[1] * 256 + data[2] * 256 * 256 + data[3] * 256 * 256 * 256;

    for (i = 0; i < 4; i++)
        fread(data + i, sizeof(unsigned char), 1, f);

    *height = data[0] + data[1] * 256 + data[2] * 256 * 256 + data[3] * 256 * 256 * 256;

    fclose(f);
}


void main(int argc, char** argv) {
    int width, height;

    if (argc != 2) {
        fprintf(stderr, "ERROR: Must specify file name!\n");
        return;
    }

    getBmpSize(argv[1], &width, &height);
    if (width == -1 || height == -1)
        fprintf(stderr, "ERROR: File \"%s\" doesn't exist or program doesn't have enough permissions to open it!\n", argv[1]);

    printf("File: %s\nWidth: %d\tHeight: %d\n", argv[1], width, height);
}