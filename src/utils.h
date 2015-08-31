#ifndef _UTILS_H
#define _UTILS_H

#include <iostream>
#include <vector>
#include <bitset>
#include <unistd.h>	// getopt()


/**
 * @brief Shows the usages.
 * @param argv0 The argv[0] from main the get name of the program.
*/
void show_usages(char *argv0);

/**
 * Bitmask to get the flags passed to the application.
*/
enum /*class */OPTIONS
{
	NONE		= 0x0,
	INVALID		= 0x2,
	CREAT_LOG	= 0x4,
	CURR_FILE	= 0x8,
	FULL_LOG	= 0x12
};

/**
 * @brief Calls getopt()
 * @param argc argc from main.
 * @param argv argv from main.
 * @param options Options to read.
 * @return An OPTIONS bitmask.
 */
unsigned char read_opt(int argc, char *const *argv, const char *options);

/**
 * @brief Reads a hexadecimal pattern to find from a file.
 * @param patVec Vector where to save the patterns read from 'file'.
 * @param path File with the patterns to find.
 * @return On success returns 0. On error returns -1.
 */
int read_patterns(std::vector<std::bitset<8>> *patVec, const std::string path);


#endif	// UTILS_H