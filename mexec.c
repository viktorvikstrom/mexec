#include "mexec.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define READ_END 0
#define WRITE_END 1

/* Author: Viktor Vikström, ens22vvm, vivi0427@student.umu.se */
/* Since: 2024-10-14*/

int main(int argc, char *argv[]) {

    info *inf;
    FILE *input_file = stdin;

    if (argc == 2) {

        input_file = fopen(argv[1], "r");

        if (input_file == NULL) {

            fprintf(stderr, "%s: No such file or directory\n", argv[1]);
            exit(EXIT_FAILURE);

        }

    } else if (argc > 2) {

        fprintf(stderr, "Usage: %s [FILE]\n", argv[0]);
        exit(EXIT_FAILURE);

    }

    inf = read_input(input_file);

    if (argc == 2) {

        fclose(input_file);

    }
   
    pipeline(inf);

    return EXIT_SUCCESS;
}

void pipeline(info *inf) {

    pid_t pid;
    int num_commands = get_amount_of_commands(inf);
    int **fds = create_file_descriptors(num_commands);
    int status;

    for (int i = 0; i < num_commands; i++) {

        pid = fork();

        if (pid < 0) {

            cleanup_and_exit("Failed to fork", EXIT_FAILURE, inf, fds);

        } else if (pid == 0) {
                    
            if (i > 0) {   
                handle_pipe_ends(i, READ_END, fds, inf);
            }

            if (i < num_commands - 1) {
                handle_pipe_ends(i, WRITE_END, fds, inf);
            }

            close_pipes(num_commands, fds);

            char **command = parse_string_at_index(i, inf);
            if (command == NULL) {
                cleanup_and_exit("Failed to parse string", EXIT_FAILURE, inf, fds);
            }

            if (execvp(command[0], command) == -1) {

                destroy_parsed_array(command);
                cleanup_and_exit("nosuchcmd: No such file or directory", EXIT_FAILURE, inf, fds);

            }
        }
    }
    
   close_pipes(num_commands, fds);

    for (int i = 0; i < num_commands; i++) {

        wait(&status);

        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {

            cleanup_and_exit(NULL, EXIT_FAILURE, inf, fds);

        }
    }

    cleanup_and_exit(NULL, EXIT_SUCCESS, inf, fds);

}

void handle_pipe_ends(int index, int pipe_end, int **fds, info *inf) {

    int in_or_output;
    int pipe_at_index;

    if (pipe_end == READ_END) {

        in_or_output = 0;
        pipe_at_index = index - 1;
        
    } else {

        in_or_output = 1;
        pipe_at_index = index;

    }

    if (connect_pipe_end(pipe_at_index, pipe_end, in_or_output, fds) == 0) {
        cleanup_and_exit("Failed to dup2", EXIT_FAILURE, inf, fds);
    }
}

int connect_pipe_end(int pipe_at_index, int pipe_end, int in_or_output, int **fds) {

    if (dup2(fds[pipe_at_index][pipe_end], in_or_output) == -1) {
        return 0;
    }
    close(fds[pipe_at_index][pipe_end]);

    return 1;
}

void close_pipes(int amount_of_commands, int **fds) {
    
    for (int i = 0; i < amount_of_commands - 1; i++) {

        close(fds[i][WRITE_END]);
        close(fds[i][READ_END]);

    }
}

char **parse_string_at_index(int index, info *inf) {

    char *token;
    int amount_of_elements = 5;
    int i = 0;
    char *str = get_string_at_index(index, inf);

    char **parse_array = malloc(sizeof(char *) * 5); 
    if (parse_array == NULL) {

        return NULL;

    }

    token = strtok(str, " ");
    while (token != NULL) {

        parse_array[i] = malloc(sizeof(char) * (strlen(token) + 1));
        strncpy(parse_array[i], token, strlen(token) + 1);
        i++;

        if (i >= amount_of_elements) {

            amount_of_elements *= 2;
            parse_array = realloc(parse_array, sizeof(char **) * (amount_of_elements));

            if (parse_array == NULL) {

                return NULL;

            }
        }

        token = strtok(NULL, " ");
    }

    free(str);
    parse_array[i] = NULL;
    return parse_array;
}

int **create_file_descriptors(int number_of_commands) {

    int **array = (int**)malloc(sizeof(int *) * number_of_commands - 1);
    if (array == NULL) {

        perror("Failed malloc in create_file_descriptors\n");
        exit(EXIT_FAILURE);

    }

    for (int i = 0; i < number_of_commands - 1; i++) {

        array[i] = malloc(sizeof(int) * 2);
        if (array[i] == NULL) {

            perror("Failed malloc in create_file_descriptors loop\n");
            exit(EXIT_FAILURE);

        }
 
        if (pipe(array[i]) == -1) {

            perror("Failed call to function pipe() in create_file_descriptors\n");
            exit(EXIT_FAILURE);

        } 
    }

    return array;
}

void destroy_file_descriptors(int number_of_commands, int **fds) {

    for (int i = 0; i < number_of_commands - 1; i++) {

        close(fds[i][WRITE_END]);
        close(fds[i][READ_END]);
        free(fds[i]);

    }

    free(fds);

}

void destroy_parsed_array(char **array) {

    int i = 0;

    while (array[i] != NULL) {

        free(array[i]);
        i++;

    }
    
    free(array);

}

void cleanup_and_exit(const char *error_msg, int error_code, info *inf, int **fds) {

    if (error_code == 1 && error_msg != NULL) {
        fprintf(stderr, "%s\n", error_msg); 
    }

    destroy_file_descriptors(get_amount_of_commands(inf), fds);
    destroy_info(inf);
    exit(error_code);

}