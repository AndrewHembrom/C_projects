#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] ){

    if (argc != 2){
        printf("Specify the file that needs to be read.");
    } else {

        FILE *file_ptr;

        char ch;
        int ch_num = 0;
        int lines_num = 0;
        int word_count = 0;

        file_ptr = fopen(argv[1], "r");

        if (NULL == file_ptr) {
            printf("The file cannot be opened \n");
            return EXIT_FAILURE;
        }

        printf("Content of the file: \n");

        while((ch = fgetc(file_ptr)) != EOF) {
            printf("%c", ch);
            if(ch != ' ' && ch != '\n') {
                ch_num++;
            }
            if(ch == ' ') {
                word_count++;
            }
            if(ch == '\n') {
                lines_num++;
                word_count++;
            }
        }
        printf("\n");
        printf("No. of Characters: %d\n", ch_num);
        printf("No. of Words: %d\n", word_count);
        printf("No. of Lines: %d\n", lines_num);
        printf("\n");

        fclose(file_ptr);
    }
    return 0;
}