#include "../includes/cube.h"
void	error_handler(int error)
{
	if (error < 0)
		printf("Error\n");
	if (error == -1)
		printf("Something went wrong with the configuration/map file\n");
	else if (error == -2)
		printf("Invalid character in map\n");
	else if (error == -3)
		printf("Invalid configuration\n");
	else if (error == -4)
		printf("Empty configuration file\n");
	else if (error == -5)
		printf("Too many configuration parameters\n");
	else if (error == -6)
		printf("Configuration parameter missing or invalid\n");
	else if (error == -7)
		printf("Invalid map\n");
	else if (error == -8)
		printf("No input file\n");
	else
		printf("Configuration ok\n");
}
