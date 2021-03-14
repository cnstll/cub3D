/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:43:58 by calle             #+#    #+#             */
/*   Updated: 2021/03/14 16:44:00 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	move_up(t_ray *ray, int **world)
{
	if (world[(int)(ray->pos_x + ray->dir_x * ray->ms)]
				[(int)(ray->pos_y)] == 0)
		ray->pos_x += ray->dir_x * ray->ms;
	if (world[(int)(ray->pos_x)]
				[(int)(ray->pos_y + ray->dir_y * ray->ms)] == 0)
		ray->pos_y += ray->dir_y * ray->ms;
}

void	move_down(t_ray *ray, int **world)
{
	if (world[(int)(ray->pos_x - ray->dir_x * ray->ms)]
				[(int)(ray->pos_y)] == 0)
		ray->pos_x -= ray->dir_x * ray->ms;
	if (world[(int)(ray->pos_x)]
				[(int)(ray->pos_y - ray->dir_y * ray->ms)] == 0)
		ray->pos_y -= ray->dir_y * ray->ms;
}

void	move_left(t_ray *ray, int **world)
{
	if (world[(int)(ray->pos_x - ray->plane_x * ray->ms)]
				[(int)(ray->pos_y)] == 0)
		ray->pos_x -= ray->plane_x * ray->ms;
	if (world[(int)(ray->pos_x)]
				[(int)(ray->pos_y - ray->plane_y * ray->ms)] == 0)
		ray->pos_y -= ray->plane_y * ray->ms;
}

void	move_right(t_ray *ray, int **world)
{
	if (world[(int)(ray->pos_x + ray->plane_x * ray->ms)]
				[(int)(ray->pos_y)] == 0)
		ray->pos_x += ray->plane_x * ray->ms;
	if (world[(int)(ray->pos_x)]
				[(int)(ray->pos_y + ray->plane_y * ray->ms)] == 0)
		ray->pos_y += ray->plane_y * ray->ms;
}
