#include "../includes/cube.h"

int	find_sprite_num(t_data *data)
{
	int	r;
	int	i;
	int	j;

	r = 0;
	i = 0;
	while (i < data->world_ht)
	{
		j = 0;
		while (j < data->world_wd)
		{
			if (data->world[i][j] == 2)
				r++;
			j++;
		}
		i++;
	}
	return (r);
}

void	find_sprite_pos(t_data *data, t_sprite *sprite)
{
	int	r;
	int	i;
	int	j;

	r = 0;
	i = 0;
	while (i < data->world_ht)
	{
		j = 0;
		while (j < data->world_wd && r < sprite->num)
		{
			if (data->world[i][j] == 2)
				sprite->sp[r++] = (t_sp){(double)(i) + 0.5, (double)(j) + 0.5, 4};
			j++;
		}
		i++;
	}
}

int	init_map(t_data *data)
{
	data->sprite = malloc(sizeof(t_sprite));
	data->sprite->num = find_sprite_num(data);
	data->sprite->buffer = malloc(sizeof(double) * data->screen_wd);
	data->sprite->distance = malloc(sizeof(double) * data->sprite->num);
	data->sprite->sp = malloc(sizeof(t_sp) * data->sprite->num);
	find_sprite_pos(data, data->sprite);
	return (1);
}

