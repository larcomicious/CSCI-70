#include <stdio.h>
// #include <string.h>
#include <ctype.h>


void scanner(const char filename[]) {
    FILE *fptr;
    fptr = fopen(filename, "r");
    char input[100];
    fgets(input, 100, fptr);
    fclose(fptr);

    int i = 0;
    while (input[i] != '\0') {
        char ch = input[i];
        
        if (isdigit(ch)) {
            char numBuffer[100];
            int index = 0;
            
            // look for succeeding digits
            while (isdigit(ch)) {
                numBuffer[index++] = ch;
                // printf("added %c\n", ch);
                ch = input[++i];
            }
            
            printf("%s\n", numBuffer);

            // empty buffer
            for (int i = 0; i <= index; i++)
                numBuffer[i] = ' ';
        }
        i++;
    }
}

int main() {
    scanner("input.txt");

    return 0;
}
