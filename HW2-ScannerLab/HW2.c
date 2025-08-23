#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>

#define BUFFER_SIZE 1024

// got from stack overflow. replaces substring with specified pattern and dynamically allocates to new 
// char array if substring and pattern are not same length
// https://stackoverflow.com/questions/56043612/how-to-replace-a-part-of-a-string-with-another-substring
char* strreplace(char *s, const char *s1, const char *s2) {
    char *p = strstr(s, s1);
    if (p != NULL) {
        size_t len1 = strlen(s1);
        size_t len2 = strlen(s2);
        if (len1 != len2)
            memmove(p + len2, p + len1, strlen(p + len1) + 1);
        memcpy(p, s2, len2);
    }
    return s;
}

void scanner(char* filename, const char* pattern) {
    // input
    FILE *in;
    char input[BUFFER_SIZE]; // input buffer
    in = fopen(filename, "r");
    // fgets(input, BUFFER_SIZE, in);
    
    // output
    char* outputFilename = strreplace(filename, pattern, "output");
    FILE *out;
    out = fopen(outputFilename, "w");

    // scanning
    while (fgets(input, BUFFER_SIZE, in)) {
        int i = 0;
        while (i != strlen(input)) {
            char ch = input[i];
            
            // skip spaces
            if (isspace(ch)) {
                i++;
                continue;
            }
            // if digit
            else if (isdigit(ch)) {
                char numBuffer[BUFFER_SIZE];
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
                char next = input[++i];
                if (next == '=')
                    fprintf(out, "ASSIGN\t==\n");
                else {
                    fprintf(out,"Lexical Error reading character \"%c\"", next);
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
        
    fclose(in);
    fclose(out);
}

void application(const char* pattern) {
    DIR *d;
    struct dirent *dir;
    const char *search_dir = "."; // current directory

    d = opendir(search_dir);
    if (d) {
        // go through all files in search_dir directory
        while ((dir = readdir(d)) != NULL) {
            char* filename = dir->d_name;
            // check if filename has pattern
            if (strstr(filename, pattern)) {
                // run scanner
                scanner(filename, pattern);
            }
        }
        closedir(d);
    }
}

int main() {
    application("input");
    return 0;
}
