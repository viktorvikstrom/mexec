#ifndef MEXEC_H
#define MEXEC_H

#include <stdio.h>
#include <stdlib.h>
#include "info.h"

/**
* Included libraries: stdlib.h, stdio.h
* 
* @defgroup module MEXEC_H mexec
*
* @brief Headerfile mexec.h
*
* Includes multiple function declarations for a bash pipeline.
* This code is meant to be used with a specific source file "info.c"
*
* @author Viktor Vikström, ens22vvm, vivi0427@student.umu.se
* @since 2024-10-14
*
* @{
*/

/**
 * @brief Execute a pipeline.
 * 
 * This function executes a pipeline of bash commands.
 * The commands and arguments is stored inside inf.
 * 
 * @param inf A struct of information to execute the pipeline.
 * @param inf The commands to be executed and amount of commands.
 * 
 */
void pipeline(info *inf);

/**
 * @brief Parse a string.
 * 
 * A function that parses a string by a space.
 * 
 * This function creates a dynamically allocated memory.
 * Its the users respornsibility to deallocate the memory.
 * 
 * To deallocate the memory a call to function free().
 * 
 * @param str The string to be parsed.
 * @param inf A struct of information to execute the pipeline.
 * 
 * @return The parsed string.
 * 
 */
char **parse_string_at_index(int i, info *inf);

/**
 * @brief Creates file descriptors.
 * 
 * Dynamically allocates memory for a matrix of filedescriptors.
 * 
 * Its the users responsibility to deallocate the dynamically allocated memory
 * This function creates. Can be done with a call to function destroy_file_descriptors.
 * 
 * @param number_of_commands The number of commands.
 * 
 * @return A matrix of file desriptors.
 * 
*/
int **create_file_descriptors(int number_of_commands);

/**
 * @brief Destroys file descriptors.
 * 
 * This function is used to deallocate the dynamically allocated memory
 * used by the filedescriptors.
 * 
 * @param number_of_commands The amount of commands.
 * @param fds The filedescriptors.
 */
void destroy_file_descriptors(int number_of_commands, int **fds);

/**
 * @brief Destroys a parsed array.
 * 
 * Destroy the dynamically allocated memory used by a parsed array.
 * 
 * @param array The parsed array.
 */
void destroy_parsed_array(char **array);

/**
 * @brief Closes pipes.
 * 
 * Closes all the pipes used by a process.
 * 
 * @param amount_of_commands The amount of commands.
 * @param fds The filedescriptors.
 */
void close_pipes(int amount_of_commands, int **fds);

/**
 * @brief Clean memory and exit.
 * 
 * Deallocates memory used for filedescriptors and info.
 * Also prints error message to stderr if needed and exit with specific error code.
 * If error_msg is NULL no output to stderr is printed.
 * 
 * @param error_msg The error message to stderr.
 * @param error_code EXIT_SUCCESS or EXIT_FAILURE.
 * @param inf A struct of information to execute the pipeline.
 * @param fds The filedescriptors.
 */
void cleanup_and_exit(const char *error_msg, int error_code, info *inf, int **fds);

/**
 * @brief Connects input or output to pipe.
 * 
 * Connects input or ouput to a pipe.
 * 
 * @param index The row of the pipe.
 * @param pipe_end Read or write end.
 * @param fds The filedescriptors.
 * @param inf A struct of information to execute the pipeline.
 */
void handle_pipe_ends(int index, int pipe_end, int **fds, info *inf);

/**
 * @brief Help function for handle_pipe_ends.
 * 
 * Uses dup2 to connect ouput or input to pipe.
 * Returns 0 on failure.
 * 
 * @param pipe_at_index Row number of the pipe.
 * @param pipe_end Read or write end.
 * @param in_or_ouput Stdin or stdout.
 * @param fds The filedescriptors.
 * 
 * @return 1 or 0.
 */
int connect_pipe_end(int pipe_at_index, int pipe_end, int in_or_output, int **fds);

/**
 * @}
*/

#endif /* MEXEC_H */