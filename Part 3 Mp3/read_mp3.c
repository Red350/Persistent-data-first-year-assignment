/* This program takes a file as an argument.
 * If the file has a valid id3 tag, it will print
 * the data stored in the tag.
 *
 * Operating system: Linux Mint 17.2 Rafaela 
 * Compiler: gcc 4.9.2
 * Author: Padraig Redmond C15755659
 */

#include <stdio.h>
#include <string.h>

struct st_id3
{
	char tag_start[3];
	char title[30];
	char artist[30];
	char album[30];
	char year[4];
	char comment[30];
	char genre;
};

int main(int argc, char *argv[])
{
	FILE *f, *genre_file;
	struct st_id3 id3_tag;
	char genre[30];
	int i;

	// make sure user has put a file as an argument
	if (argc != 2)
	{
		printf("Must have a file as an argument\n");
		return 0;
	}

	// open both files
	f = fopen(argv[1], "rb");
	if (f == NULL)
	{
		printf("File not found, exiting\n");
		return 1;
	}
	genre_file = fopen("genre.txt", "r");
	if (genre_file == NULL)
	{
		printf("File not found, exiting\n");
		return 1;
	}

	// jump to the tag part of the mp3 file
	fseek(f, -128, SEEK_END);
	// read the entire tag into id3 struct
	fread(&id3_tag, sizeof(id3_tag), 1, f);
	
	// If there's a valid ID3 tag, print the information
	if (id3_tag.tag_start[0] == 'T' && id3_tag.tag_start[1] == 'A' && id3_tag.tag_start[2] == 'G')
	{
		printf("\nTitle: ");
		if (id3_tag.title[0] == '\0')
		{
			printf("Unknown");
		}
		else
		{
			for(i = 0; i < 30; i++)
			{
				putchar(id3_tag.title[i]);
			}
		}

		printf("\nArtist: ");
		if (id3_tag.artist[0] == '\0')
		{
			printf("Unknown");
		}
		else
		{
			for(i = 0; i < 30; i++)
			{
				putchar(id3_tag.artist[i]);
			}
		}

		printf("\nAlbum: ");
		if (id3_tag.album[0] == '\0')
		{
			printf("Unknown");
		}
		else
		{
			for(i = 0; i < 30; i++)
			{
				putchar(id3_tag.album[i]);
			}
		}

		printf("\nYear: ");
		if (id3_tag.year[0] == '\0')
		{
			printf("Unknown");
		}
		else
		{
			for(i = 0; i < 4; i++)
			{
				putchar(id3_tag.year[i]);
			}
		}

		printf("\nTrack number: ");
		if (id3_tag.comment[29] == '\0')
		{
			printf("Unknown");
		}
		else
		{
			printf("%d", id3_tag.comment[29]);
		}

		// determine genre using genre.txt
		// Highest genre is 125
		printf("\nGenre: ");
		if ((unsigned char)id3_tag.genre > 125)
		{
			printf("Unknown\n");
		}
		else
		{
			for (i = 0; i <= (unsigned char)id3_tag.genre; i++)
			{
				fgets(genre, 30, genre_file);
			}
			printf("%s", genre);
		}
		printf("\n");
	}
	else
	{
		printf("This file does not contain a valid audio tag\n");
	}

	return 0;
}

