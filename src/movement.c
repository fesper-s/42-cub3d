/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gussoare <gussoare@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:34:37 by gussoare          #+#    #+#             */
/*   Updated: 2023/04/05 15:36:20 by gussoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	vertical_movement(t_game *game, double speed)
{
	t_player	*pl;

	pl = game->pl;
	if (game->map->map[(int)(pl->pl_x + pl->ver_walk * \
		(pl->pldir_x * speed))][(int)pl->pl_y] == '0')
		pl->pl_x += pl->ver_walk * (pl->pldir_x * speed);
	if (game->map->map[(int)(pl->pl_x)][(int)(pl->pl_y + pl->ver_walk * \
	(pl->pldir_y * speed))] == '0')
		pl->pl_y += pl->ver_walk * (pl->pldir_y * speed);
}

void	horizontal_movement(t_game *game, double speed)
{
	t_player	*pl;
	t_raycast	*ray;

	pl = game->pl;
	ray = game->ray;
	if (game->map->map[(int)(pl->pl_x + pl->hor_walk * \
		(ray->plane_x * speed))][(int)pl->pl_y] == '0')
		pl->pl_x += pl->hor_walk * (ray->plane_x * speed);
	if (game->map->map[(int)pl->pl_x][(int)(pl->pl_y + pl->hor_walk * \
		(ray->plane_y * speed))] == '0')
		pl->pl_y += pl->hor_walk * (ray->plane_y * speed);
}

void	camera_movement(t_game *game, double speed)
{
	t_player	*pl;
	t_raycast	*ray;
	double		rotation;

	rotation = game->pl->turn_dir * speed;
	pl = game->pl;
	ray = game->ray;
	pl->old_pldir_x = pl->pldir_x;
    pl->pldir_x = pl->pldir_x * cos(rotation) - pl->pldir_y * sin(rotation);
    pl->pldir_y = pl->old_pldir_x * sin(rotation) + pl->pldir_y * cos(rotation);
    ray->old_plane_x = ray->plane_x;
	ray->plane_x = ray->plane_x * cos(rotation) - ray->plane_y * sin(rotation);
	ray->plane_y = ray->old_plane_x * sin(rotation) + ray->plane_y * cos(rotation);
}

int	key_press(int key, t_game *game)
{
	if (key == W_KEY)
		game->pl->ver_walk = 1;
	else if (key == S_KEY)
		game->pl->ver_walk = -1;
	else if (key == A_KEY)
		game->pl->hor_walk = 1;
	else if (key == D_KEY)
		game->pl->hor_walk = -1;
	else if (key == RIGHT_KEY)
		game->pl->turn_dir = -1;
	else if (key == LEFT_KEY)
		game->pl->turn_dir = 1;
	else if (key == ESC_KEY)
		close_game(game);
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == W_KEY)
		game->pl->ver_walk = 0;
	else if (key == A_KEY)
		game->pl->hor_walk = 0;
	else if (key == S_KEY)
		game->pl->ver_walk = 0;
	else if (key == D_KEY)
		game->pl->hor_walk = 0;
	else if (key == RIGHT_KEY)
		game->pl->turn_dir = 0;
	else if (key == LEFT_KEY)
		game->pl->turn_dir = 0;
	return (0);
}
