/* Program to decrypt a file by swapping adjacent bytes.
 *
 * Operating system: Linux Mint 17.2 Rafaela 
 * Compiler: gcc 4.9.2
 * Author: Padraig Redmond C15755659
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char unscrambled_filename[256];
	char byte1;
	char byte2;

	// check if an argument was given
	if (argc != 2)
	{
		printf("Incorrect number of arguments\n");
		printf("Correct usage: scramble <filename>\n");
		return 0;
	}
	
	// remove the .sbl extension
	strcpy(unscrambled_filename, argv[1]);
	unscrambled_filename[strlen(unscrambled_filename)-4] = '\0';

	// open both files
	FILE *scrambled_file = fopen(argv[1], "rb");
	if (scrambled_file == NULL)
	{
		printf("File not found\n");
		return 0;
	}
	FILE *unscrambled_file = fopen(unscrambled_filename, "wb");
	if (unscrambled_file == NULL)
	{
		printf("File not created\n");
		return 0;
	}

	// loop through the scrambled file until the end is reached
	while (1)
	{
		// read 2 bytes at a time
		fread(&byte1, sizeof(char), 1, scrambled_file);
		if (feof(scrambled_file))
		{
			// if EOF is reached here, the file has an even number of bytes 
			// and has been fully copied, so nothing more needs to be written
			break;
		}
		fread(&byte2, sizeof(char), 1, scrambled_file);
		if (feof(scrambled_file))
		{
			// if EOF is reached here, the file has an odd number of bytes
			// In this case the final byte must be copied over before the program exits
			fwrite(&byte1, sizeof(char), 1, unscrambled_file);
			break;
		}
		
		// write bytes in reverse order to scrambled file
		fwrite(&byte2, sizeof(char), 1, unscrambled_file);
		fwrite(&byte1, sizeof(char), 1, unscrambled_file);

	}

	fclose(scrambled_file);
	fclose(unscrambled_file);

	return 0;
	
}
