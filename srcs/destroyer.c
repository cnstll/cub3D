#include "../includes/cube.h"

void	destroy_sprites(t_data *data)
{
	free(data->sprite->buffer);
	free(data->sprite->distance);
	free(data->sprite->sp);
	free(data->sprite);
}

void	destroy_textures(t_data *data)
{
	int x;

	x = 0;
	while (x < 5)
	{
		mlx_destroy_image(data->mlx, data->textures[x]->img);
		free(data->textures[x]->file_paths);
		free(data->textures[x++]);
	}
	free(data->textures);
}

void	free_and_destroy_all(t_data *data)
{
	free(data->mlx);
	free(data->ray);
	free(data->img);
	free(data->inputs);
	destroy_sprites(data);
	destroy_textures(data);
}
