/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 15:11:40 by calle             #+#    #+#             */
/*   Updated: 2021/03/14 15:11:42 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		printf("Invalid or missing input file\n");
	else if (error == -9)
		printf("Invalid or missing argument\n");
	else if (error == -10)
		printf("Texture file format not supported\n");
	else if (error < -10)
		printf("Unexpected error\n");
}
