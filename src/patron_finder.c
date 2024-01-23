#include "../peer2pong.h"

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shuffleArray(int *array, int size) {
    srand(time(NULL));
    
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&array[i], &array[j]);
    }
}

int* generateRandomArray(int n) {
    int* array = (int*)malloc(n * sizeof(int));

    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Fill the array with consecutive integers
    for (int i = 0; i < n; i++) {
        array[i] = i + 1;
    }

    // Shuffle the array
    shuffleArray(array, n);

    return array;
}

void count_lines(int *lineCount, int fileDescriptor) {
    FILE *file = fdopen(fileDescriptor, "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return;
    }

    int count = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }

    // Check if the last line is not terminated with a newline character
    if (count > 0 && fseek(file, -1, SEEK_END) == 0 && fgetc(file) != '\n') {
        count++;
    }

    *lineCount = count;

    fclose(file);
}

int main(int argv, char **argc)
{
	int players;
	int i = 1;
	int fd;
	int lines = 0;
	char **net_players = NULL;
	char *line = NULL;
	int *mix;
	int free_points = 0;
	
	if (argv == 3)
	{
		players = atoi(argc[1]);
		if (players % 2 != 0)
		{
			printf("Executing with %d players...\n", players + 1);
			players++;
		}
	}
	else if (argv == 2)
	{
		fd = open(argc[1], O_RDONLY);
		if (fd == -1)
			return (2);
		count_lines(&lines, fd);
		close(fd);
		// if (-1 == lseek(fd, 0, SEEK_SET))
		// {
		// 	printf("mal\n");
		// 	return 0;
		// }
		printf("num players: %d\n\n", lines);
		players = lines;
		if (players % 2 != 0)
		{
			players++;
			free_points = 1;
			printf("Theres uneven number of players!\nWe are going to play with FREE POINTS!\n\n");
		}
		net_players = malloc(sizeof(char *) * (players + 1));
		net_players[players] = 0;
		fd = open(argc[1], O_RDONLY);
		if (fd == -1)
			return (2);
		while (i <= players)
		{
			get_next_line(fd, &line);
			net_players[i - 1] = malloc(sizeof(char) * (strlen(line) + 1));
			if (i + 1 == players && free_points == 1)
				strcpy(net_players[i - 1], "FREE POINTS");
			else
			{
				strcpy(net_players[i - 1], line);
				free(line);
				line = NULL;
			}
			i++;
		}
	}
	else 
	{
		printf("Executing with 8 players...\n");
		players = 8;
	}
	mix = generateRandomArray(players);
	i = 1;
	if (1)
	{
		while (i <= players)
		{
			printf("Player %s\n", net_players[mix[i - 1] - 1]);
			if (i == players/2)
				printf("(%s , %s)\n", net_players[mix[i - 1] - 1], net_players[mix[players - 1] - 1]);
			else if (i == players)
				printf("(%s , %s)\n", net_players[mix[i - 1] - 1], net_players[mix[players/2 - 1] - 1]);
			else
				printf("(%s , %s)\n", net_players[mix[i - 1] - 1], net_players[mix[(players - i) - 1] - 1]);
			if (i == 1)
				printf("(%s , %s)\n", net_players[mix[i - 1] - 1], net_players[mix[players - 1] - 1]);
			else
				printf("(%s , %s)\n", net_players[mix[i - 1] - 1], net_players[mix[i - 2] - 1]);
			if (i == players)
				printf("(%s , %s)\n", net_players[mix[i - 1] - 1], net_players[mix[0] - 1]);
			else
				printf("(%s , %s)\n", net_players[mix[i - 1] - 1], net_players[mix[i] - 1]);
			i++;
			printf("\n");
		}
	}
	else
	{
		i = 1;
		players++;
		while (i <= players)
		{
			printf("Player %d\n", i);
			if (i == players/2)
				printf("(%d , %d)\n", i, players);
			else if (i == players)
				printf("(%d , %d)\n", i, players/2);
			else
				printf("(%d , %d)\n", i, players - i);
			if (i == 1)
				printf("(%d , %d)\n", i, players);
			else
				printf("(%d , %d)\n", i, i - 1);
			if (i == players)
				printf("(%d , %d)\n", i, 1);
			else
				printf("(%d , %d)\n", i, i + 1);
			i++;
		}
	}
	// i = 0;
	// while (net_players[i])
	// {
	// 	printf("%s\n", net_players[i]);
	// 	i++;
	// }
}