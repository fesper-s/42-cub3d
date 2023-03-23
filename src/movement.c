/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gussoare <gussoare@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:02:24 by gussoare          #+#    #+#             */
/*   Updated: 2023/03/23 12:49:58 by gussoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_event(int key, t_game *game)
{
	t_player	*pl;
	t_raycast	*ray;

	pl = game->pl;
	ray = game->ray;
	
	while (key == W_KEY)
	{
		if (game->map->map[(int)(pl->pl_x + pl->pldir_x * 0.05)][(int)pl->pl_y] == '0')
			pl->pl_x += pl->pldir_x * 0.05;
      	if (game->map->map[(int)(pl->pl_x)][(int)(pl->pl_y + pl->pldir_y * 0.05)] == '0')
	  		pl->pl_y += pl->pldir_y * 0.05;
		mlx_clear_window(game->mlx, game->mlx_win);
		raycasting(game);
    }
	
	if (key == S_KEY)
	{
		if (game->map->map[(int)(pl->pl_x - pl->pldir_x * 0.05)][(int)pl->pl_y] == '0')
			pl->pl_x -= pl->pldir_x * 0.05;
      	if (game->map->map[(int)(pl->pl_x)][(int)(pl->pl_y - pl->pldir_y * 0.05)] == '0')
	  		pl->pl_y -= pl->pldir_y * 0.05;
		mlx_clear_window(game->mlx, game->mlx_win);
		raycasting(game);
    }

	if (key == D_KEY)
	{
		if (game->map->map[(int)(pl->pl_x + ray->plane_x * 0.05)][(int)pl->pl_y] == '0')
			pl->pl_x += ray->plane_x * 0.05;
		if (game->map->map[(int)pl->pl_x][(int)(pl->pl_y + ray->plane_y * 0.05)] == '0')
			pl->pl_y += ray->plane_y * 0.05;
		mlx_clear_window(game->mlx, game->mlx_win);
		raycasting(game);
    }


	if (key == A_KEY)
	{
		if (game->map->map[(int)(pl->pl_x - ray->plane_x * 0.05)][(int)pl->pl_y] == '0')
			pl->pl_x -= ray->plane_x * 0.05;
		if (game->map->map[(int)pl->pl_x][(int)(pl->pl_y - ray->plane_y * 0.05)] == '0')
			pl->pl_y -= ray->plane_y * 0.05;
		mlx_clear_window(game->mlx, game->mlx_win);
		raycasting(game);
	}

	if (key == RIGHT_KEY)
	{
		pl->old_pldir_x = pl->pldir_x;
      	pl->pldir_x = pl->pldir_x * cos(0.05) - pl->pldir_y * sin(0.05);
      	pl->pldir_y = pl->old_pldir_x * sin(0.05) + pl->pldir_y * cos(0.05);
      	ray->old_plane_x = ray->plane_x;
      	ray->plane_x = ray->plane_x * cos(0.05) - ray->plane_y * sin(0.05);
     	ray->plane_y = ray->old_plane_x * sin(0.05) + ray->plane_y * cos(0.05);
		mlx_clear_window(game->mlx, game->mlx_win);
		raycasting(game);
	}

	if (key == LEFT_KEY)
	{
		pl->old_pldir_x = pl->pldir_x;
      	pl->pldir_x = pl->pldir_x * cos(-0.05) - pl->pldir_y * sin(-0.05);
      	pl->pldir_y = pl->old_pldir_x * sin(-0.05) + pl->pldir_y * cos(-0.05);
      	ray->old_plane_x = ray->plane_x;
      	ray->plane_x = ray->plane_x * cos(-0.05) - ray->plane_y * sin(-0.05);
     	ray->plane_y = ray->old_plane_x * sin(-0.05) + ray->plane_y * cos(-0.05);
		mlx_clear_window(game->mlx, game->mlx_win);
		raycasting(game);
	}
	return (0);
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