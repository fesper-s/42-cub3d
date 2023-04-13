/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:15:23 by gussoare          #+#    #+#             */
/*   Updated: 2023/04/13 08:29:31 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	step_and_side_calc(t_game *game)
{
	t_raycast	*ray;
	t_player	*pl;

	ray = game->ray;
	pl = game->pl;
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (pl->pl_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - pl->pl_x) * ray->delta_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (pl->pl_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - pl->pl_y) * ray->delta_y;
	}
}

void	camera_wall_calc(t_game *game)
{
	t_raycast	*ray;
	t_player	*pl;

	ray = game->ray;
	pl = game->pl;
	if (ray->side == 0)
		ray->camera_wall = fabs((ray->map_x - pl->pl_x \
			+ (1 - ray->step_x) / 2) / ray->raydir_x);
	else
		ray->camera_wall = fabs((ray->map_y - pl->pl_y \
			+ (1 - ray->step_y) / 2) / ray->raydir_y);
}

void	dda(t_game *game)
{
	t_raycast	*ray;

	ray = game->ray;
	while (ray->hit == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map->map[ray->map_x][ray->map_y] != '0')
			ray->hit = 1;
		camera_wall_calc(game);
	}
}

void	get_line_position(t_game *game)
{
	t_raycast	*ray;

	ray = game->ray;
	ray->line_height = (int)(game->height / ray->camera_wall);
	ray->draw_start = (-1 * ray->line_height) / 2 + game->height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + game->height / 2;
	if (ray->draw_end >= game->height)
		ray->draw_end = game->height - 1;
}

void	raycasting(t_game *game)
{
	int	x;

	x = -1;
	while (++x < game->width)
	{
		init_raycast(game, x);
		step_and_side_calc(game);
		dda(game);
		get_line_position(game);
		get_texture_id(game);
		get_texture_pos(game, x);
	}
}
