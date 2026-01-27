#ifndef INFO_H
#define INFO_H

#include <stdio.h>
#include <string.h>

/**
* Included libraries: stdio.h, string.h
* 
* @defgroup module INFO_H info
*
* @brief Headerfile info.h
*
* Includes multiple function-declarations and one structure.
* The functions is meant to be used to store input from user when
* creating a pipeline.
*
* Some functions use dynamically allocated memory.
* Its the users responsibility to deallocate the dynamically allocated memory.
* Can be done with call to function destroy_info.
*
* @author Viktor Vikström, ens22vvm, vivi0427@student.umu.se
* @since 2024-10-14
*
* @{
*/

typedef struct info {

    int amount_of_strings; /** The number of commands. */
    char **strings; /** An array of char pointers to all the commands. */

} info;

/**
 * @brief Creates a info structure.
 * 
 * Dynamically allocates memory for a info structure.
 * Its the users responsibility to deallocate the dynamically allocated memory.
 * Can be done with call to function destroy_info.
 * 
 * @return A information structure.
 */
info *create_info(void);

/**
 * @brief Reads input.
 * 
 * Reads input and stores specific information.
 * This function dynamically allocates memory for a info structure.
 * To deallocate the memory call function destroy_info.
 * 
 * @param input The file to be read.
 * 
 * @return A info structure.
 */
info *read_input(FILE *input);

/**
 * @brief Returns the amount of commands.
 * 
 * @param inf The information structure.
 */
int get_amount_of_commands(info *inf);

/**
 * @brief Returns a string.
 * 
 * Returns a string at a specific index.
 * 
 * @param index The index.
 * @param inf The information structure.
 * 
 * @return The specific string.
 */
char *get_string_at_index(int index, info *inf);

/**
 * @brief Destroys the information structure.
 * 
 * Deallocate the dynamically allocated memory used by a information structure.
 * 
 * @param inf The information structure.
 */
void destroy_info(info *inf);

/**
 * @}
*/

#endif /* INFO_H */