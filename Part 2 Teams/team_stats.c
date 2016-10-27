/* Parses results.bin to calculate the stats of a requested team
 *
 * Operating system: Linux Mint 17.2 Rafaela 
 * Compiler: gcc 4.9.2
 * Author: Padraig Redmond C15755659
 */
 
#include <stdio.h>
#include "match.h"

int main()
{
	FILE *f;
	char team[20];
	int num_matches = 0, wins = 0, draws = 0, losses = 0;
	int goals_for = 0, goals_against = 0;
	struct st_match temp;

	// open both files
	f = fopen("results.bin", "rb");
	if (f == NULL)
	{ 
		printf("File not found\n");
		return 0;
	}

	printf("Enter a team: ");
	scanf("%s", team);
	
	// loop that reads every record of the results.bin file,
	// and updates the stats if the match involves the selected team
	while (1)
	{
		fread(&temp, sizeof(temp), 1, f);
		if (feof(f))
		{
			break;
		}

		// if team is team 1
		if (strcmp(team, temp.team1) == 0)
		{
			num_matches++;
			goals_for += temp.goals1;
			goals_against+= temp.goals2;

			if (temp.goals1 > temp.goals2)
			{
				wins++;
			}
			else
			{
				if (temp.goals1 < temp.goals2)
				{
					losses++;
				}
				else
				{
					draws++;
				}
			}
		}

		// if team is team 2
		if (strcmp(team, temp.team2) == 0)
		{
			num_matches++;
			goals_for += temp.goals2;
			goals_against+= temp.goals1;

			if (temp.goals1 > temp.goals2)
			{
				losses++;
			}
			else
			{
				if (temp.goals1 < temp.goals2)
				{
					wins++;
				}
				else
				{
					draws++;
				}
			}
		}
	}

	printf("Team: %s\n\n", team);
	printf("Matches Played: %d\n\n", num_matches);
	printf("Win: %d\n\n", wins);
	printf("Draw: %d\n\n", draws);
	printf("Loss: %d\n\n", losses);
	printf("Goals Scored: %d\n\n", goals_for);
	printf("Goals Conceded: %d\n\n", goals_against);

	fclose(f);

	return 0;
}

