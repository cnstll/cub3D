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
		free(data->textures[x]);
		x++;
	}
	free(data->textures);
}

void	free_and_destroy_play(t_data *data)
{
	free(data->ray);
	free(data->img);
	free(data->inputs);
	free_2d_array(data->buffer, data->screen_ht);
	free_2d_array(data->world, data->world_ht);
	destroy_sprites(data);
	destroy_textures(data);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

void	free_and_destroy_save(t_data *data)
{
	free(data->ray);
	free_2d_array(data->buffer, data->screen_ht);
	free_2d_array(data->world, data->world_ht);
	destroy_sprites(data);
	destroy_textures(data);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

