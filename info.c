#include "info.h"

#include <stdlib.h>

#define MAX_STRING_LENGTH 1024

/* Author: Viktor Vikström, ens22vvm, vivi0427@student.umu.se */
/* Since: 2024-10-14 */

info *create_info(void) {

    info *inf = malloc(sizeof(info));
    inf->strings = (char **)malloc(sizeof(char *) * 5);
    inf->amount_of_strings = 5;

    if (inf == NULL) {
        perror("Failed malloc in create info (inf)");
        exit(EXIT_FAILURE);
    }

    if (inf->strings == NULL) {
        perror("Failed malloc in create info (inf->strings)");
        free(inf);
        exit(EXIT_FAILURE);
    }

    return inf;

}

info *read_input(FILE *input) {

    char string_buffer[MAX_STRING_LENGTH];
    info *inf = create_info();
    int i = 0;

    while (fgets(string_buffer, MAX_STRING_LENGTH, input) != NULL) {

        if (i == (inf->amount_of_strings - 1)) {

            inf->strings = realloc(inf->strings, sizeof(char **) * (inf->amount_of_strings + inf->amount_of_strings));
            inf->amount_of_strings = (inf->amount_of_strings + inf->amount_of_strings);

            if (inf->strings == NULL) {

                perror("Realloc in function read_input\n");
                destroy_info(inf);
                exit(EXIT_FAILURE);

            }
        }

        inf->strings[i] = malloc(sizeof(char *) * strlen(string_buffer) + 1);
        if (inf->strings[i] == NULL) {

            perror("Malloc in function read_input\n");
            destroy_info(inf);
            exit(EXIT_FAILURE);

        }

        string_buffer[strcspn(string_buffer, "\n")] = '\0';
        strcpy(inf->strings[i], string_buffer);
        i++;

    }

    inf->amount_of_strings = i;

    return inf;
}

static void destroy_char_array(char **array, int amount_of_elements) {

    for (int i = 0; i < amount_of_elements; i++) {

        free(array[i]);

    }
}

void destroy_info(info *inf) {

    destroy_char_array(inf->strings, get_amount_of_commands(inf));

    free(inf->strings);
    free(inf);
}

int get_amount_of_commands(info *inf) {

    return inf->amount_of_strings;

}

char *get_string_at_index(int index, info *inf) {

    char *str = malloc(strlen(inf->strings[index]) + 1); 
    if (str == NULL) {

        perror("Memory allocation failed");
        exit(EXIT_FAILURE);

    }

    strcpy(str, inf->strings[index]);
    return str;

}