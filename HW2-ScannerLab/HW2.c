#include <stdio.h>
#include <ctype.h>


void scanner(const char filename[]) {
    // input
    FILE *in;
    char input[100]; // input buffer, arbitrary size
    in = fopen(filename, "r");
    fgets(input, 100, in);
    fclose(in);
    
    // output
    FILE *out;
    out = fopen("output.txt", "a");

    int i = 0;
    while (input[i] != '\0') {
        char ch = input[i];
        
        // skip spaces
        if (isspace(ch)) {
            i++;
            continue;
        }
        // if digit
        else if (isdigit(ch)) {
            char numBuffer[100]; // arbitrary size
            int index = 0;
            
            // look for succeeding digits
            while (isdigit(ch)) {
                numBuffer[index++] = ch;
                // printf("added %c\n", ch);
                ch = input[++i];
            }
            numBuffer[index] = '\0'; // null terminate string

            // output number
            fprintf(out, "NUM\t%s\n", numBuffer);

            // push back
            i--;

            // empty num buffer
            index = 0;
            numBuffer[0] = '\0';
        }
        else if (ch == '=') {
            if (input[++i] == '=')
                fprintf(out, "ASSIGN\t==\n");
            else {
                fprintf(out,"Lexical Error reading character \"=\"", ch);
                break;
            }
        }
        else if (ch == '+') {
            fprintf(out, "PLUS\t+\n");
        }
        else if (ch == '-') {
            fprintf(out, "MINUS\t-\n");
        }
        else {
            fprintf(out,"Lexical Error reading character \"%c\"", ch);
            break;
        }
        i++;
    }
}

int main() {
    scanner("input.txt");
    return 0;
}
