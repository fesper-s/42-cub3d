/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gussoare <gussoare@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:32:20 by gussoare          #+#    #+#             */
/*   Updated: 2023/04/10 10:02:50 by gussoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_var(t_game *game, t_map *map)
{
	game->height = 480;
	game->width = 640;
	game->pl->pldir_x = 0.00000000001;
	game->pl->pldir_y = 0.00000000001;
	game->ray->plane_x = 0;
	game->ray->plane_y = 0;
	game->pl->old_pldir_x = 0;
	game->ray->old_plane_x = 0;
	game->ray->camera_wall = 0;
	game->ray->camera_x = 0;
	game->ray->step_x = 0;
	game->ray->step_y = 0;
	game->ray->side_x = 0;
	game->ray->side_y = 0;
	game->pl->ver_walk = 0;
	game->pl->hor_walk = 0;
	game->pl->turn_dir = 0;
	game->map = map;
}

void	pl_pos(t_game *game, t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (char_in_str("NSEW", map->map[i][j]))
			{
				game->pl->pl_x = i;
				game->pl->pl_y = j;
				set_player_pov(game, i, j);
				break ;
			}
		}
	}
}

void	set_player_pov(t_game *game, int i, int j)
{
	t_map	*map;

	map = game->map;
	if (map->map[i][j] == 'N')
	{
		game->pl->pldir_x = -1;
		game->ray->plane_y = -0.66;
	}
	else if (map->map[i][j] == 'S')
	{
		game->pl->pldir_x = 1;
		game->ray->plane_y = 0.66;
	}
	else if (map->map[i][j] == 'E')
	{
		game->pl->pldir_y = 1;
		game->ray->plane_x = -0.66;
	}
	else if (map->map[i][j] == 'W')
	{
		game->pl->pldir_y = -1;
		game->ray->plane_x = 0.66;
	}
		map->map[i][j] = '0';
}

void	init_raycast(t_game *game, int x)
{
	t_raycast	*ray;
	t_player	*pl;

	ray = game->ray;
	pl = game->pl;
	ray->camera_x = 2 * x / (double)(game->width) - 1;
	ray->raydir_x = pl->pldir_x + ray->plane_x * ray->camera_x;
	ray->raydir_y = pl->pldir_y + ray->plane_y * ray->camera_x;
	if (ray->raydir_x == 0)
		ray->raydir_x = 1e30;
	else
		ray->delta_x = fabs(1 / ray->raydir_x);
	if (ray->raydir_y == 0)
		ray->raydir_y = 1e30;
	else
		ray->delta_y = fabs(1 / ray->raydir_y);
	ray->map_x = (int)game->pl->pl_x;
	ray->map_y = (int)game->pl->pl_y;
	ray->hit = 0;
}
