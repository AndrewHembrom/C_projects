#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

struct WordFreq {
    char word[MAX_WORD_LENGTH];
    int frequency;
};

int main(int argc, char *argv[]) {

    if (argc != 2){
        printf("Specify the file that needs to be read.");
        return EXIT_FAILURE;
    }

    FILE *file_ptr;
    char ch;
    int ch_num = 0;
    int ch_num_wo_space = 0;
    int lines_num = 0;
    int word_count = 0;
    char current_word[MAX_WORD_LENGTH];
    int current_word_length = 0;

    struct WordFreq word_frequencies[MAX_WORDS];
    int unique_word_count = 0;

    file_ptr = fopen(argv[1], "r");
    if (NULL == file_ptr) {
        printf("The file cannot be opened \n");
        return EXIT_FAILURE;
    }

    printf("Content of the file: \n");

    while((ch = fgetc(file_ptr)) != EOF) {
        printf("%c", ch);
        ch_num++;

        if(ch == ' ' || ch == '\n'){
            ch_num_wo_space++;
        }

        if(ch!=' ' && ch!='\n') {
            current_word[current_word_length++] = ch;
        } else {
            if (current_word > 0) {
                current_word[current_word_length] = '\0';
                word_count++;

                int found = 0;
                for (int i = 0; i < unique_word_count; i++) {
                    if(strcmp(word_frequencies[i].word, current_word) == 0) {
                        word_frequencies[i].frequency++;
                        found = 1;
                        break;
                    }
                }

                if(!found && unique_word_count < MAX_WORDS) {
                    strcpy(word_frequencies[unique_word_count].word, current_word);
                    word_frequencies[unique_word_count].frequency = 1;
                    unique_word_count++;
                }

                current_word_length = 0;

                if (ch == '\n') {
                    lines_num++;
                }
            }
        }
    }

    // Handles last word if it wasn't followed by a space or newline
    if (current_word_length > 0) {
        current_word[current_word_length] = '\0';
        word_count++;
        lines_num++;

        int found = 0;
        for (int i = 0; i < unique_word_count; i++) {
            if (strcmp(word_frequencies[i].word, current_word) == 0) {
                word_frequencies[i].frequency++;
                found = 1;
                break;
            }
        }

        if (!found && unique_word_count < MAX_WORDS) {
            strcpy(word_frequencies[unique_word_count].word, current_word);
            word_frequencies[unique_word_count].frequency = 1;
            unique_word_count++;
        }
    }

    fclose(file_ptr);

    int max_frequency = 0;
    char most_common_word[MAX_WORD_LENGTH];
    for (int i = 0; i < unique_word_count; i++){
        if (word_frequencies[i].frequency > max_frequency) {
            max_frequency = word_frequencies[i].frequency;
            strcpy(most_common_word, word_frequencies[i].word);
        }
    }

    // Output results
    printf("\nNo. of Characters: %d\n", ch_num);
    printf("No. of Characters without space: %d\n", ch_num - ch_num_wo_space);
    printf("No. of Words: %d\n", word_count);
    printf("No. of Lines: %d\n", lines_num);
    printf("Most Common Word: '%s' (appears %d times)\n", most_common_word, max_frequency);

    return 0;
}