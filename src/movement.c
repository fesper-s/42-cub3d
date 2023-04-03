/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gussoare <gussoare@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:34:37 by gussoare          #+#    #+#             */
/*   Updated: 2023/04/03 16:35:20 by gussoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void vertical_movement(int key, t_game *game, double speed)
{
	t_player	*pl;

	pl = game->pl;
	if (key == W_KEY)
	{
		if (game->map->map[(int)(pl->pl_x + pl->pldir_x *speed)][(int)pl->pl_y] == '0')
			pl->pl_x += pl->pldir_x *speed;
      	if (game->map->map[(int)(pl->pl_x)][(int)(pl->pl_y + pl->pldir_y *speed)] == '0')
	  		pl->pl_y += pl->pldir_y *speed;
    }
	else if (key == S_KEY)
	{
		if (game->map->map[(int)(pl->pl_x - pl->pldir_x *speed)][(int)pl->pl_y] == '0')
			pl->pl_x -= pl->pldir_x *speed;
      	if (game->map->map[(int)(pl->pl_x)][(int)(pl->pl_y - pl->pldir_y *speed)] == '0')
	  		pl->pl_y -= pl->pldir_y *speed;
    }
}

void horizontal_movement(int key, t_game *game, double speed)
{
	t_player	*pl;
	t_raycast	*ray;

	pl = game->pl;
	ray = game->ray;
	if (key == D_KEY)
	{
		if (game->map->map[(int)(pl->pl_x + ray->plane_x * speed)][(int)pl->pl_y] == '0')
			pl->pl_x += ray->plane_x * speed;
		if (game->map->map[(int)pl->pl_x][(int)(pl->pl_y + ray->plane_y *speed)] == '0')
			pl->pl_y += ray->plane_y * speed;
    }
	else if (key == A_KEY)
	{
		if (game->map->map[(int)(pl->pl_x - ray->plane_x *speed)][(int)pl->pl_y] == '0')
			pl->pl_x -= ray->plane_x *speed;
		if (game->map->map[(int)pl->pl_x][(int)(pl->pl_y - ray->plane_y *speed)] == '0')
			pl->pl_y -= ray->plane_y * speed;
	}
}

void	camera_movement(int key, t_game *game, double speed)
{
	t_player	*pl;
	t_raycast	*ray;

	pl = game->pl;
	ray = game->ray;
	if (key == LEFT_KEY)
	{
		pl->old_pldir_x = pl->pldir_x;
      	pl->pldir_x = pl->pldir_x * cos(speed) - pl->pldir_y * sin(speed);
      	pl->pldir_y = pl->old_pldir_x * sin(speed) + pl->pldir_y * cos(speed);
      	ray->old_plane_x = ray->plane_x;
      	ray->plane_x = ray->plane_x * cos(speed)- ray->plane_y * sin(speed);
     	ray->plane_y = ray->old_plane_x * sin(speed) + ray->plane_y * cos(speed);
	}
	else if (key == RIGHT_KEY)
	{
		pl->old_pldir_x = pl->pldir_x;
      	pl->pldir_x = pl->pldir_x * cos(-speed) - pl->pldir_y * sin(-speed);
      	pl->pldir_y = pl->old_pldir_x * sin(-speed) + pl->pldir_y * cos(-speed);
      	ray->old_plane_x = ray->plane_x;
      	ray->plane_x = ray->plane_x * cos(-speed) - ray->plane_y * sin(-speed);
     	ray->plane_y = ray->old_plane_x * sin(-speed) + ray->plane_y * cos(-speed);
	}
}


void	handle_keys(t_game *game)
{
	t_keys	*keys;
	float		speed;

	keys = game->keys;
	speed = 0.25;
	if (keys->w != keys->s)
	{
		if (keys->w == 1)
			vertical_movement(W_KEY, game, speed);
		else if (keys->s == 1)
			vertical_movement(S_KEY, game, speed);
	}
	if (keys->a != keys->d)
	{
		if (keys->a == 1)
			horizontal_movement(A_KEY, game, speed);
		else if (keys->d == 1)
			horizontal_movement(D_KEY, game, speed);
	}
	if (keys->right != keys->left)
	{
		if (keys->right == 1)
			camera_movement(RIGHT_KEY, game, 0.1);
		else if (keys->left == 1)
			camera_movement(LEFT_KEY, game, 0.1);
	}
}

int	key_press(int key, t_game *game)
{
	if (key == W_KEY)
		game->keys->w = 1;
	else if (key == A_KEY)
		game->keys->a = 1;
	else if (key == S_KEY)
		game->keys->s = 1;
	else if (key == D_KEY)
		game->keys->d = 1;
	else if (key == RIGHT_KEY)
		game->keys->right = 1;
	else if (key == LEFT_KEY)
		game->keys->left = 1;
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == W_KEY)
		game->keys->w = 0;
	else if (key == A_KEY)
		game->keys->a = 0;
	else if (key == S_KEY)
		game->keys->s = 0;
	else if (key == D_KEY)
		game->keys->d = 0;
	else if (key == RIGHT_KEY)
		game->keys->right = 0;
	else if (key == LEFT_KEY)
		game->keys->left = 0;
	return (0);
}