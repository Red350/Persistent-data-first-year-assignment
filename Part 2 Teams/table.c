/* Create a league table based on the results in results.bin
 *
 * Operating system: Linux Mint 17.2 Rafaela 
 * Compiler: gcc 4.9.2
 * Author: Padraig Redmond C15755659
 */
 
#include <stdio.h>
#include <string.h>
#include "match.h"

#define NUM_TEAMS 20

struct st_team
{
	char name[20];
	int num_games;
	int points;
};

void bubble_sort(struct st_team[]);

int main()
{
	FILE *f;
	struct st_team table[20];
	struct st_match temp;
	int last_updated = 0;
	int i, j;

	// initialise all the teams in the table
	for (i = 0; i < NUM_TEAMS; i++)
	{
		strcpy(table[i].name, "x");
		table[i].points = 0;
		table[i].num_games = 0;
	}

	// open results.bin file
	f = fopen("results.bin", "rb");
	if (f == NULL)
	{ 
		printf("File not found\n");
		return 0;
	}
	
	while (1)
	{
		fread(&temp, sizeof(temp), 1, f);
		if (feof(f))
		{
			break;
		}

		/* find each team from the record in the table and update their points
		   if this is their first entry, create them in the table
		 */

		// find team 1
		i = 0;
		// while we haven't reached an empty table entry, and we haven't found our team in the table, and we haven't overflowed
		while((strcmp(table[i].name, "x") != 0) && (strcmp(table[i].name, temp.team1) != 0) && i < NUM_TEAMS)
		{
			i++;
		}
	
		// check for out of bounds of table array
		if (i >= NUM_TEAMS)
		{
			printf("Table overflow, exiting\n");
			return 1;
		}
		
		// if this is the first time we've seen this team, create an entry in the table for it
		if (i == last_updated)
		{
			last_updated++;
			strcpy(table[i].name, temp.team1);
		}
		
		// find team 2
		j = 0;
		// while we haven't reached an empty table entry, and we haven't found our team in the table, and we haven't overflowed
		while((strcmp(table[j].name, "x") != 0) && (strcmp(table[j].name, temp.team2) != 0) && j < NUM_TEAMS)
		{
			j++;
		}

		// check for out of bounds of table array
		if (j >= NUM_TEAMS)
		{
			printf("Table overflow, exiting\n");
			return 1;
		}

		// if this is the first time we've seen this team, create an entry in the table for it
		if (j == last_updated)
		{
			last_updated++;
			strcpy(table[j].name, temp.team2);
		}

		// at this stage, i and j refer to the correct table entries for team 1 and team 2 respectively

		table[i].num_games++;
		table[j].num_games++;
		if (temp.goals1 > temp.goals2)
		{
			table[i].points += 3;
		}
		else
		{
			if (temp.goals2 > temp.goals1)
			{
				table[j].points += 3;
			}
			else
			{
				// draw
				table[i].points += 1;
				table[j].points += 1;
			}
		}
	}

	// sort the table
	bubble_sort(table);

	// print the table
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("%10s	|%10s	|\n", "Team", "Points");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for (i = 0; i < NUM_TEAMS; i++)
	{
		printf("%10s	|	%d	|\n", table[i].name, table[i].points);		
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	fclose(f);

	return 0;
}

// Implementation of bubble sort
void bubble_sort(struct st_team arr[])
{
	struct st_team temp;
	int i, j;
	for (i = 0; i < NUM_TEAMS-1; i++)
	{
		for (j = i+1; j < NUM_TEAMS; j++)
		{
			if (arr[i].points < arr[j].points)
			{
				//swap
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}
