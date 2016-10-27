/* Program to encrypt a file by swapping adjacent bytes.
 *
 * Operating system: Linux Mint 17.2 Rafaela 
 * Compiler: gcc 4.9.2
 * Author: Padraig Redmond C15755659
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char extension[] = ".sbl";
	char scrambled_name[256];
	char byte1;
	char byte2;

	// check if an argument was given
	if (argc != 2)
	{
		printf("Incorrect number of arguments\n");
		printf("Correct usage: scramble <filename>\n");
		return 0;
	}
	
	// create the filename for the scrambled file
	strcpy(scrambled_name, argv[1]);
	strcat(scrambled_name, extension);

	// open both files
	FILE *original = fopen(argv[1], "rb");
	if (original == NULL)
	{
		printf("File not found\n");
		return 0;
	}
	FILE *scrambled = fopen(scrambled_name, "wb");
	if (scrambled == NULL)
	{
		printf("File not created\n");
		return 0;
	}

	// loop through the original file until the end is reached
	while (1)
	{
		// read 2 bytes at a time
		fread(&byte1, sizeof(char), 1, original);
		if (feof(original))
		{
			// if EOF is reached here, the file has an even number of bytes 
			// and has been fully copied, so nothing more needs to be written
			break;
		}
		fread(&byte2, sizeof(char), 1, original);
		if (feof(original))
		{
			// if EOF is reached here, the file has an odd number of bytes
			// In this case the final byte must be copied over before the program exits
			fwrite(&byte1, sizeof(char), 1, scrambled);
			break;
		}
		
		// write bytes in reverse order to scrambled file
		fwrite(&byte2, sizeof(char), 1, scrambled);
		fwrite(&byte1, sizeof(char), 1, scrambled);

	}

	fclose(original);
	fclose(scrambled);

	return 0;
	
}
