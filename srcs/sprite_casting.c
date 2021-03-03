/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:37:17 by calle             #+#    #+#             */
/*   Updated: 2021/02/23 22:56:39 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	sort_sprites(t_data *data, t_ray *ray, t_sprite *sprite)
{
	int i;

	i = 0;
	while(i < sprite->num)
	{
		sprite->distance[i] = ((ray->pos_x - sprite->sp[i].x)
			* (ray->pos_x - sprite->sp[i].x) + (ray->pos_y - sprite->sp[i].y)
			* (ray->pos_y - sprite->sp[i].y));
		i++;
	}
	bubble_sort(data->sprite, sprite->distance, sprite->num);
}

static void	put_sprite_stripes(t_data *data, t_sprite *sprite, int stripe)
{
	int color;
	int y;
	int d;

	y = sprite->start_y;
	while(y < sprite->end_y)
	{
		d = y * 256 - data->screen_ht * 128 + sprite->height * 128;
		sprite->tx_y = ((d * TEXTR_HT) / sprite->height) / 256;
		color =
			data->textures[4]->addr[TEXTR_WD * sprite->tx_y + sprite->tx_x];
		if((color & 0x00FFFFFF) != 0)
			data->buffer[y][stripe] = color;
		y++;
	}
}

static void	put_sprite(t_data *data, t_sprite *sprite)
{
	int i;

	i = sprite->start_x;
	while (i < sprite->end_x)
	{
		sprite->tx_x =
				(int)(256 * (i - (-sprite->width / 2 + sprite->screen_x))
				* TEXTR_WD / sprite->width) / 256;
		if(sprite->transfo_y > 0 && i > 0 && i < data->screen_wd
				&& sprite->transfo_y < sprite->buffer[i])
		{
			put_sprite_stripes(data, sprite, i);
		}
		i++;
	}
}

static void	calculate_sprite_dimensions(t_data *data, t_sprite *sprite)
{
	sprite->height = fabs((int)(data->screen_ht / (sprite->transfo_y)));
	sprite->start_y = -sprite->height / 2 + data->screen_ht / 2;
	if(sprite->start_y < 0)
		sprite->start_y = 0;
	sprite->end_y = sprite->height / 2 + data->screen_ht / 2;
	if(sprite->end_y >= data->screen_ht)
		sprite->end_y = data->screen_ht - 1;
	sprite->width = fabs((int)(data->screen_ht / sprite->transfo_y));
	sprite->start_x = -sprite->width / 2 + sprite->screen_x;
	if(sprite->start_x < 0)
		sprite->start_x = 0;
	sprite->end_x = sprite->width / 2 + sprite->screen_x;
	if(sprite->end_x >= data->screen_wd)
		sprite->end_x = data->screen_wd - 1;
}

void	handle_sprites(t_data *data, t_ray *ray, t_sprite *sprite)
{
	int i;
	int w;

	i = 0;
	w =  data->screen_wd;
	sort_sprites(data, ray, sprite);
	while(i < sprite->num)
	{
		sprite->x = sprite->sp[i].x - ray->pos_x;
		sprite->y = sprite->sp[i].y - ray->pos_y;
		sprite->invert =
			1.0 / (ray->plane_x * ray->dir_y - ray->dir_x * ray->plane_y);
		sprite->transfo_x =
			sprite->invert * (ray->dir_y * sprite->x - ray->dir_x * sprite->y);
		sprite->transfo_y = sprite->invert
			* (-ray->plane_y * sprite->x + ray->plane_x * sprite->y);
		sprite->screen_x =
			(int)((w / 2) * (1 + sprite->transfo_x / sprite->transfo_y));

		calculate_sprite_dimensions(data, sprite);
		put_sprite(data, sprite);
		i++;
	}
}

