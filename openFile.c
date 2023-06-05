#include <stdio.h>

void readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file: %s\n", filename);
        return;
    }

    char buffer[1024];
    int count = 0;
    int number;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
        if (count == 1) {
            number++;
        }
        if (count == 2)
        {
            int numbertoproduce = atoi(buffer);
        }
        if (count == 3)
        {
            int queuesize = atoi(buffer);
        }
        count = count % 3;
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    const char* filename = argv[1];
    readFile(filename);
    return 0;
}
