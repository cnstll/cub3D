#include "../includes/cube.h"

int load_textures(t_data *data, t_img **textures)
{
	int x;

	textures[0]->file_paths = ft_strdup(data->config->tx_no);
	textures[1]->file_paths = ft_strdup(data->config->tx_so);
	textures[2]->file_paths = ft_strdup(data->config->tx_we);
	textures[3]->file_paths = ft_strdup(data->config->tx_ea);
	textures[4]->file_paths = ft_strdup(data->config->tx_sprite);
	x = 0;
	while (x < 5)
	{
		textures[x]->img = mlx_xpm_file_to_image(
				data->mlx, textures[x]->file_paths,
				&textures[x]->width, &textures[x]->height);
		textures[x]->addr = (int *)mlx_get_data_addr(
				textures[x]->img, &textures[x]->bpp,
				&textures[x]->line_len, &textures[x]->endian);
		x++;
	}
	return(1);
}

int init_textures(t_data *data)
{
	int x;

	x = 0;
	data->textures = malloc(sizeof(t_img *) * 5);
	while (x < 5)
	{
		data->textures[x] = malloc(sizeof(t_img));
		x++;
	}
	load_textures(data, data->textures);
	return (1);
}