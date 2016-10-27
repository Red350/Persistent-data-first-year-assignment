/* Converts results.txt to results.bin using st_match struct
 * 
 * Operating system: Linux Mint 17.2 Rafaela 
 * Compiler: gcc 4.9.2
 * Author: Padraig Redmond C15755659
 */
 
#include <stdio.h>
#include "match.h"

int main()
{
	FILE *input, *output;
	struct st_match temp;

	// open both files
	input = fopen("results.txt", "r");
	if (input == NULL)
	{
		printf("File not found\n");
		return 0;
	}
	output = fopen("results.bin", "wb");
	if (output == NULL)
	{
		printf("File not created\n");
		return 0;
	}
	
	// loop through the text file, reading one line at a time and storing in a temporary struct
	while (fscanf(input,"%s %s %d %d", temp.team1, temp.team2, &temp.goals1, &temp.goals2) == 4)
	{
		// write the struct to results.bin
		fwrite(&temp, sizeof(struct st_match), 1, output);
	}

	fclose(input);
	fclose(output);

	return 0;
}

